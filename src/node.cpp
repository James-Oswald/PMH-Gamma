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
        std::cout << "kill yourself" << std::endl;
    }
    coords[0] = bottomLeftX;
    coords[1] = bottomLeftY;
    coords[2] = topRightX;
    coords[3] = topRightY;
}

node::node(const node& n){
    this->children = std::vector<node*>(n.children.size());
    for (int i = 0; i < n.children.size(); ++i){
        this->children[i] = n.children[i];
    }
    this->atoms = n.atoms;
    this->cut = n.cut;
    this->level = n.level;
    for (int i = 0; i < 4; ++i){
        this->coords[i] = n.coords[i];
    }
}

void node::updateLevel(int l){
    this->level = l;
    for (int i = 0; i < this->children.size(); ++i){
        this->children[i]->updateLevel(l+1);
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
        if (*this->children[i] == *n) return true;
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

bool const node::isSameCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const{
    return (this->cut == c && this->coords[0] == bottomLeftX && this->coords[1] == bottomLeftY
            && this->coords[2] == topRightX && this->coords[3] == topRightY);
}

bool const node::isSameCut(const node* n) const{
    return isSameCut(n->cut, n->coords[0], n->coords[1], n->coords[2], n->coords[3]);
}


bool node::operator==(const node& other) const{
    if (this->cut != other.cut || this->level != other.level || this->atoms.size() != other.atoms.size() || this->children.size() != other.children.size()){
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
        if (this->children[i] != other.children[i]){
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
        bool found = false;
        for (int i = 0; i < this->children.size(); ++i){
            found = (*this->children[i]).removeSubgraph(n);
        }
        return found;
    }
    for (int i = x+1; i < this->children.size(); ++i){
        this->children[i-1] = this->children[i];
    }
    this->children.pop_back();
    return true;
}