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

    int level = 0;


    void updateLevel(int l);

public:
    node();
    node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    bool const isEmpty() const { return (children.size() == 0 && atoms.size() == 0); }
    CUT_TYPE const cutType() const { return cut; }
    int const numChildren() const { return children.size(); }
    std::vector<node*> const getChildren() const { return children; }
    int const numAtoms() const { return atoms.size(); }
    std::vector<atom> const getAtoms() const { return atoms; }

    bool const contains(const atom& a) const;
    bool const envelopes(const node * n) const;

    bool const addAtom(const atom& a);

    bool const addSubgraph(node * n);
};

#endif