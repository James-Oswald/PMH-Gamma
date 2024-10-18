#include "graph.h"


#include <iostream>
graph::graph(){
    root = node();
    cuts = std::vector<node>();
}

//for making smaller graphs
graph::graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    root = node(TOP, bottomLeftX, bottomLeftY, topRightX, topRightY);
    cuts = std::vector<node>();
}

void graph::removeFromCuts(node n){
    int x = -1;
    for (int i = 0; i < this->cuts.size(); ++i){
        if (this->cuts[i] == n){
            x = i;
            break;
        }
    }
    if (x == -1){
        //THIS IS AN ERROR
        std::cerr << "PREPARE FOR SEGFAULT :)" << std::endl;
    }
    for (int i = x+1; i < this->cuts.size(); ++i){
        this->cuts[i-1] = this->cuts[i];
    }
    this->cuts.pop_back();
}

bool graph::contains(graph g) const{
    //Need to check to see if all of the children of g.root are removable
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.contains(gCh[i])) return false;
    }
    //then check if all of the atoms of g.root are removable
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.contains(gAt[i])) return false;
    }
    return true;
}

bool graph::insert(std::string s, int x, int y){
    return root.addAtom(atom(s, x, y));
}

bool graph::insert(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    node n = node(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (!this->root.envelopes(&n)){
        return false;
    }
    bool ret = this->root.addSubgraph(&n);
    if (ret){
        cuts.push_back(n);

        //This MAY cause an error (if cuts.pushback(n) calls the node copy constructor)
    }
    return ret;
}

bool graph::insert(graph g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    for (int i = 0; i < g.cuts.size(); ++i){
        this->cuts.push_back(g.cuts[i]);
        this->root.addSubgraph(&this->cuts[this->cuts.size()-1]);
    }
    std::vector<atom> gAt = g.root.getAtoms();
    for(int i = 0; i < gAt.size(); ++i){
        if (!this->root.addAtom(gAt[i])){
            //idk what to do but this is an error
        }
    }
    return true;
}


bool graph::remove(std::string s, int x, int y){
    return this->root.removeAtom(atom(s, x, y));
}
bool graph::remove(graph g){
    //make sure it is removable
    if (!this->contains(g)) return false;

    //remove the children
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.removeSubgraph(gCh[i])) {
            //this is an error
            std::cerr << "Graph removal Error\n";
        }
        this->removeFromCuts(*gCh[i]);
    }
    //then remove the atoms
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.removeAtom(gAt[i])) {
            //this is an error
            std::cerr << "Graph removal Error\n";
        }
    }

    return true;
}

bool graph::remove(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    bool ret = this->root.removeCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (ret){
        //TODO: change this to be in a helper function:
        int x = -1;
        for (int i = 0; i < this->cuts.size(); ++i){
            if (this->cuts[i].isSameCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY)){
                x = i;
                break;
            }
        }
        if (x == -1){
            //THIS IS AN ERROR
            std::cerr << "PREPARE FOR SEGFAULT :)" << std::endl;
        }
        for (int i = x+1; i < this->cuts.size(); ++i){
            this->cuts[i-1] = this->cuts[i];
        }
        this->cuts.pop_back();
        //----------------------------------------------
    }
    return ret;
}



std::string const getSubgraphText(node * n){
    std::string  ret = "";
    //check for empty node
    if (n->isEmpty()) return "";
    //place correct paren at front
    if (n->cutType() == BOX) ret += "[";
    else if (n->cutType() == NOT) ret += "(";
    //write atoms
    std::vector<atom> atoms = n->getAtoms();
    for (int i = 0; i < atoms.size(); ++i){
        ret += atoms[i].getName();
        if (i != atoms.size()-1) ret += " ";
    }
    //write children
    std::vector<node*> children = n->getChildren();
    for (int i = 0; i < children.size(); ++i){
        ret += getSubgraphText(children[i]);
        if (i != children.size()-1) ret += " ";
    }
    //place correct paren at end
    if (n->cutType() == BOX) ret += "]";
    if (n->cutType() == NOT) ret += ")";
    return ret;
}

std::string const graph::text(){
    return getSubgraphText(&root);
}