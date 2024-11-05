#include "TextUIHelper.h"
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>

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
        std::printf("Insert into Odd: add graph\nRemove in Even: rm graph\n");
        std::printf("Add double cut: add dcut\nRemove double cut: rm dcut\n");
        std::printf("Iteration: itr graph\nDeiterate: ditr graph\n");
        std::printf("Quit: quit\nBuild mode: build\n");
        std::printf("Graph representation: pr graph\n");
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