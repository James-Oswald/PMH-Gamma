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
    //THERE IS A HARD CUT LIMIT:
    const static int CUT_LIMIT = 100;
    node cuts[CUT_LIMIT];
    int numCuts;

    bool removeFromCuts(const node& n);
    bool removeFromCuts(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    bool addToCuts(const node& n);

public:
    graph();
    //for making smaller graphs
    graph(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    graph(const graph&);

    std::string const text() const;

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

    // PROOF INFERENCE RULES
    // alpha ir:
    void doubleCutElimination();
    void doubleCutIntroduction();

    void insertion();

    void erasure();

    void iteration();
    void deiteration();

    //gamma ir:
};

//returns the string representation of the subgraph headed by n
std::string const getSubgraphText(const node * n);



/*
    This will perhaps be useful for the graphic interface
class nodeIterator{
    using iterator_category = std::input_iterator_tag;

public:
    bool operator==(const nodeIterator n);

private:
    node* pointer;
};
*/

#endif