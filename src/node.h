#ifndef NODE_H
#define NODE_H

#include <vector>
#include <limits>

#include "atom.h"


enum CUT_TYPE{TOP, NOT, BOX};


/*
 * Each node within the graph represents all contents of a cut
*/
class node
{
private:
    std::vector<node*> children;
    std::vector<atom> atoms;
    CUT_TYPE cut;

    // [bottomLeftX, bottomLeftY, topRightX, topRightY]
    int coords[4];
public:
    node();
    node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    bool const isEmpty() { return (children.size() == 0 && atoms.size() == 0); }
    CUT_TYPE const cutType() { return cut; }
    int const numChildren() { return children.size(); }
    std::vector<node*> const getChildren() { return children; }
    int const numAtoms() { return atoms.size(); }
    std::vector<atom> const getAtoms() { return atoms; }

    bool addAtom(atom a);

    bool addSubgraph(node * n);
};

#endif