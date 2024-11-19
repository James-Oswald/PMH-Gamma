#include "TextUIHelper.h"
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../src/graph.h"
#include <iostream>

void printoperations(int solveorbuild){
    if (solveorbuild == 0){
        std::printf("Add Cut: add cut\nAdd Atom: add atom\n");
        std::printf("Add Gamma Cut: add gamma cut\n");
        std::printf("Remove Cut: rm cut\nRemove Atom: rm atom\n");
        std::printf("Remove Gamma Cut: rm gamma cut\n");
        std::printf("Quit: quit\nSolve mode: solve\n");
        
        std::printf("Graph representation: pr graph\n");
    } else {
        std::printf("Alpha rules:\n");
        std::printf("Insert into Odd: add graph\nRemove in Even: rm graph\n");
        std::printf("Add double cut: add dcut\nRemove double cut: rm dcut\n");
        std::printf("Iteration: itr graph\nDeiterate: ditr graph\n");
        std::printf("Quit: quit\nBuild mode: build\n");
        std::printf("Graph representation: pr graph\n");
        std::printf("Gamma rules:\n");
        std::printf("K Break: k break\n");
        std::printf("K Join: k join\n");
        std::printf("Necessity: nec\n");
    }
}

std::vector<int> get2coords(){
    std::vector<int> cutcoords;

    int temp;
    while (std::cout << "Enter x1 (left most character of atom)\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y1 (left most character of atom)\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);
    return(cutcoords);
}

std::vector<int> get4coords(){
    std::vector<int> cutcoords;
    int temp;
    while (std::cout << "Enter x1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter x2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);
    return(cutcoords);
}


std::vector<int> getdoublecutcoords(){
    std::vector<int> cutcoords;
    int temp;
            
    while (std::cout << "Enter x1 outer cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y1 outer cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter x2 outer cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y2 outer cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);
            
    while (std::cout << "Enter x1 inner cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y1 inner cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter x2 inner cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "Enter y2 inner cut\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);
    return(cutcoords);
}

std::vector<int> getitrcoords(){
    std::vector<int> cutcoords;
    int temp;
            
    while (std::cout << "graph itering x1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph itering y1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph itering x2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph itering y2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "placing graph x1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "placing graph y1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    cutcoords.push_back(cutcoords[4] + cutcoords[2] - cutcoords[0]);
    cutcoords.push_back(cutcoords[5] + cutcoords[3] - cutcoords[1]);
    return(cutcoords);
}

std::vector<int> getkjoincoords(){
    std::vector<int> cutcoords;
    int temp;

    while (std::cout << "graph 1 join x1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 1 join y1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 1 join x2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 1 join y2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 2 join x1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 2 join y1\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 2 join x2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    while (std::cout << "graph 2 join y2\n" && !(std::cin >> temp)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    cutcoords.push_back(temp);

    return(cutcoords);
}


bool add_cut(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType, std::vector<int> cutcoords, bool CheckStruct){
    if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] +1 < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    if ((*text_graph)[i][cutcoords[0]] != ' ' || (*text_graph)[i][cutcoords[2]] != ' '){
                        valid = false;
                        break;
                    }
                }
                if (valid){
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        if ((*text_graph)[cutcoords[1]][i] != ' ' || (*text_graph)[cutcoords[3]][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                }
                if (CutType){
                    bool buffer = true;
                    if (CheckStruct){
                        (*struct_graph).insert(NOT,cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]);
                    }
                    if (valid && buffer){
                        for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                            (*text_graph)[i][cutcoords[0]] = '|';
                            (*text_graph)[i][cutcoords[2]] = '|';
                        }
                        for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                            (*text_graph)[cutcoords[1]][i] = '-';
                            (*text_graph)[cutcoords[3]][i] = '-';
                        }
                    } else {
                        return(false);
                    }
                } else {
                    bool buffer = true;
                    if (CheckStruct){
                        (*struct_graph).insert(BOX,cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]);
                    }
                    if (valid && buffer){
                        for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                            (*text_graph)[i][cutcoords[0]] = ':';
                            (*text_graph)[i][cutcoords[2]] = ':';
                        }
                        for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                            (*text_graph)[cutcoords[1]][i] = '.';
                            (*text_graph)[cutcoords[3]][i] = '.';
                        }
                } else {
                    return(false);
                }
                }
            } else {
                return(false);
            }
    return(true);
}

