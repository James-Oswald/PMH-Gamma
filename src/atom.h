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
    atom(const atom& a);

    std::string const getName();
    int const xCoord();
    int const yCoord();
};

#endif