#include <iostream>

#include "../src/node.h"
#include "../src/graph.h"

int main(){
    node root = node();
    if (root.cutType() != TOP){
        std::cout << "ERROR: node defualt constructor\n";
        return -1;
    }
    node cut = node(NOT, 0, 0, 10, 10);
    node boxCut = node(BOX, -500, -500, 230, 456);
    if (!root.isEmpty() || !cut.isEmpty() || !boxCut.isEmpty()){
        std::cout << "ERROR: node isEmpty\n";
        return -1;
    }

    atom a = atom("apple", 1, 1);
    atom b = atom("badger", -400, 36);
    atom c = atom("cat", 12, 13);
    atom d = atom("dog", -400, 400);

    if (!cut.addAtom(a)){
        std::cout << "ERROR: node addAtom returns false when should input atom\n";
        return -1;
    }
    if (!root.addAtom(c)){
        std::cout << "ERROR: node addAtom returns false when should input atom\n";
        return -1;
    }
    if (!boxCut.addAtom(d)){
        std::cout << "ERROR: node addAtom returns false when should input atom\n";
        return -1;
    }
    if (cut.addAtom(b)){
        std::cout << "ERROR: node addAtom returns true when should not input atom\n";
        return -1;
    }
    if (cut.addSubgraph(&boxCut)){
        std::cout << "ERROR: node addSubgraph returns true when input is outside bounds\n";
        return -1;
    }
    if (!root.addSubgraph(&boxCut)){
        std::cout << "ERROR: node addSubgraph returns false when input is inside bounds\n";
        return -1;
    }
    if (!boxCut.addSubgraph(&cut)){
        std::cout << "ERROR: node addSubgraph returns false when input is inside bounds\n";
        return -1;
    }

    std::cout << getSubgraphText(&root) << std::endl;

    std::cout << "Tests Ran Sucessfully\n";
    return 0;
}
