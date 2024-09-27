#include "graph.h"

graph::graph(){
    root = node();
}

graph::graph(std::string s){
    root = node();
    for (int i = 0; i < s.length(); ++i){
        
    }
}

node const graph::createSubgraphFromString(std::string s){
    node n;
    int len = s.length() - 2;
    //initialize node with cut type
    if (s[0] == '(') n = node(NOT);
    else if (s[0] == '[') n = node(BOX);
    else {
        n = node(TOP);
        len += 1; // the last character is not a paren for this node
    }
    int firstChild = NULL; //Index of the open paren for the first child in s
    std::string atom = "";
    for (int i = 1; i < len; ++i){
        if (s[i] == '(' || s[i] == '['){
            firstChild = i;
        } else if (s[i] == ')'){
            if (s[0] == '(') {
                //we are done
                break;
            } else {
                //ERROR CASE
                //TODO: figure out what to do in case of error
            }
        } else if (s[i] == ']'){
            if (s[0] == '[') {
                break;
            } else {
                //ERROR CASE
                //TODO: figure out what to do in case of error
            }
        } else if (s[i] == ' ') {
            if (s[i-1] == ' ' || s[i-1] == '(' || s[i-1] == '['){
                //ERROR CASE
                //TODO: figure out what to do in case of error
            } else {
                n.addAtom(atom);
                atom = "";
            }
        } else {
            atom.push_back(s[i]);
        }
    }

    //TODO: Write loop to do children



}

std::string const graph::getSubgraphText(node n){
    std::string  ret = "";
    //check for empty node
    if (n.isEmpty()) return "";
    //place correct paren at front
    if (n.cut() == BOX) ret += "[";
    else if (n.cut() == NOT) ret += "(";
    //write atoms
    std::vector<std::string> atoms = n.getAtoms();
    for (int i = 0; i < atoms.size(); ++i){
        ret += atoms[i];
        if (i != atoms.size()-1) ret += " ";
    }
    //write children
    std::vector<node> children = n.getChildren();
    for (int i = 0; i < children.size(); ++i){
        ret += getSubgraphText(children[i]);
        if (i != children.size()-1) ret += " ";
    }
    //place correct paren at end
    if (n.cut() == BOX) ret += "]";
    if (n.cut() == NOT) ret += ")";
    return ret;
}

std::string const graph::text(){
    return getSubgraphText(this->root);
}