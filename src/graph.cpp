#include "graph.h"

graph::graph(){
    root = node();
}

//for making smaller graphs
graph::graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    root = node(TOP, bottomLeftX, bottomLeftY, topRightX, topRightY);
}

bool graph::insert(atom a){
    return root.addAtom(a);
}

bool graph::insert(graph g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    std::set<node*, nodeGreater> gCh = g.root.getChildren();
    for(std::set<node*>::iterator it = gCh.begin(); it != gCh.end(); ++it){
        if (!this->root.addSubgraph(*it)){
            //idk what to do but this is an error
        }
    }
    std::set<atom> gAt = g.root.getAtoms();
    for(std::set<atom>::iterator it = gAt.begin(); it != gAt.end(); ++it){
        if (!this->root.addAtom(*it)){
            //idk what to do but this is an error
        }
    }
    return true;
}

bool graph::remove(atom a){
    return false;
}
bool remove(graph g);









std::string const getSubgraphText(node * n){
    std::string  ret = "";
    //check for empty node
    if (n->isEmpty()) return "";
    //place correct paren at front
    if (n->cutType() == BOX) ret += "[";
    else if (n->cutType() == NOT) ret += "(";
    //write atoms
    std::set<atom> atoms = n->getAtoms();
    int i = 0;
    for (std::set<atom>::iterator it = atoms.begin(); it != atoms.end(); ++it){
        ret += it->getName();
        if (i != atoms.size()-1) ret += " ";
        ++i;
    }
    //write children
    i = 0;
    std::set<node*, nodeGreater> children = n->getChildren();
    for (std::set<node*, nodeGreater>::iterator it = children.begin(); it != children.end(); ++it){
        ret += getSubgraphText(*it);
        if (i != children.size()-1) ret += " ";
        ++i;
    }
    //place correct paren at end
    if (n->cutType() == BOX) ret += "]";
    if (n->cutType() == NOT) ret += ")";
    return ret;
}

std::string const graph::text(){
    return getSubgraphText(&root);
}