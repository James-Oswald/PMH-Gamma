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

    std::vector<std::string> const getAtoms();

    void addAtom(std::string a){ atoms.push_back(a); }
};

#endif