bool remove_cut(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType, std::vector<int> cutcoords, bool CheckStruct){
    if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                if (CutType){
                    for (int i = cutcoords[1] + 1; i < cutcoords[3]; ++i){
                        if ((*text_graph)[i][cutcoords[0]] != '|' || (*text_graph)[i][cutcoords[2]] != '|'){

                            valid = false;
                            break;
                        }
                    }
                } else {
                    for (int i = cutcoords[1] + 1; i < cutcoords[3]; ++i){
                        if ((*text_graph)[i][cutcoords[0]] != ':' || (*text_graph)[i][cutcoords[2]] != ':'){
                            valid = false;
                            break;
                        }
                    }
                }
                
                if (CutType){
                    bool buffer = true;
                    if (CheckStruct){
                        buffer = (*struct_graph).remove(NOT,cutcoords[0],cutcoords[1], cutcoords[2], cutcoords[3]);
                    }
                    if (valid && buffer){
                        for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                            if ((*text_graph)[cutcoords[1]][i] != '-' || (*text_graph)[cutcoords[3]][i] != '-'){
                                valid = false;
                                break;
                            }
                        }
                    }
                } else {
                    bool buffer = true;
                    if (CheckStruct){
                        buffer = (*struct_graph).remove(BOX,cutcoords[0],cutcoords[1], cutcoords[2], cutcoords[3]);
                    }
                    if (valid && buffer){
                        for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                            if ((*text_graph)[cutcoords[1]][i] != '.' || (*text_graph)[cutcoords[3]][i] != '.'){
                                valid = false;
                                break;
                            }
                        }
                    }
                }
                
                if (valid){
                    // CALL FUNCTION DATA STRUCTURE TO REMOVE CUT AND CHECK
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        (*text_graph)[i][cutcoords[0]] = ' ';
                        (*text_graph)[i][cutcoords[2]] = ' ';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = ' ';
                        (*text_graph)[cutcoords[3]][i] = ' ';
                    }
                } else {
                    std::printf("No cut at location\n");
                    return(false);
                }
            } else {
                std::printf("coords out of bounds\n");
                return(false);
            }
    return(true);
}

bool make_subgraph_from_coords(std::vector<std::vector<char>>* text_graph, graph* struct_graph,graph* return_graph_ptr, std::vector<int> coords){
    std::vector<std::vector<char>> text_graph2;
    
    for (int k = coords[1]; k <= coords[3]; ++k){
        std::vector<char> temp;
        for (int i = coords[0]; i <= coords[2]; ++i){
            temp.push_back(((*text_graph)[k][i]));
        }
        text_graph2.push_back(temp);
    }
    bool valid_graph = true;

    int offsetx = coords[0];
    int offsety = coords[1];

    for (int k = coords[1]; k <= coords[3]; ++k){
        if (!valid_graph){break;}
        for (int i = coords[0]; i <= coords[2]; ++i){
            if (!valid_graph){break;}
            if (text_graph2[k-offsety][i-offsetx] == '-' || text_graph2[k-offsety][i-offsetx] == '.'){
                int startx = i-offsetx;
                int starty = k-offsety;
                char graph_top_bot = (text_graph2[k-offsety][i-offsetx]);
                char graph_side = (text_graph2[k-offsety+1][i-offsetx]);
                int counter = starty+1;
                int topyvalue;
                while (true){
                    if ((counter > coords[3] - offsety)){
                        valid_graph = false;
                        break;
                    }
                    if (graph_top_bot == text_graph2[counter][startx]){
                        topyvalue = counter;
                        break;
                    }
                    ++counter;
                }
                if (!valid_graph){break;}
                counter = startx+1;
                int rightsidevalue;
                while (true){
                    if ((counter > coords[2] - offsetx)){
                        valid_graph = false;
                        break;
                    }
                    if (graph_side == text_graph2[starty+1][counter]){
                        rightsidevalue = counter;
                        break;
                    }
                    ++counter;
                }
                if (!valid_graph){break;}
                std::vector<int> cutcoords;
                cutcoords.push_back(startx);
                cutcoords.push_back(starty);
                cutcoords.push_back(rightsidevalue);
                cutcoords.push_back(topyvalue);
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    text_graph2[i][cutcoords[0]] = ' ';
                    text_graph2[i][cutcoords[2]] = ' ';
                    }
                for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                    text_graph2[cutcoords[1]][i] = ' ';
                    text_graph2[cutcoords[3]][i] = ' ';
                }
                if (graph_top_bot == '-'){
                    (*return_graph_ptr).insert(NOT,cutcoords[0]+offsetx,cutcoords[1]+offsety,cutcoords[2]+offsetx,cutcoords[3]+offsety);
                } else {
                    (*return_graph_ptr).insert(BOX,cutcoords[0]+offsetx,cutcoords[1]+offsety,cutcoords[2]+offsetx,cutcoords[3]+offsety);
                }
            } else if (text_graph2[k-offsety][i-offsetx] != ' '){
                std::string atom;
                

                int counter = i-offsetx;
                while(true){
                    if (counter > coords[2]){
                        valid_graph = false;
                        break;
                    }
                    atom += text_graph2[k-offsety][counter];
                    if ((*struct_graph).contains(atom,i,k)){
                        break;
                    }
                    ++counter;
                }
                if (!valid_graph){break;}
                for (int j = i-offsetx; j <= counter; ++j){
                    text_graph2[k-offsety][j] = ' ';
                }
                
            }
        }
    }
    return(valid_graph);
}

