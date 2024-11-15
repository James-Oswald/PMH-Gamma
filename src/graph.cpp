#include "graph.h"


#include <iostream>
graph::graph(){
    root = node();
}

//for making smaller graphs
graph::graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    root = node(TOP, bottomLeftX, bottomLeftY, topRightX, topRightY);
}

graph::graph(const graph&){
    root = node();
    std::cerr << "Graph copy constructor called when shouldn't be" << std::endl;
}

bool graph::contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const{
    return this->root.contains(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
}

bool graph::contains(const graph& g) const{
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    //Need to check to see if all of the children of g.root are there
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.contains(gCh[i])) {
            return false;
        }
    }
    //then check if all of the atoms of g.root are there
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
    node* n = new node(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (!this->root.envelopes(n)){
        delete(n);
        return false;
    }
    bool ret = this->root.addSubgraph(n);
    if (!ret){
        delete(n);
    }
    return ret;
}

bool graph::insert(const graph& g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    node* newNode;
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        newNode = new node(*gCh[i]);
        if (!this->root.addSubgraph(newNode)){
            //error
            std::cerr << "Graph insert error node" << std::endl;
            delete(newNode);
        }
    }
    std::vector<atom> gAt = g.root.getAtoms();
    for(int i = 0; i < gAt.size(); ++i){
        if (!this->root.addAtom(gAt[i])){
            //idk what to do but this is an error
            std::cerr << "Graph insert error atom" << std::endl;
        }
    }
    return true;
}


bool graph::remove(std::string s, int x, int y){
    return this->root.removeAtom(atom(s, x, y));
}
bool graph::remove(const graph& g){
    //make sure it is removable
    if (!this->contains(g)) return false;

    //remove the children
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.removeSubgraph(gCh[i])) {
            //this is an error
            std::cerr << "Graph removal Error node\n";
            return false;
        }
    }
    //then remove the atoms
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.removeAtom(gAt[i])) {
            //this is an error
            std::cerr << "Graph removal Error atom\n";
            return false;
        }
    }

    return true;
}

bool graph::remove(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    return this->root.removeCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
}

bool graph::moveCut(CUT_TYPE c, const int* cutLoc, int deltaX, int deltaY){
    return this->root.moveCut(c, cutLoc, deltaX, deltaY);
}

bool graph::resizeCut(CUT_TYPE c, const int* cutLoc, const int* deltas){
    return this->root.resizeCut(c, cutLoc, deltas);
}

/* 
 * =============================================================================================
 * Alpha Inference Rules
 * =============================================================================================
*/
bool graph::doubleCutElimination(const int* outerCoords, const int* innerCoords){
    return this->root.doubleCutElimination(outerCoords, innerCoords);
}
bool graph::doubleCutIntroduction(const int* outerCoords, const int* innerCoords){
    node* cuts = new node(NOT, outerCoords[0], outerCoords[1], outerCoords[2], outerCoords[3]);
    cuts->addSubgraph(new node(NOT, innerCoords[0], innerCoords[1], innerCoords[2], innerCoords[3]));
    if (!this->root.addSubgraph(cuts)){
        delete(cuts);
        return false;
    }
    return true;
}

//These are just like insert except they require the position to be on an odd level
bool graph::insertion(std::string s, int x, int y){
    return this->root.insertAtom(atom(s, x, y));
}
bool graph::insertion(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    node* n = new node(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (!this->root.envelopes(n)){
        delete(n);
        return false;
    }
    bool ret = this->root.insertSubgraph(n);
    if (!ret){
        delete(n);
    }
    return ret;
}
bool graph::insertion(const graph& g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    if (!this->root.onLevel(&g.root, 1)) return false;
    node* newNode;
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        newNode = new node(*gCh[i]);
        if (!this->root.insertSubgraph(newNode)){
            //error
            std::cerr << "Graph insertion error node" << std::endl;
            delete(newNode);
        }
    }
    std::vector<atom> gAt = g.root.getAtoms();
    for(int i = 0; i < gAt.size(); ++i){
        if (!this->root.insertAtom(gAt[i])){
            //idk what to do but this is an error
            std::cerr << "Graph insertion error atom" << std::endl;
        }
    }
    return true;
}

//These are just like remove excpet they require the position to be on an even level
bool graph::erasure(std::string s, int x, int y){
    return this->root.eraseAtom(atom(s, x, y));
}
bool graph::erasure(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    return this->root.eraseCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
}
bool graph::erasure(const graph& g){
    //make sure it is removable
    if (!this->contains(g)) return false;
    if (!this->root.onLevel(&g.root, 0)) return false;

    //remove the children
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.eraseSubgraph(gCh[i])) {
            //this is an error
            std::cerr << "Graph erasure Error node\n";
            return false;
        }
    }
    //then remove the atoms
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.eraseAtom(gAt[i])) {
            //this is an error
            std::cerr << "Graph erasure Error atom\n";
            return false;
        }
    }

    return true;
}


bool graph::iteration(std::string s, int x, int y){
    return this->root.iterate(atom(s, x, y));
}
bool graph::iteration(const graph& g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    if (!this->root.withinSameCut(&g.root)) return false;
    node* newNode;
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        newNode = new node(*gCh[i]);
        if (!this->root.iterate(newNode)){
            //error
            std::cerr << "Graph iteration error node" << std::endl;
            delete(newNode);
        }
    }
    std::vector<atom> gAt = g.root.getAtoms();
    for(int i = 0; i < gAt.size(); ++i){
        if (!this->root.iterate(gAt[i])){
            //idk what to do but this is an error
            std::cerr << "Graph iteration error atom" << std::endl;
        }
    }
    return true;
}

bool graph::deiteration(std::string s, int x, int y){
    return this->root.deiterate(atom(s, x, y));
}
bool graph::deiteration(const graph& g){
    //make sure it is removable
    if (!this->contains(g)) return false;
    if (!this->root.withinSameCut(&g.root)) return false;
    //remove the children
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.deiterate(gCh[i])) {
            //this is an error
            std::cerr << "Graph deiteration Error Node\n";
            return false;
        }
    }
    //then remove the atoms
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.deiterate(gAt[i])) {
            //this is an error
            std::cerr << "Graph deiteration Error Atom\n";
            return false;
        }
    }

    return true;
}




std::string const getSubgraphText(const node * n){
    std::string  ret = "";
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


std::string const graph::text() const{
    return getSubgraphText(&root);
}