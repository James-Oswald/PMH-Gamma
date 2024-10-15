#include "node.h"

/*
    std::vector<node> children;
    std::vector<std::string> atoms;
    CUT_TYPE cut;
*/

node::node(){
    children = std::vector<node*>();
    atoms = std::vector<atom>();
    cut = TOP;
    coords[0] = std::numeric_limits<int>::min();
    coords[1] = std::numeric_limits<int>::min();
    coords[2] = std::numeric_limits<int>::max();
    coords[3] = std::numeric_limits<int>::max();
}

node::node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    children = std::vector<node*>();
    atoms = std::vector<atom>();
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

bool const node::envelopes(const node * n) const{
    return (n->coords[0] > this->coords[0] && n->coords[1] > this->coords[1]
     && n->coords[2] < this->coords[2] && n->coords[3] < this->coords[3]);
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