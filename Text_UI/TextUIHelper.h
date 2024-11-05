#ifndef TEXTUIHELPER_H
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>

void printoperations(int solveorbuild); //prints operations available in solve mode and build mode

std::vector<int> get2coords(); //get 2 coords for functions like add atom

std::vector<int> get4coords(); //get 4 coords for functions like add cut

std::vector<int> getdoublecutcoords(); // get 8 coords for double cut coords

std::vector<int> getitrcoords(); // get 8 coords for itr coords (calculates the last 2)


#endif