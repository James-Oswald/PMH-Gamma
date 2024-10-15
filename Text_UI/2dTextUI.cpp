
#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../src/graph.h"

//prints the graph
int printgraph(std::vector<std::vector<char>> graph){
    for (int i = 0; i < graph[0].size() + 2; ++i){
        std::printf("=");
    }
    std::printf("\n");
    //for (int i = 0; i < graph.size(); ++i){
    for (int i = graph.size() - 1; i >= 0 ; --i){
        for (int k = 0; k < graph[i].size(); ++k){
            if (k == 0){
                printf("#");
            }
            std::printf("%c",graph[i][k]);
            if (k == graph[i].size() - 1){
                printf("#");
            }
        }
        std::printf("\n");
    }
    for (int i = 0; i < graph[0].size() + 2; ++i){
        std::printf("=");
    }
    std::printf("\n");
    return(0);
}

//building mode can add cuts and nodes with no regard to legality (on the tree end)
int buildingmode(std::vector<std::vector<char>> text_graph, graph struc_graph){
    while (true){
        
        std::cout << "build graph (check operations by entering 'operations'):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            std::printf("Add Cut: add cut\nAdd Atom: add atom\n");
            std::printf("Remove Cut: rm cut\nRemove Atom: rm atom\n");
            std::printf("Quit: quit\nSolve mode: solve\n");
        } else if (input.compare("solve") == 0){
            return(1);
        } else if (input.compare("add cut") == 0){
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
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < text_graph[0].size() && cutcoords[2] > 0 && cutcoords[2] < text_graph[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph.size() && cutcoords[3] > 0 && cutcoords[3] < text_graph.size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    if (text_graph[i][cutcoords[0]] != ' ' || text_graph[i][cutcoords[2]] != ' '){
                        valid = false;
                        break;
                    }
                }
                if (valid){
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        if (text_graph[cutcoords[1]][i] != ' ' || text_graph[cutcoords[3]][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                }
                if (valid && struc_graph.insert(NOT,cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3])){
                    // CALL FUNCTION DATA STRUCTURE TO ADD CUT
                    
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        text_graph[i][cutcoords[0]] = '|';
                        text_graph[i][cutcoords[2]] = '|';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        text_graph[cutcoords[1]][i] = '-';
                        text_graph[cutcoords[3]][i] = '-';
                    }
                } else {
                    std::printf("Illegal cut\n");
                }
            } else {
                std::printf("coords out of bounds\n");
            }
        } else if (input.compare("add atom") == 0){
            std::vector<int> cutcoords;
            int temp;
            std::string input2;

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
                
            while (std::cout << "Enter atom\n" && !(std::cin >> input2)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                std::cout << "Invalid input; please re-enter.\n";
            }


            std::remove_if(input2.begin(), input2.end(), isspace);
            cutcoords.push_back(cutcoords[0]+ input2.length());
            cutcoords.push_back(cutcoords[1]);

            if (cutcoords[0] >= 0 && cutcoords[0] < text_graph[0].size() && cutcoords[2] > 0 && cutcoords[2] <= text_graph[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph.size() && cutcoords[3] <= text_graph.size()
            && cutcoords[0] < cutcoords[2]){
                bool valid = true;
                if (valid){
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        if (text_graph[cutcoords[1]][i] != ' ' || text_graph[cutcoords[3]][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                }

                if (valid){
                    // CALL FUNCTION DATA STRUCTURE TO ADD ATOM
                    int k = 0;
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        text_graph[cutcoords[1]][i] = input2[k];
                        ++k;
                    }
                } else {
                    std::printf("invalid atom\n");
                }
            } else {
                std::printf("atom out of bounds\n");
            }
        } else if (input.compare("rm atom") == 0){
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
            
            std::string input2;
            while (std::cout << "Enter atom\n" && !(std::cin >> input2)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                std::cout << "Invalid input; please re-enter.\n";
            }
            std::remove_if(input2.begin(), input2.end(), isspace);

            if (true){ // check with datastructure call to see if there is an atom named __ at __ temp set to true
                //remove atom from data structure
                int k = 0;
                for (int i = cutcoords[0]; i < cutcoords[0] + input2.length(); ++i){
                    text_graph[cutcoords[1]][i] = ' ';
                    ++k;
                }
            }

        } else if (input.compare("rm cut") == 0){
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

            if (cutcoords[0] >= 0 && cutcoords[0] < text_graph[0].size() && cutcoords[2] > 0 && cutcoords[2] < text_graph[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph.size() && cutcoords[3] > 0 && cutcoords[3] < text_graph.size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1] + 1; i < cutcoords[3]; ++i){
                    printf("%c |\n",text_graph[i][cutcoords[0]]);
                    if (text_graph[i][cutcoords[0]] != '|' || text_graph[i][cutcoords[2]] != '|'){

                        valid = false;
                        break;
                    }
                }
                if (valid){
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        printf("%c -\n",text_graph[cutcoords[1]][i]);
                        if (text_graph[cutcoords[1]][i] != '-' || text_graph[cutcoords[3]][i] != '-'){
                            valid = false;
                            
                            break;
                        }
                    }
                }

                if (valid){
                    // CALL FUNCTION DATA STRUCTURE TO REMOVE CUT AND CHECK
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        text_graph[i][cutcoords[0]] = ' ';
                        text_graph[i][cutcoords[2]] = ' ';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        text_graph[cutcoords[1]][i] = ' ';
                        text_graph[cutcoords[3]][i] = ' ';
                    }
                } else {
                    std::printf("No cut at location\n");
                }
            } else {
                std::printf("coords out of bounds\n");
            }
        }
        printgraph(text_graph);
    }
}

