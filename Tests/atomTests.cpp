#include <iostream>

#include "../src/atom.h"

int main(){
    atom a = atom("a", 1, 1);
    std::cout << "Atom \"" << a.getName() << "\": is at position (" << a.xCoord() << ", " << a.yCoord() << ")" << std::endl;
    atom b = atom("b", -400, 36);
    std::cout << "Atom \"" << b.getName() << "\": is at position (" << b.xCoord() << ", " << b.yCoord() << ")" << std::endl;
}