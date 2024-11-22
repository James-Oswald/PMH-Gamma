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
    void shift(int deltaX, int deltaY);

public:
    node();
    node(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
    node(const node& n);

    ~node();

    bool operator==(const node& other) const;
    bool inline operator!= (const node& other) const { return !(*this == other); }

    bool const isEmpty() const { return (children.size() == 0 && atoms.size() == 0); }
    bool const isSameCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;
    bool const isSameCut(const node* n) const;
    bool isSameGraph(const node* n) const;

    //checks if the provided coordinates are on even or odd level
    //mod = 0 for even, mod = 1 for odd
    bool onLevel(const node* n, int mod) const;

    //checks if all parts of n are within the same cut
    bool withinSameCut(const node* n) const;

    bool const contains(const atom& a) const;
    bool const contains(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;
    bool const contains(const node* n) const;

    bool const envelopes(const node * n) const;
    bool const envelopes(const atom& a) const;
    bool envelopes(int left, int bottom, int right, int top) const;

    bool overlaps(const node* n) const;
    bool overlaps(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) const;

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

    bool moveCut(CUT_TYPE c, const int* cutLoc, int deltaX, int deltaY);

    bool resizeCut(CUT_TYPE c, const int* cutLoc, const int* deltas);

// Alpha Inference Rule Helpers
private:
    //helper for double cut elim
    bool doubleCutElimFinder(const int* outerCoords, const int* innerCoords);

    //helpers for insert
    //return null on failure
    node * findPlaceToAdd(const atom& a);
    node * findPlaceToAdd(node * n);

    //helpers for erase
    node * findParent(const atom& a);
    node * findParent(const node * n);
    node * findParent(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    //helpers for iter/deiter
    //These functions return true if there is a NOT cut between the current node and the requested item
    bool cutBefore(const atom& a);
    bool cutBefore(const node* n);

    bool existsAbove(const atom& a);
    bool existsAbove(const node* n);
/* 
 * =============================================================================================
 * Alpha Inference Rules
 * =============================================================================================
*/
public:
    bool doubleCutElimination(const int* outerCoords, const int* innerCoords);

    //like add but only on odd
    bool insertAtom(const atom& a);
    bool insertSubgraph(node * n);

    bool eraseAtom(const atom& a);
    bool eraseSubgraph(const node* n);
    bool eraseCut(CUT_TYPE c, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    bool iterate(const atom& a);
    bool deiterate(const atom& a);
    bool iterate(node* n); //This requires n to be the new graph(aka is dynamically allocated and will be inserted via adding a pointer)
    bool deiterate(const node* n);

/* 
 * =============================================================================================
 * Gamma Inference Rules
 * =============================================================================================
*/
    bool kJoin(const int* cut1, const int* cut2, const int* newCut);
    bool kBreak(const int* cut1, const int* cut2, const int* oldCut);

};

#endif