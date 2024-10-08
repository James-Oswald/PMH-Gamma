#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <iterator>

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

    std::string const text();

    // EDITING COMMANDS
    bool insert(atom a);
    bool insert(graph g);

    bool remove(atom a);
    bool remove(graph g);

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
std::string const getSubgraphText(node * n);



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