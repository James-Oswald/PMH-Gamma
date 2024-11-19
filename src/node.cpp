#include "node.h"

#include <iostream>
#include "graph.h"

/*
    std::vector<node> children;
    std::vector<std::string> atoms;
    CUT_TYPE cut;
*/

node::node(){
    children = std::vector<node*>();
    atoms = std::vector<atom>();
    cut = TOP;
    level = 0;
    coords[0] = std::numeric_limits<int>::min();
    coords[1] = std::numeric_limits<int>::min();
    coords[2] = std::numeric_limits<int>::max();
    coords[3] = std::numeric_limits<int>::max();
}

node::node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    children = std::vector<node*>();
    atoms = std::vector<atom>();
    cut = c;
    level = 0;
    if (bottomLeftX >= topRightX || bottomLeftY >= topRightY){
        //TODO: This is an error. Figure out what to do here
        std::cerr << "node construction error: upper coord < lower coord" << std::endl;
    }
    coords[0] = bottomLeftX;
    coords[1] = bottomLeftY;
    coords[2] = topRightX;
    coords[3] = topRightY;
}

node::node(const node& n){
    this->children = std::vector<node*>(n.children.size());
    for (int i = 0; i < n.children.size(); ++i){
        this->children[i] = new node(*n.children[i]);
    }
    this->atoms = n.atoms;
    this->cut = n.cut;
    this->level = n.level;
    for (int i = 0; i < 4; ++i){
        this->coords[i] = n.coords[i];
    }
}

node::~node(){
    for (int i = 0; i < this->children.size(); ++i){
        delete(this->children[i]);
    }
}

void node::updateLevel(int l){
    this->level = l;
    for (int i = 0; i < this->children.size(); ++i){
        this->children[i]->updateLevel(l+1);
    }
}

void node::shift(int deltaX, int deltaY){
    this->coords[0] += deltaX;
    this->coords[1] += deltaY;
    this->coords[2] += deltaX;
    this->coords[3] += deltaY;
    std::vector<atom> olda = this->getAtoms();
    for (int i = 0; i < olda.size(); ++i){
        this->atoms[i] = atom(olda[i].getName(), olda[i].xCoord()+deltaX, olda[i].yCoord()+deltaY);
    }
    for (int i = 0; i < this->children.size(); ++i){
        this->children[i]->shift(deltaX, deltaY);
    }
}

bool const node::contains(const atom& a) const{
    for (int i = 0; i < this->atoms.size(); ++i){
        if (this->atoms[i] == a){
            return true;
        }
    }
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->contains(a)){
            return true;
        }
    }
    return false;
}

// returns true if any subgraph contains the cut described
// does not check the cut called on, use isSameCut for that
bool const node::contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const{
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->isSameCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY)) return true;
        if (this->children[i]->contains(c, bottomLeftX, bottomLeftY, topRightX, topRightY)){
            return true;
        }
    }
    return false;
}

bool const node::contains(const node* n) const{
    if (*this == *n) return true;
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->contains(n)){
            return true;
        }
    }
    return false;
}

bool const node::envelopes(const node * n) const{
    return (n->coords[0] > this->coords[0] && n->coords[1] > this->coords[1]
     && n->coords[2] < this->coords[2] && n->coords[3] < this->coords[3]);
}
bool const node::envelopes(const atom& a) const{
    return (a.xCoord() > this->coords[0] && a.yCoord() > this->coords[1]
     && a.xCoord() < this->coords[2] && a.yCoord() < this->coords[3]);
}

bool node::envelopes(int left, int bottom, int right, int top) const{
    return (left > this->coords[0] && bottom > this->coords[1]
     && right < this->coords[2] && top < this->coords[3]);
}

bool node::overlaps(const node* n) const{
    return (this->coords[0] <= n->coords[2] && this->coords[2] >= n->coords[0] &&
     this->coords[3] >= n->coords[1] && this->coords[1] <= n->coords[3] );
}

bool node::overlaps(int left, int bottom, int right, int top) const{
    return (this->coords[0] <= right && this->coords[2] >= left &&
     this->coords[3] >= bottom && this->coords[1] <= top );
}

