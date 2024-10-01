#ifndef ATOM_H
#define ATOM_H

#include <string>

class atom{
private:
    std::string name;
    int x;
    int y;

public:
    atom(std::string s, int x, int y);

    std::string const name();
    int const x();
    int const y();
};

#endif