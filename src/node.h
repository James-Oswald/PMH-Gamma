#ifndef NODE_H
#define NODE_H

#include <vector>
#include <set>
#include <limits>

#include "atom.h"

class nodeGreater;

enum CUT_TYPE{TOP, NOT, BOX};

/*
 * Each node within the graph represents all contents of a cut
*/
class node
{
private:
    std::set<node*, nodeGreater> children;
    std::set<atom> atoms;
    CUT_TYPE cut;

    // [bottomLeftX, bottomLeftY, topRightX, topRightY]
    int coords[4];

    int level = 0;


    void updateLevel(int l);

public:
    node();
    node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);


    //These operators are somewhat fictictious. They only compare bounding box and level.
           bool operator== (const node& other) const;
    inline bool operator!= (const node& other) const { return !(*this == other); }
           bool operator<  (const node& other) const;
    inline bool operator>  (const node& other) const { if (*this == other) return false; else return !(*this < other); }

    bool const isEmpty() const { return (children.size() == 0 && atoms.size() == 0); }
    CUT_TYPE const cutType() const { return cut; }
    int const numChildren() const { return children.size(); }
    std::set<node*, nodeGreater> const getChildren() const { return children; }
    int const numAtoms() const { return atoms.size(); }
    std::set<atom> const getAtoms() const { return atoms; }

    bool const contains(const atom& a) const;
    bool const envelopes(const node * n) const;

    bool const addAtom(const atom& a);

    bool const addSubgraph(node * n);


    bool const removeAtom(const atom& a);
};

class nodeGreater{
public:
    bool operator() (const node*& rhs, const node*& lhs){
        //return *rhs > *lhs;
        return true;
    }
};

#endif