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

    void operator=(const atom& a);

    inline bool operator==(const atom& other) const { return (this->x == other.x) && (this->y == other.y) && (this->name == other.name); }
    inline bool operator!=(const atom& other) const { return !((*this) == other); }

    std::string const getName() const;
    int const xCoord() const;
    int const yCoord() const;
};

#endif