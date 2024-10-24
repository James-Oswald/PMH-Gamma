
#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../src/graph.h"

//prints the graph
int printgraph(std::vector<std::vector<char>>* graph){
    for (int i = 0; i < graph[0].size() + 2; ++i){
        std::printf("=");
    }
    std::printf("\n");
    //for (int i = 0; i < graph.size(); ++i){
    for (int i = graph->size() - 1; i >= 0 ; --i){
        for (int k = 0; k < (*graph)[i].size(); ++k){
            if (k == 0){
                printf("#");
            }
            std::printf("%c",(*graph)[i][k]);
            if (k == (*graph)[i].size() - 1){
                printf("#");
            }
        }
        std::printf("\n");
    }
    for (int i = 0; i < (*graph)[0].size() + 2; ++i){
        std::printf("=");
    }
    std::printf("\n");
    return(0);
}

//building mode can add cuts and nodes with no regard to legality (on the tree end)
int buildingmode(std::vector<std::vector<char>>* text_graph, graph* struc_graph, int offsetx = 0, int offsety = 0){
    //offsets are used when creating a graph in a graph and ONLY deal with graph class
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
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
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
                if (valid && (*struc_graph).insert(NOT,cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3])){
                //if (valid && (*struc_graph).insert(NOT,cutcoords[0]+ offsetx,cutcoords[1]+ offsety,cutcoords[2] + offsetx,cutcoords[3]+ offsety)){ offsets dont work rn will work later
                    // CALL FUNCTION DATA STRUCTURE TO ADD CUT
                    
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        (*text_graph)[i][cutcoords[0]] = '|';
                        (*text_graph)[i][cutcoords[2]] = '|';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = '-';
                        (*text_graph)[cutcoords[3]][i] = '-';
                    }
                } else {
                    std::printf("Illegal cut\n");
                    if (!valid){
                        std::printf("Illegal cut but again\n");
                    }
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

            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] <= (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] <= text_graph->size()
            && cutcoords[0] < cutcoords[2]){
                bool valid = true;
                if (valid){
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        if ((*text_graph)[cutcoords[1]][i] != ' ' || (*text_graph)[cutcoords[3]][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                }

                if (valid){
                    // CALL FUNCTION DATA STRUCTURE TO ADD ATOM
                    int k = 0;
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = input2[k];
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
                    (*text_graph)[cutcoords[1]][i] = ' ';
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

            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1] + 1; i < cutcoords[3]; ++i){
                    printf("%c |\n",(*text_graph)[i][cutcoords[0]]);
                    if ((*text_graph)[i][cutcoords[0]] != '|' || (*text_graph)[i][cutcoords[2]] != '|'){

                        valid = false;
                        break;
                    }
                }
                if (valid){
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        printf("%c -\n",(*text_graph)[cutcoords[1]][i]);
                        if ((*text_graph)[cutcoords[1]][i] != '-' || (*text_graph)[cutcoords[3]][i] != '-'){
                            valid = false;
                            
                            break;
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
                }
            } else {
                std::printf("coords out of bounds\n");
            }
        }
        printgraph(text_graph);
    }
}

int solvemode(std::vector<std::vector<char>>* text_graph, graph* struct_graph){
    while(true){
        std::cout << "solve graph (check operations by entering 'operations'):\n";
        std::string input;
        std::getline(std::cin, input);
        printgraph(text_graph);
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
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                std::cout << "here\n";
                bool valid = true;
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    for (int k = cutcoords[0]; k < cutcoords[2]; ++k){
                        if ((*text_graph)[i][k] != ' '){
                            valid = false;
                            break;
                        }
                    }
                    
                }
                if (valid){
                    std::cout << "valid\n";
                    std::vector<std::vector<char>> sub_text_gragh;
                    std::vector<std::vector<char>>* sub_text_gragh_ptr = &sub_text_gragh;

                    //graph sub_struc_graph = graph(cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]); this doesnt work rn but should work eventually
                    graph sub_struc_graph = graph();
                    graph* sub_struc_graph_ptr = &sub_struc_graph;

                    for (int i = 0; i < cutcoords[3]-cutcoords[1]; ++i){
                        std::vector<char> matrixwidth;
                        for (int k = 0; k < cutcoords[2]-cutcoords[0]; ++k){
                            matrixwidth.push_back(' ');
                        }
                        sub_text_gragh.push_back(matrixwidth);
                    }
                    buildingmode(sub_text_gragh_ptr,sub_struc_graph_ptr, cutcoords[0], cutcoords[1]);
                    //struc_graph->insert(sub_struc_graph) add this when done on data structure side
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        for (int k = cutcoords[0]; k < cutcoords[2]; ++k){
                            (*text_graph)[i][k] = sub_text_gragh[i-cutcoords[1]][k-cutcoords[0]];
                        }
                    }
                } else {
                    std::cout << "area not clear\n";
                }
            }
        } else if (input.compare("rm graph") == 0){
            //data struct checks for leagality
            //removes everything in coords (all atoms cuts etc)
            
        } else if (input.compare("add dcut") == 0){
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
            std::vector<int> cutcoords;
            int temp;
            
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

            //checks
            bool valid = true;
            if (cutcoords[4] >= 0 && cutcoords[5] >= 0 && cutcoords[0] > cutcoords[4] && cutcoords[1] > cutcoords[5]
            && cutcoords[2] > cutcoords[0] && cutcoords[3] > cutcoords[1] && cutcoords[6] > cutcoords[2] && cutcoords[7] > cutcoords[3]
            && cutcoords[6] < (*text_graph)[0].size() && cutcoords[7] < text_graph->size()){
                for (int i = cutcoords[5]; i <= cutcoords[7]; ++i){
                    for (int k = cutcoords[4]; k <= cutcoords[6]; ++k){
                        if ( cutcoords[1]< i< cutcoords[3] && cutcoords[0]< k< cutcoords[2]){
                            if ((*text_graph)[i][k] != ' '){
                                valid = false;
                            }
                        }
                    }
                }

            }
        }
        
    }
}

int main(){
    int width;
    int length;
    std::vector<std::vector<char>> text_graph;
    std::vector<std::vector<char>>* text_graph_ptr = &text_graph;
    graph struc_graph = graph();
    graph* strc_graph_ptr = &struc_graph;
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
        int x = buildingmode(text_graph_ptr, strc_graph_ptr);
        if (x == 0){
            printf("done\n");
            break;
        } else {
            x = solvemode(text_graph_ptr, strc_graph_ptr);
            if (x == 0){
                printf("done\n");
                break;
            }
        }
    }
}