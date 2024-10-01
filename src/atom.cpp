#include "atom.h"

atom::atom(std::string s, int x, int y){
    this->name = s;
    this->x = x;
    this->y = y;
}

std::string const atom::name(){
    return this->name;
}
int const atom::x(){
    return this->x;
}
int const atom::y(){
    return this->y;
}