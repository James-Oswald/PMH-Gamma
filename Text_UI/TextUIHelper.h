#ifndef TEXTUIHELPER_H
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../src/graph.h"

void printoperations(int solveorbuild); //prints operations available in solve mode and build mode

std::vector<int> get2coords(); //get 2 coords for functions like add atom

std::vector<int> get4coords(); //get 4 coords for functions like add cut

std::vector<int> ditergraphcoords(); //get 4 coords for diter graph

std::vector<int> getdoublecutcoords(); // get 8 coords for double cut coords

std::vector<int> getitrcoords(); // get 8 coords for itr coords (reads 6 calculates the last 2)

std::vector<int> getkjoincoords(); // get 8 coords for k join

std::vector<int> getkbreakcoords(); // get 12 coords for k break

std::vector<int> dmncoords(); //get 8 coords for dmn

int getinput(std::string question); //helper function that loops asks the question and makes sure the input is an int

bool overlap( std::vector<int> cut_coords);

bool add_cut(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType, std::vector<int> cutcoords, bool CheckStruct);

bool remove_cut(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType, std::vector<int> cutcoords, bool CheckStruct);

bool make_subgraph_from_coords(std::vector<std::vector<char>>* text_graph, graph* struct_graph,graph* return_graph, std::vector<int> coords);

bool move_graph_text(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool buildmode);

bool resize_cut_text(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType);

void expand_graph(std::vector<std::vector<char>>* text_graph, graph* struct_graph); // expands the graph to allow for more stuff
#endif 