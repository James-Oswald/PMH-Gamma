#include "atom.h"

atom::atom(std::string s, int x, int y){
    this->name = s;
    this->x = x;
    this->y = y;
}

atom::atom(const atom& a){
    this->name = a.name;
    this->x = a.x;
    this->y = a.y;
}

bool atom::operator<(const atom& other) const{
    if (this->x == other.x && this->y == other.y){
        return this->name < other.name;
    } else {
        return (this->x < other.x || this->y < other.y);
    }
}

std::string const atom::getName() const{
    return this->name;
}
int const atom::xCoord() const{
    return this->x;
}
int const atom::yCoord() const{
    return this->y;
}