bool const node::isSameCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const{
    return (this->cut == c && this->coords[0] == bottomLeftX && this->coords[1] == bottomLeftY
            && this->coords[2] == topRightX && this->coords[3] == topRightY);
}

bool const node::isSameCut(const node* n) const{
    return isSameCut(n->cut, n->coords[0], n->coords[1], n->coords[2], n->coords[3]);
}

bool node::isSameGraph(const node* n) const{
    for (int i = 0; i < this->atoms.size(); ++i){
        if (this->atoms[i].getName() != n->atoms[i].getName()){
            return false;
        }
    }
    for (int i = 0; i < this->children.size(); ++i){
        if (!(this->children[i]->isSameGraph(n->children[i]))){
            return false;
        }
    }
    return true;
}

//checks if the provided coordinates are on even or odd level
//mod = 0 for even, mod = 1 for odd
bool node::onLevel(const node* n, int mod) const{
    if (!this->envelopes(n)) return false;
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->envelopes(n)){
            return this->children[i]->onLevel(n, mod);
        }
    }
    //The coordinates exist on this level and in none of the children
    return (this->level % 2 == mod);
}

bool node::withinSameCut(const node* n) const{
    if (!this->envelopes(n)) return false;
    //see if it is in any children
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->envelopes(n)){
            return this->children[i]->withinSameCut(n);
        }
    }
    //see if any children overlap it
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->overlaps(n)){
            return false;
        }
    }
    return true;
}

bool node::operator==(const node& other) const{\
    if (this->cut != other.cut || this->atoms.size() != other.atoms.size() || this->children.size() != other.children.size()){
        return false;
    }
    for (int i = 0; i < 4; ++i){
        if (this->coords[i] != other.coords[i]){
            return false;
        }
    }
    for (int i = 0; i < this->atoms.size(); ++i){
        if (this->atoms[i] != other.atoms[i]){
            return false;
        }
    }

    for (int i = 0; i < this->children.size(); ++i){
        if (*(this->children[i]) != *(other.children[i])){
            return false;
        }
    }
    return true;
}


bool const node::addAtom(const atom& a){
    if (a.xCoord() > coords[0] && a.yCoord() > coords[1]
     && a.xCoord() < coords[2] && a.yCoord() < coords[3]){
        //The location of the atom really is inside the bounds of the cut
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            if (this->children[i]->addAtom(a)){
                found = true;
                break;
            }
        }
        if (!found)
            atoms.push_back(a);
        return true;
    }
    return false;
}

bool const node::addSubgraph(node * n){
    if (this->envelopes(n)){
        //The other cut is fully contained within this one
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            if (this->children[i]->addSubgraph(n)){
                found = true;
                break;
            }
        }
        if (!found) {
            //have to see if current shit fits into the thing we just added
            for (int i = 0; i < this->atoms.size(); ++i){
                if (n->addAtom(this->atoms[i])){
                    this->removeAtom(this->atoms[i]);
                }
            }
            for (int i = 0; i < this->children.size(); ++i){
                node* newNode = new node(*this->children[i]);
                if (n->addSubgraph(newNode)){
                    this->removeSubgraph(this->children[i]);
                } else {
                    delete(newNode);
                }
            }

            children.push_back(n);
            n->updateLevel(this->level + 1);
        }
        return true;
    }
    return false;
}

bool const node::removeAtom(const atom& a){
    int x = -1;
    for (int i = 0; i < this->atoms.size(); ++i){
        if (a == this->atoms[i]){
            x = i;
            break;
        }
    }
    if (x == -1){
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            found = (*this->children[i]).removeAtom(a);
        }
        return found;
    }
    for (int i = x+1; i < this->atoms.size(); ++i){
        this->atoms[i-1] = this->atoms[i];
    }
    this->atoms.pop_back();
    return true;
}


