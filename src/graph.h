#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <iterator>

/*
 * This class is represented as a tree of nodes.
 * Each level of the tree is seperated by one cut from the previous level.
*/
class graph
{
private:
    node root;

    //returns the node corresponding to the subgraph dictated in s
    //this function is no longer viable due to requiring coordinates
    //node const createSubgraphFromString(std::string s);

public:
    graph();
    
    //This is for testing mostly
    graph(std::string s);

    std::string const text();

    // EDITING COMMANDS
    void insert();

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