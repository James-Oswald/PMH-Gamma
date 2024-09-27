#ifndef NODE_H

#include <vector>
#include <string>


enum CUT_TYPE{TOP, NOT, BOX};


/*
 * Each node within the graph represents all contents of a cut
*/
class node
{
private:
    std::vector<node> children;
    std::vector<std::string> atoms;
    CUT_TYPE cut;
public:
    node();
    node(CUT_TYPE c);

    bool const isEmpty() { return (children.size() == 0 && atoms.size() == 0); }
    CUT_TYPE const cut() { return cut; }
    int const numChildren() { return children.size(); }
    std::vector<node> const getChildren() { return children; }
    int const numAtoms() { return atoms.size(); }
    std::vector<std::string> const getAtoms() { return atoms; }

    void addAtom(std::string a){ atoms.push_back(a); }
};

#endif