//Only for editing mode
bool const node::removeCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    int x = -1;
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->cut == c && this->children[i]->coords[0] == bottomLeftX
        && this->children[i]->coords[1] == bottomLeftY && this->children[i]->coords[2] == topRightX
        && this->children[i]->coords[3] == topRightY){
            x = i;
            break;
        }
    }
    if (x == -1){
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            found = this->children[i]->removeCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
        }
        return found;
    }
    node* oldChild = this->children[x];
    for (int i = x+1; i < this->children.size(); ++i){
        this->children[i-1] = this->children[i];
    }
    this->children.pop_back();
    //Add all of the old node's atoms and children to the parent
    for (int i = 0; i < oldChild->atoms.size(); ++i){
        this->atoms.push_back(oldChild->atoms[i]);
    }
    for (int i = 0; i < oldChild->children.size(); ++i){
        this->children.push_back(oldChild->children[i]);
    }
    //Delete the old node
    //we have to empty out the array of children so that it does not delete nodes still in use
    oldChild->children = std::vector<node*>();
    delete(oldChild);
    return true;
}

bool const node::removeSubgraph(const node* n){
    int x = -1;
    for (int i = 0; i < this->children.size(); ++i){
        if (n == this->children[i] || *n == *this->children[i]){
            x = i;
            break;
        }
    }
    if (x == -1){
        //look recursively through children
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            found = (*this->children[i]).removeSubgraph(n);
        }
        return found;
    }
    //delete the old node
    delete(this->children[x]);

    //adjust children list
    for (int i = x+1; i < this->children.size(); ++i){
        this->children[i-1] = this->children[i];
    }
    this->children.pop_back();
    return true;
}

bool node::moveCut(CUT_TYPE c, const int* cutLoc, int deltaX, int deltaY){
    node* parent = findParent(c, cutLoc[0], cutLoc[1], cutLoc[2], cutLoc[3]);
    if (parent == NULL) return false;
    int left = cutLoc[0] + deltaX;
    int right = cutLoc[2] + deltaX;
    int bottom = cutLoc[1] + deltaY;
    int top = cutLoc[3] + deltaY;
    int x = -1;
    if (!parent->envelopes(left, bottom, right, top)) return false; //the new coords are outside the parent
    for (int i = 0; i < parent->children.size(); ++i){
        if (parent->children[i]->isSameCut(c, cutLoc[0], cutLoc[1], cutLoc[2], cutLoc[3])){
            x = i;
            continue;
        }
        if (parent->children[i]->overlaps(left, bottom, right, top)){
            //new coords interfere with existing child
            return false;
        }
    }
    if (x == -1) return false; //This is an error
    parent->children[x]->shift(deltaX, deltaY);
    return true;
}

bool node::resizeCut(CUT_TYPE c, const int* cutLoc, const int* deltas){
    node* parent = findParent(c, cutLoc[0], cutLoc[1], cutLoc[2], cutLoc[3]);
    if (parent == NULL) return false;
    int left = cutLoc[0] + deltas[0];
    int bottom = cutLoc[1] + deltas[1];
    int right = cutLoc[2] + deltas[2];
    int top = cutLoc[3] + deltas[3];
    int x = -1;
    if (!parent->envelopes(left, bottom, right, top)) return false; //the new coords are outside the parent
    for (int i = 0; i < parent->children.size(); ++i){
        if (parent->children[i]->isSameCut(c, cutLoc[0], cutLoc[1], cutLoc[2], cutLoc[3])){
            x = i;
            continue;
        }
        if (parent->children[i]->overlaps(left, bottom, right, top)){
            //new coords interfere with existing child
            return false;
        }
    }
    if (x == -1) return false; //This is an error
    parent->children[x]->coords[0] += deltas[0];
    parent->children[x]->coords[1] += deltas[1];
    parent->children[x]->coords[2] += deltas[2];
    parent->children[x]->coords[3] += deltas[3];
    return true;
}


/* 
 * =============================================================================================
 * Alpha Inference Rules
 * =============================================================================================
*/

