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

bool move_graph_text(std::vector<std::vector<char>>* text_graph, graph* struct_graph, bool buildmode){
    std::vector<int> cutcoords = getitrcoords();
    int hightestrecx1 = std::max(cutcoords[0],cutcoords[4]);
    int hightestrecy1 = std::max(cutcoords[1],cutcoords[5]);
    int hightestrecx2 = std::max(cutcoords[2],cutcoords[6]);
    int hightestrecy2 = std::max(cutcoords[3],cutcoords[7]);
    //moved twords bottom left
    bool valid = true;
    if (hightestrecx1 == cutcoords[0] && hightestrecy1 == cutcoords[1] && hightestrecx2 == cutcoords[2] && hightestrecy2 == cutcoords[3]){
        for (int i = cutcoords[4]; i < cutcoords[6]; ++i){
            if (valid == false){
                    break;
                }
            for (int k = cutcoords[5]; i < cutcoords[7]; ++k){
                if (valid == false){
                    break;
                }
                if (i >= hightestrecx1 && k >= hightestrecy1){
                    continue;
                }  else {
                    if ((*text_graph)[k][i] != ' '){
                        valid = false;
                    }
                }
            }
        }
    } else { //moved twords top right
        for (int i = cutcoords[4]; i < cutcoords[6]; ++i){
            if (valid == false){
                    break;
                }
            for (int k = cutcoords[5]; i < cutcoords[7]; ++k){
                if (valid == false){
                    break;
                }
                if (i <= cutcoords[2] && k <= cutcoords[3]){
                    continue;
                }  else {
                    if ((*text_graph)[k][i] != ' '){
                        valid = false;
                    }
                }
            }
        }
    } 
    if (!buildmode){
        // moved twords bottom left
        if (hightestrecx1 == cutcoords[0] && hightestrecy1 == cutcoords[1] && hightestrecx2 == cutcoords[2] && hightestrecy2 == cutcoords[3]){
            for (int i = cutcoords[4]; i < cutcoords[0]; ++i){
                if (valid == false){
                    break;
                }
                for (int k = cutcoords[7]; k < cutcoords[3]; ++k){
                    if (valid == false){
                        break;
                    }
                    if ((*text_graph)[k][i] == ':' || (*text_graph)[k][i] == '.' || (*text_graph)[k][i] == '|' || (*text_graph)[k][i] == '-'){
                        valid = false;
                    }
                }
            }
            for (int i = cutcoords[6]; i < cutcoords[2]; ++i){
                if (valid == false){
                    break;
                }
                for (int k = cutcoords[5]; k < cutcoords[1]; ++k){
                    if (valid == false){
                        break;
                    }
                    if ((*text_graph)[k][i] == ':' || (*text_graph)[k][i] == '.' || (*text_graph)[k][i] == '|' || (*text_graph)[k][i] == '-'){
                        valid = false;
                    }
                }
            }
        } else { // moved twords top right
            for (int i = cutcoords[0]; i < cutcoords[4]; ++i){
                if (valid == false){
                    break;
                }
                for (int k = cutcoords[3]; k < cutcoords[7]; ++k){
                    if (valid == false){
                        break;
                    }
                    if ((*text_graph)[k][i] == ':' || (*text_graph)[k][i] == '.' || (*text_graph)[k][i] == '|' || (*text_graph)[k][i] == '-'){
                        valid = false;
                    }
                }
            }
            for (int i = cutcoords[2]; i < cutcoords[6]; ++i){
                if (valid == false){
                    break;
                }
                for (int k = cutcoords[1]; k < cutcoords[5]; ++k){
                    if (valid == false){
                        break;
                    }
                    if ((*text_graph)[k][i] == ':' || (*text_graph)[k][i] == '.' || (*text_graph)[k][i] == '|' || (*text_graph)[k][i] == '-'){
                        valid = false;
                    }
                }
            }
        }
    }
    // moved twords bottom left
    if (valid){
        if (hightestrecx1 == cutcoords[0] && hightestrecy1 == cutcoords[1] && hightestrecx2 == cutcoords[2] && hightestrecy2 == cutcoords[3]){
            for (int i = 0; i < cutcoords[2] - cutcoords[0]; ++i){
                for (int k = 0; k < cutcoords[3] - cutcoords[1]; ++k){
                    (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                }
            }
        } else {// moved twords top right
            for (int i = cutcoords[2] - cutcoords[0]; i > 0; --i){
                for (int k = cutcoords[3] - cutcoords[1] - 1; k >= 0; --k){
                    (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                }
            }
        }
    }
    return(valid); 
}