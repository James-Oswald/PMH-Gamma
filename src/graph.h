#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <iterator>
#include <set>

/*
 * This class is represented as a tree of nodes.
 * Each level of the tree is seperated by one cut from the previous level.
 * 
 * This representation DOES NOT check for overlap in insertions.
 * That is assumed to be done on the UI end.
*/
class graph
{
private:
    node root;


public:
    graph();
    //for making smaller graphs
    graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    graph(const graph&);

    std::string const text() const;

    bool isEmpty() const {return this->root.isEmpty(); }

    bool contains(std::string s, int x, int y) const { return this->root.contains(atom(s, x, y)); }
    bool contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;
    bool contains(const graph& g) const;

    // EDITING COMMANDS
    bool insert(std::string s, int x, int y);
    bool insert(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    bool insert(const graph& g);

    bool remove(std::string s, int x, int y);
    bool remove(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    bool remove(const graph& g);

    bool moveCut(CUT_TYPE c, const int* cutLoc, int deltaX, int deltaY);
    bool resizeCut(CUT_TYPE c, const int* cutLoc, const int* deltas); //deltas is the ammount to change each coordinate by [lowX, lowY, upX, upY]

    // PROOF INFERENCE RULES
    // alpha ir:
    bool doubleCutElimination(const int* outerCoords, const int* innerCoords);
    bool doubleCutIntroduction(const int* outerCoords, const int* innerCoords);

    //These are just like insert except they require the position to be on an odd level
    bool insertion(std::string s, int x, int y);
    bool insertion(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    bool insertion(const graph& g);

    //These are just like remove excpet they require the position to be on an even level
    bool erasure(std::string s, int x, int y);
    bool erasure(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    bool erasure(const graph& g);

    bool iteration(std::string s, int x, int y);
    bool iteration(const graph& g);

    bool deiteration(std::string s, int x, int y);
    bool deiteration(const graph& g);

    //gamma ir:
};

//returns the string representation of the subgraph headed by n
std::string const getSubgraphText(const node * n);

#endif