bool node::doubleCutElimFinder(const int* outerCoords, const int* innerCoords){
    if (this->isSameCut(NOT, outerCoords[0], outerCoords[1], outerCoords[2], outerCoords[3])){
        if (this->atoms.size() != 0) return false;
        for (int i = 0; i < this->children.size(); ++i){
            if (this->children[i]->isSameCut(NOT, innerCoords[0], innerCoords[1], innerCoords[2], innerCoords[3])){
                //We have found the cuts to eliminate :)
                this->removeCut(NOT, innerCoords[0], innerCoords[1], innerCoords[2], innerCoords[3]);
                //we still have to remove the outer cut lol
                return true;
            }
        }
        return false;
    }
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->doubleCutElimFinder(outerCoords, innerCoords)){
            return true;
        }
    }
    return false;
}

bool node::doubleCutElimination(const int* outerCoords, const int* innerCoords){
    if (this->doubleCutElimFinder(outerCoords, innerCoords)){
        this->removeCut(NOT, outerCoords[0], outerCoords[1], outerCoords[2], outerCoords[3]);
        return true;
    }
    return false;
}

node * node::findPlaceToAdd(const atom& a){
    if (a.xCoord() > coords[0] && a.yCoord() > coords[1]
     && a.xCoord() < coords[2] && a.yCoord() < coords[3]){
        //The location of the atom really is inside the bounds of the cut
        node * place = NULL;
        for (int i = 0; i < this->children.size(); ++i){
            place = this->children[i]->findPlaceToAdd(a);
            if (place != NULL){
                return place;
            }
        }
        return this;
    }
    return NULL;
}

bool node::insertAtom(const atom& a){
    node* n = this->findPlaceToAdd(a);
    if (n == NULL) return false;
    if (n->cut != NOT) return false;
    if (n->level % 2 == 0) return false;
    n->addAtom(a);
    return true;
}

node * node::findPlaceToAdd(node * n){
    if (this->envelopes(n)){
        //The other cut is fully contained within this one
        node* place = NULL;
        for (int i = 0; i < this->children.size(); ++i){
            place = this->children[i]->findPlaceToAdd(n);
            if (place != NULL){
                return place;
            }
        }
        return this;
    }
    return NULL;
}

bool node::insertSubgraph(node * n){
    node * place = this->findPlaceToAdd(n);
    if (place == NULL) return false;
    if (n->cut != NOT) return false;
    if (place->level % 2 == 0) return false;
    place->addSubgraph(n);
    return true;
}

node * node::findParent(const atom& a){
    for (int i = 0; i < this->atoms.size(); ++i){
        if (this->atoms[i] == a){
            return this;
        }
    }
    node * par = NULL;
    for (int i = 0; i < this->children.size(); ++i){
        par = this->children[i]->findParent(a);
        if (par != NULL){
            return par;
        }
    }
    return NULL;
}
node * node::findParent(const node * n){
    node * par = NULL;
    for (int i = 0; i < this->children.size(); ++i){
        if (*this->children[i] == *n) return this;
        par = this->children[i]->findParent(n);
        if (par != NULL){
            return par;
        }
    }
    return NULL;
}

node * node::findParent(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    node * par = NULL;
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->isSameCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY)) return this;
        par = this->children[i]->findParent(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
        if (par != NULL){
            return par;
        }
    }
    return NULL;
}

bool node::eraseAtom(const atom& a){
    node * parent = this->findParent(a);
    if (parent == NULL) return false;
    if (parent->cut == BOX) return false;
    if (parent->level % 2 == 1) return false;
    parent->removeAtom(a);
    return true;
}
bool node::eraseSubgraph(const node* n){
    node * parent = this->findParent(n);
    if (parent == NULL) return false;
    if (parent->cut == BOX) return false;
    if (parent->level % 2 == 1) return false;
    parent->removeSubgraph(n);
    return true;
}

bool node::eraseCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    node * parent = this->findParent(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (parent == NULL) return false;
    else if (parent->level % 2 == 1) return false;
    parent->removeCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    return true;
}

bool node::cutBefore(const atom& a){
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->envelopes(a)){
            if (this->children[i]->cut == NOT){
                return true;
            } else {
                return this->children[i]->cutBefore(a);
            }
        }
    }
    return false;
}

