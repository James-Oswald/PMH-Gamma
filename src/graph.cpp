#include "graph.h"


#include <iostream>
graph::graph(){
    root = node();
    numCuts = 0;
}

//for making smaller graphs
graph::graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    root = node(TOP, bottomLeftX, bottomLeftY, topRightX, topRightY);
    numCuts = 0;
}

graph::graph(const graph&){
    root = node();
    numCuts = 0;
    std::cerr << "\n-------------------------------------\nTHIS SHOULD NEVER BE CALLED YOU FOOL!\n-------------------------------------" << std::endl;
}

bool graph::removeFromCuts(const node& n){
    int x = -1;
    for (int i = 0; i < numCuts; ++i){
        if (this->cuts[i].operator==(n)){
            x = i;
            break;
        }
    }
    if (x == -1){
        //Node not found
        return false;
    }
    for (int i = x+1; i < numCuts; ++i){
        this->cuts[i-1] = this->cuts[i];
    }
    --numCuts;
    return true;
}

bool graph::removeFromCuts(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    int x = -1;
    for (int i = 0; i < numCuts; ++i){
        if (this->cuts[i].isSameCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY)){
            x = i;
            break;
        }
    }
    if (x == -1){
        //Node not found
        return false;
    }
    for (int i = x+1; i < numCuts; ++i){
        this->cuts[i-1] = this->cuts[i];
    }
    --numCuts;
    return true;
}

bool graph::addToCuts(const node& n){
    if (numCuts == CUT_LIMIT) return false;
    cuts[numCuts] = n;
    ++numCuts;
    return true;
}

bool graph::contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const{
    return this->root.contains(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
}

bool graph::contains(const graph& g) const{
    std::cout << "checking to see if " << this->text() << " contains " << g.text() << std::endl;
    //Need to check to see if all of the children of g.root are there
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->root.contains(gCh[i])) {
            std::cout << getSubgraphText(gCh[i]) << " was not found\n";
            return false;
        }
    }
    std::cout << "-2" << std::endl;
    //then check if all of the atoms of g.root are there
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.contains(gAt[i])) return false;
    }
    std::cout << "-3" << std::endl;
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
    if (!this->addToCuts(n)) return false;
    bool ret = this->root.addSubgraph(&cuts[numCuts-1]);
    if (!ret){
        --numCuts;
    }
    return ret;
}

bool graph::insert(const graph& g){
    if (!this->root.envelopes(&g.root)){
        return false;
    }
    std::vector<node*> gCh = g.root.getChildren();
    for (int i = 0; i < gCh.size(); ++i){
        if (!this->addToCuts( *gCh[i])) return false;
        if (!this->root.addSubgraph(&this->cuts[numCuts-1])){
            //error
            std::cerr << "Graph insert error node" << std::endl;
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
            std::cerr << "Graph removal Error1\n";
            return false;
        }
        if (!this->removeFromCuts(*gCh[i])){
            //THIS IS AN ERROR:
            std::cerr << "Graph removal Error2\n";
            return false;
        }
    }
    //then remove the atoms
    std::vector<atom> gAt = g.root.getAtoms();
    for (int i = 0; i < gAt.size(); ++i){
        if (!this->root.removeAtom(gAt[i])) {
            //this is an error
            std::cerr << "Graph removal Error3\n";
            return false;
        }
    }

    return true;
}

bool graph::remove(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY){
    bool ret = this->root.removeCut(c, bottomLeftX, bottomLeftY, topRightX, topRightY);
    if (ret){
        if (!this->removeFromCuts(c, bottomLeftX, bottomLeftY, topRightX, topRightY)){
            //BIG ERROR MOMENT
            std::cerr << "SEGFAULT INCOMING LOL" << std::endl;
        }
    }
    return ret;
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