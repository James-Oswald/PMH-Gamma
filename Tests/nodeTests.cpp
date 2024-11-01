#include <iostream>
#include <cassert>

#include "../src/node.h"
#include "../src/graph.h"

int main(){
    //Testing destructor
    node* ohio = new node();
    delete(ohio);

    //more thourogh testing of destructor
    ohio = new node();
    ohio->addAtom(atom("nothing", 0, 0));
    ohio->addSubgraph(new node(BOX, 10, 10, 20, 20));
    node* kansas = new node(BOX, 11, 11, 19, 19);
    ohio->addSubgraph(kansas);
    delete(ohio);



    node* root = new node();
    assert(root->contains(root));
    if (root->cutType() != TOP){
        std::cout << "ERROR: node defualt constructor\n";
        return -1;
    }
    node* cut = new node(NOT, 0, 0, 10, 10);
    node* boxCut = new node(BOX, -500, -500, 230, 456);
    if (!root->isEmpty() || !cut->isEmpty() || !boxCut->isEmpty()){
        std::cout << "ERROR: node isEmpty\n";
        return -1;
    }

    atom a = atom("apple", 1, 1);
    atom b = atom("badger", -400, 36);
    atom c = atom("cat", 12, 13);
    atom d = atom("dog", -400, 400);

    //testing add atom
    assert(cut->addAtom(a));
    assert(root->addAtom(c));
    assert(boxCut->addAtom(d));
    assert(!cut->addAtom(b));

    //testing add subgraph
    assert(!cut->addSubgraph(boxCut));
    assert(root->addSubgraph(boxCut));

    //Checking that edits to subgraphs are reflected in the root
    assert(boxCut->addSubgraph(cut));
    assert(root->contains(a));

    //Tesing that insert adds down a level:
    atom e = atom("egret", 6, 6);
    assert(root->addAtom(e));
    assert(cut->contains(e));

    std::cout << getSubgraphText(root) << std::endl;


    //Testing that remove works
    assert(root->removeSubgraph(cut)); //cut should have been deleted after this
    assert(!root->contains(e));
    assert(root->removeAtom(d));
    assert(!boxCut->contains(d));

    //Testing that removeCut works
    node* newCut = new node(NOT, 0, 0, 10, 10);
    node* tinyCut = new node(NOT, 1, 1, 2, 2);
    assert(newCut->addAtom(e));
    assert(newCut->addSubgraph(tinyCut));
    assert(root->addSubgraph(newCut));
    assert(!root->removeCut(TOP, 0, 0, 10, 10));
    assert(root->removeCut(NOT, 0, 0, 10, 10));
    assert(root->contains(e));
    assert(root->contains(tinyCut));


    //Testing adding empty graphs
    node* alpha = new node(TOP, -10, -10, 10, 10);
    node* beta = new node(NOT, -9, -9, 9, 9);
    node* gamma = new node(BOX, -8, -8, 8, 8);
    node* kappa = new node(NOT, -7, -7, 7, 7);

    assert(alpha->addSubgraph(beta));
    assert(alpha->addSubgraph(gamma));
    assert(alpha->addSubgraph(kappa));
    assert(alpha->contains(beta));
    assert(beta->contains(kappa));

    //Testing copy constructor:
    node * alphaPrime = new node(*alpha);
    assert(alphaPrime->contains(NOT, -7, -7, 7, 7));

    //Testing contains Node
    beta = new node(NOT, -9, -9, 9, 9);
    gamma = new node(BOX, -8, -8, 8, 8);
    kappa = new node(NOT, -7, -7, 7, 7);

    assert(beta->addSubgraph(gamma));
    assert(beta->addSubgraph(kappa));
    assert(beta->contains(kappa));

    assert(alpha->contains(beta));

    //cleanup
    delete(root);
    delete(alpha);
    delete(alphaPrime);
    delete(beta);

    std::cout << "Tests Ran Sucessfully\n";
    return 0;
}