bool node::existsAbove(const atom& a){
    //Check if the coordinates of a are within one of the children
    if (!this->cutBefore(a)) return false;

    //if there is a child containing the coords, check if it exists on this level
    for (int i = 0; i < this->atoms.size(); ++i){
        if (this->atoms[i].getName() == a.getName()){
            return true;
        }
    }

    //if it doesnt exist here, recurse
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->existsAbove(a)){
            return true;
        }
    }
    return false;
}

bool node::iterate(const atom& a){
    if (this->existsAbove(a)){
        return this->addAtom(a);
    }
    return false;
}
bool node::deiterate(const atom& a){
    if (this->existsAbove(a)){
        return this->removeAtom(a);
    }
    return false;
}

bool node::cutBefore(const node* n){
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->envelopes(n)){
            if (this->children[i]->cut == NOT){
                return true;
            } else {
                return this->children[i]->cutBefore(n);
            }
        }
    }
    return false;
}

bool node::existsAbove(const node* n){
    //Check if the coordinates of n are within one of the children
    if (!this->cutBefore(n)) return false;

    //check if each child is the same, then recurese to it if not
    for (int i = 0; i < this->children.size(); ++i){
        if (this->children[i]->isSameGraph(n)) return true;
        if (this->children[i]->existsAbove(n)){
            return true;
        }
    }
    return false;
}

bool node::iterate(node* n){
    if (this->existsAbove(n)){
        return this->addSubgraph(n);
    }
    return false;
}
bool node::deiterate(const node* n){
    if (this->existsAbove(n)){
        return this->removeSubgraph(n);
    }
    return false;
}

/* 
 * =============================================================================================
 * Gamma Inference Rules
 * =============================================================================================
*/

bool node::kJoin(const int* cut1, const int* cut2, const int* newCut){
    node * parent = this->findParent(BOX, cut1[0], cut1[1], cut1[2], cut1[3]);
    if (!parent->envelopes(newCut[0], newCut[1], newCut[2], newCut[3])){
        return false;
    }
    int y;
    int x = -1;
    for (int i = 0; i < parent->children.size(); ++i){
        if (parent->children[i]->isSameCut(BOX, cut2[0], cut2[1], cut2[2], cut2[3])){
            x = i;
        }
        if (parent->children[i]->isSameCut(BOX, cut1[0], cut1[1], cut1[2], cut1[3])){
            y = i;
        }
    }
    if (x == -1) return false;
    node * thing2Add = new node(BOX, newCut[0], newCut[1], newCut[2], newCut[3]);
    //check if the new cut interferes with other stuff
    for (int i = 0; i < parent->children.size(); ++i){
        if (i == x || i == y){
            //one of the cuts to be replaced
            continue;
        }
        if (parent->children[i]->overlaps(thing2Add) || thing2Add->envelopes(parent->children[i])){
            delete(thing2Add);
            return false;
        }
    }
    for (int i = 0; i < parent->atoms.size(); ++i){
        if (thing2Add->envelopes(parent->atoms[i])){
            delete(thing2Add);
            return false;
        }
    }

    //add stuff from other nodes to new node
    for (int i = 0; i < parent->children[x]->children.size(); ++i){
        thing2Add->addSubgraph(parent->children[x]->children[i]);
    }
    for (int i = 0; i < parent->children[x]->atoms.size(); ++i){
        thing2Add->addAtom(parent->children[x]->atoms[i]);
    }
    for (int i = 0; i < parent->children[y]->children.size(); ++i){
        thing2Add->addSubgraph(parent->children[y]->children[i]);
    }
    for (int i = 0; i < parent->children[y]->atoms.size(); ++i){
        thing2Add->addAtom(parent->children[y]->atoms[i]);
    }
    //remove child pointers from nodes to be deleted:
    while (parent->children[x]->children.size() > 0){
        parent->children[x]->children.pop_back();
    }
    while (parent->children[y]->children.size() > 0){
        parent->children[y]->children.pop_back();
    }

    parent->removeSubgraph(parent->children[x]);
    parent->removeSubgraph(parent->children[y]);

    if (!parent->addSubgraph(thing2Add)){
        std::cerr << "kjoin Error" <<std::endl;
        delete(thing2Add);
        return false;
    }
    return true;
}