#include "node.h"


node::node(){
    children = std::set<node*, nodeGreater>();
    atoms = std::set<atom>();
    cut = TOP;
    coords[0] = std::numeric_limits<int>::min();
    coords[1] = std::numeric_limits<int>::min();
    coords[2] = std::numeric_limits<int>::max();
    coords[3] = std::numeric_limits<int>::max();
}

node::node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    children = std::set<node*, nodeGreater>();
    atoms = std::set<atom>();
    cut = c;
    if (bottomLeftX >= topRightX || bottomLeftY >= topRightY){
        //TODO: This is an error. Figure out what to do here
    }
    coords[0] = bottomLeftX;
    coords[1] = bottomLeftY;
    coords[2] = topRightX;
    coords[3] = topRightY;
}

void node::updateLevel(int l){
    this->level = l;
    for (std::set<node*>::const_iterator it = this->children.begin(); it != this->children.end(); ++it){
        (*it)->updateLevel(l+1);
    }
}

bool const node::contains(const atom& a) const{
    if (atoms.count(a) == 1){
        return true;
    }
    for (std::set<node*>::const_iterator it = this->children.begin(); it != this->children.end(); ++it){
        if ((*it)->contains(a)){
            return true;
        }
    }
    return false;
}

bool const node::envelopes(const node * n) const{
    return (n->coords[0] > this->coords[0] && n->coords[1] > this->coords[1]
     && n->coords[2] < this->coords[2] && n->coords[3] < this->coords[3]);
}
//----------------------------------------------------------------------------------------------------------------------------------
//Comparators

bool node::operator==(const node& other) const{
    if (this->level != other.level){
        return false;
    }
    for (int i = 0; i < 4; ++i){
        if (this->coords[i] != other.coords[i]){
            return false;
        }
    }
    return true;
}
/*
bool node::operator==(const node& other) const{
    if (this->cut != other.cut || this->level != other.level || this->atoms.size() != other.atoms.size() || this->children.size() != other.children.size()){
        return false;
    }
    for (int i = 0; i < 4; ++i){
        if (this->coords[i] != other.coords[i]){
            return false;
        }
    }
    std::set<atom>::iterator tAtIt = this->atoms.begin();
    std::set<atom>::iterator oAtIt = other.atoms.begin();
    while (tAtIt != this->atoms.end()){
        if ((*tAtIt) != (*oAtIt)){
            return false;
        }
        tAtIt++;
        oAtIt++;
    }
    std::set<node*>::iterator tChIt = this->children.begin();
    std::set<node*>::iterator oChIt = other.children.begin();
    while (tChIt != this->children.end()){
        if (!((**tChIt) == (**oChIt))){
            return false;
        }
    }
    return true;
}
*/

bool node::operator<(const node& other) const{
    //compare bounding boxes
    if (other.envelopes(this)){
        return true;
    } else if (this->envelopes(&other)) {
        return false;
    } else if (this->coords[0] == other.coords[0] && this->coords[1] == other.coords[1]
            && this->coords[2] == other.coords[2] && this->coords[3] == other.coords[3]) {
        //then check if one is at a lower level than the other
        if (this->level == other.level){
            return false;
        } else {
            return this->level < other.level;
        }
    } else {
        for (int i = 0; i < 4; ++i){
            if (this->coords[i] < other.coords[i]){
                return true;
            }
        }
        return false;
    }
}
/*
bool node::operator<(const node& other) const{
    //first compare bounding boxes
    if (other.envelopes(this)){
        return true;
    } else if (this->envelopes(&other)) {
        return false;
    } else if (this->coords[0] == other.coords[0] && this->coords[1] == other.coords[1]
            && this->coords[2] == other.coords[2] && this->coords[3] == other.coords[3]) {
        //then check if one is at a lower level than the other
        if (this->level == other.level){
            //compare number of atoms and children
            if (this->atoms.size() + this->children.size() == other.atoms.size() + other.atoms.size()){
                //compare individual atoms
                std::set<atom>::iterator tAtIt = this->atoms.begin();
                std::set<atom>::iterator oAtIt = other.atoms.begin();
                while (tAtIt != this->atoms.end()){
                    if ((*tAtIt) == (*oAtIt)){
                        continue;
                    } else if ((*tAtIt) < (*oAtIt)){
                        return true;
                    } else {
                        return false;
                    }
                    tAtIt++;
                    oAtIt++;
                }

                //i really don't want to compare indivitual nodes because that will make this operation incredibly expensive.

            } else {
                return (this->atoms.size() + this->children.size() < other.atoms.size() + other.atoms.size());
            }
        } else {
            return this->level < other.level;
        }
    } else {
        for (int i = 0; i < 4; ++i){
            if (this->coords[i] < other.coords[i]){
                return true;
            }
        }
        return false;
    }
}
*/

//----------------------------------------------------------------------------------------------------------------------------------
//Editors
bool const node::addAtom(const atom& a){
    if (a.xCoord() > coords[0] && a.yCoord() > coords[1]
     && a.xCoord() < coords[2] && a.yCoord() < coords[3]){
        //The location of the atom really is inside the bounds of the cut
        bool found = false;
        for (std::set<node*>::iterator it = this->children.begin(); it != this->children.end(); ++it){
            if ((*it)->addAtom(a)){
                found = true;
                break;
            }
        }
        if (!found)
            atoms.insert(a);
        return true;
    }
    return false;
}

bool const node::addSubgraph(node * n){
    if (this->envelopes(n)){
        //The other cut is fully contained within this one
        bool found = false;
        for (std::set<node*>::iterator it = this->children.begin(); it != this->children.end(); ++it){
            if ((*it)->addSubgraph(n)){
                found = true;
                break;
            }
        }
        if (!found) {
            children.insert(n);
            n->updateLevel(this->level + 1);
        }
        return true;
    }
    return false;
}

bool const node::removeAtom(const atom& a){
    return false;
}