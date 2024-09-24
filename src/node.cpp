#include "node.h"

/*
    std::vector<node> children;
    std::vector<std::string> atoms;
    CUT_TYPE cut;
*/

node::node(){
    children = std::vector<node>();
    atoms = std::vector<std::string>();
    cut = TOP;
}

node::node(CUT_TYPE c){
    children = std::vector<node>();
    atoms = std::vector<std::string>();
    cut = c;
}

std::vector<std::string> const node::getAtoms(){
    return atoms;
}