int solvemode(std::vector<std::vector<char>> text_graph, graph struct_graph){
    while(true){
        std::cout << "solve graph (check operations by entering 'operations'):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            std::printf("Insert into Odd: add graph\nRemove in Even: rm graph\n");
            std::printf("Add double cut: add dcut\nRemove double cut: rm dcut\n");
            std::printf("Iteration: itr graph\nDeiterate: ditr graph\n");
            std::printf("Quit: quit\nBuild mode: build\n");
        } else if (input.compare("build") == 0){
            return(1);
        } else if (input.compare("add graph") == 0){
            //data struct checks for legality (this checks for correct in space)]
            //needs to build a graph area where I can add cuts etc (mini build mode)
            //this can be done by having the user assign a new build area if space is empty then allow else say not allowed
            //then let user build whatever in there creating a new struct graph

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
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < text_graph[0].size() && cutcoords[2] > 0 && cutcoords[2] < text_graph[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph.size() && cutcoords[3] > 0 && cutcoords[3] < text_graph.size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    for (int k = cutcoords[0]; k < cutcoords[2]; ++k){
                        if (text_graph[i][cutcoords[k]] != ' '){
                            valid = false;
                            break;
                        }
                    }
                    
                }
            }
        } else if (input.compare("rm graph") == 0){
            //data struct checks for leagality
            //removes everything in coords (all atoms cuts etc)
            
        }
    }
}

int main(){
    int width;
    int length;
    std::vector<std::vector<char>> text_graph;
    graph struc_graph = graph();
    //creates the graph
    while (true){
        std::cout<< "Enter valid width and length for size of the graph\n";
        std::cin >> width;
        std::cin >> length;
        std::printf("%d %d\n", width,length);
        if (width > 0 && length > 0){
            break;
        }
    }
    for (int i = 0; i < length; ++i){
        std::vector<char> matrixwidth;
        for (int k = 0; k < width; ++k){
            matrixwidth.push_back(' ');        
        }
        text_graph.push_back(matrixwidth);
    }

    // main loop
    while (true){
        int x = buildingmode(text_graph, struc_graph);
        if (x == 0){
            printf("done\n");
            break;
        } else {
            x = solvemode(text_graph, struc_graph);
            if (x == 0){
                printf("done\n");
                break;
            }
        }
    }
}