bool move_graph_text(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType){
    std::vector<int> cutcoords = getitrcoords();
    const int cutLoc[4] = {cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]};
    bool valid = false;
    if (CutType){
        if ((*struct_graph).moveCut(NOT,cutLoc,cutcoords[4]-cutcoords[0],cutcoords[5]-cutcoords[1])){
            valid = true;
            int hightestrecx1 = std::max(cutcoords[0],cutcoords[4]);
            int hightestrecy1 = std::max(cutcoords[1],cutcoords[5]);
            int hightestrecx2 = std::max(cutcoords[2],cutcoords[6]);
            int hightestrecy2 = std::max(cutcoords[3],cutcoords[7]);
            //moved twords bottom left
            if (hightestrecx1 == cutcoords[0] && hightestrecy1 == cutcoords[1] && hightestrecx2 == cutcoords[2] && hightestrecy2 == cutcoords[3]){
                for (int i = 0; i <= cutcoords[2] - cutcoords[0]; ++i){
                    for (int k = 0; k <= cutcoords[3] - cutcoords[1]; ++k){
                        (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                        (*text_graph)[k + cutcoords[1]][i + cutcoords[0]] = ' ';
                    }
                }
            } else { //moved twords top right
                for (int i = cutcoords[2] - cutcoords[0]; i >= 0; --i){
                    for (int k = cutcoords[3] - cutcoords[1]; k >= 0; --k){
                        (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                        (*text_graph)[k + cutcoords[1]][i + cutcoords[0]] = ' ';
                    }
                }
            }
        }
    } else {
        if ((*struct_graph).moveCut(BOX,cutLoc,cutcoords[4]-cutcoords[0],cutcoords[5]-cutcoords[1])){
            valid = true;
            int hightestrecx1 = std::max(cutcoords[0],cutcoords[4]);
            int hightestrecy1 = std::max(cutcoords[1],cutcoords[5]);
            int hightestrecx2 = std::max(cutcoords[2],cutcoords[6]);
            int hightestrecy2 = std::max(cutcoords[3],cutcoords[7]);
            //moved twords bottom left
            if (hightestrecx1 == cutcoords[0] && hightestrecy1 == cutcoords[1] && hightestrecx2 == cutcoords[2] && hightestrecy2 == cutcoords[3]){
                for (int i = 0; i <= cutcoords[2] - cutcoords[0]; ++i){
                    for (int k = 0; k <= cutcoords[3] - cutcoords[1]; ++k){
                        (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                        (*text_graph)[k + cutcoords[1]][i + cutcoords[0]] = ' ';
                    }
                }
            } else { //moved twords top right
                for (int i = cutcoords[2] - cutcoords[0]; i >= 0; --i){
                    for (int k = cutcoords[3] - cutcoords[1]; k >= 0; --k){
                        (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                        (*text_graph)[k + cutcoords[1]][i + cutcoords[0]] = ' ';
                    }
                }
            }
        }
    }
    return(valid);
}

bool resize_cut_text(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool CutType){
    std::vector<int> cutcoords = getdoublecutcoords();
    const int cutLoc[4] = {cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]};
    const int deltas[4] = {cutcoords[4]-cutcoords[0],cutcoords[5]-cutcoords[1],cutcoords[6]-cutcoords[2],cutcoords[7]-cutcoords[3]};
    if (CutType){
        bool legal = struct_graph->resizeCut(NOT,cutLoc,deltas);
        if (legal){
            std::vector<int> addcutcoords = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
            remove_cut(text_graph,struct_graph, true, cutcoords, false);
            add_cut(text_graph,struct_graph, true, addcutcoords, false);
            return(true);
        }
    } else {
        bool legal = struct_graph->resizeCut(BOX,cutLoc,deltas);
        if (legal){
            std::vector<int> addcutcoords = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
            remove_cut(text_graph,struct_graph, false, cutcoords, false);
            add_cut(text_graph,struct_graph, false, addcutcoords, false);
            return(true);
        }
    }
    return(false);
}