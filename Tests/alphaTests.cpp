#include <iostream>
#include <cassert>

#include "../src/graph.h"

int main() {

    //"Build Mode"
    graph implication = graph();
    assert(implication.insert("A", -10, 10));
    assert(implication.insert(NOT, 0, 0, 6, 6));
    assert(implication.insert("A", 1, 3));
    assert(implication.insert(NOT, 3, 1, 5, 5));
    assert(implication.insert("B", 4, 3));
    assert(implication.text() == "A(A(B))");

    //Testing deiterate
    assert(implication.deiteration("A", 1, 3));
    assert(implication.text() == "A((B))");

    //Testing double Cut Removal
    int coords1[4] = {0, 0, 6, 6};
    int coords2[4] = {3, 1, 5, 5};
    assert(implication.doubleCutElimination(coords1, coords2));
    assert(implication.text() == "A B");

    //Now reverse the process using inference rules:
    assert(implication.doubleCutIntroduction(coords1, coords2));
    assert(implication.iteration("A", 1, 3));
    assert(implication.text() == "A(A(B))");

    //should not be able to remove cut with thing between:
    assert(!implication.doubleCutElimination(coords1, coords2));

    //should not be able to iterate nor deiterate without higher thing
    assert(!implication.iteration("A", -99, -99));
    assert(!implication.deiteration("A", -10, 10));
    assert(!implication.iteration("B", 4, 2));
    assert(!implication.deiteration("A", 4, 3));


    //"Build Mode"
    graph biig = graph();
    assert(biig.insert(NOT, -99, -99, 99, 99));
    assert(biig.insert(NOT, 50, 50, 98, 98));
    assert(biig.insert("For", 60, 60));
    assert(biig.insert("While", 70, 70));

    //Testing insertion
    assert(biig.insertion("A", 0, 0));
    assert(!biig.insertion("A", 51, 51));

    //Testing eraseure
    assert(biig.erasure("For", 60, 60));
    assert(!biig.erasure("A", 0, 0));

    //TODO: test these using graphs instead of just atoms
}