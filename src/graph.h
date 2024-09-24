#ifndef GRAPH_H

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

public:
    graph();



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

class nodeIterator{
    using iterator_category = std::input_iterator_tag;

public:
    bool operator==(const nodeIterator n);

private:
    node* pointer;
};

#endif