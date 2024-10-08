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
    std::vector<node*> gCh = g.root.getChildren();
    for(int i = 0; i < gCh.size(); ++i){
        if (!this->root.addSubgraph(gCh[i])){
            //idk what to do but this is an error
        }
    }
    std::vector<atom> gAt = g.root.getAtoms();
    for(int i = 0; i < gAt.size(); ++i){
        if (!this->root.addAtom(gAt[i])){
            //idk what to do but this is an error
        }
    }
    return true;
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