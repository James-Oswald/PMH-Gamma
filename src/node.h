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

    int level;


    void updateLevel(int l);

public:
    node();
    node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    node(const node& n);

    ~node();

    bool operator==(const node& other) const;

    bool const isEmpty() const { return (children.size() == 0 && atoms.size() == 0); }
    bool const isSameCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;
    bool const isSameCut(const node* n) const;

    bool const contains(const atom& a) const;
    bool const contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;
    bool const contains(const node* n) const;

    bool const envelopes(const node * n) const;

    CUT_TYPE const cutType() const { return cut; }
    int const numChildren() const { return children.size(); }
    std::vector<node*> const getChildren() const { return children; }
    int const numAtoms() const { return atoms.size(); }
    std::vector<atom> const getAtoms() const { return atoms; }

    bool const addAtom(const atom& a);

    //this expects to be passed a heap allocated child.
    //will give error on destruction otherwise
    bool const addSubgraph(node * n);

    bool const removeAtom(const atom& a);

    bool const removeCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    bool const removeSubgraph(const node* n);
};

#endif