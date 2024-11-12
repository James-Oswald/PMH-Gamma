
#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cctype>
#include "../src/graph.h"
#include "TextUIHelper.h"

//prints the graph
int printgraph(std::vector<std::vector<char>>* graph){
    for (int i = 0; i < (*graph)[0].size() + 2; ++i){
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
        std::transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            printoperations(0);
        } else if (input.compare("solve") == 0){
            return(1);
        } else if (input.compare("pr graph") == 0){
            std::cout << struc_graph->text() << "\n";
        } else if (input.compare("add cut") == 0){
            std::vector<int> cutcoords = get4coords();
            // check if coords in graph
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
            std::vector<int> cutcoords = get2coords();

            std::string input2;
                
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

                if (valid && (*struc_graph).insert(input2,cutcoords[0],cutcoords[1])){
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
        } else if (input.compare("add gamma cut") == 0){
            std::vector<int> cutcoords = get4coords();
            // check if coords in graph
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
                if (valid && (*struc_graph).insert(BOX,cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3])){
                //if (valid && (*struc_graph).insert(NOT,cutcoords[0]+ offsetx,cutcoords[1]+ offsety,cutcoords[2] + offsetx,cutcoords[3]+ offsety)){ offsets dont work rn will work later
                    // CALL FUNCTION DATA STRUCTURE TO ADD CUT
                    
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        (*text_graph)[i][cutcoords[0]] = ':';
                        (*text_graph)[i][cutcoords[2]] = ':';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = '.';
                        (*text_graph)[cutcoords[3]][i] = '.';
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
        } else if (input.compare("rm atom") == 0){
            std::vector<int> cutcoords = get2coords();
            
            std::string input2;
            while (std::cout << "Enter atom\n" && !(std::cin >> input2)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                std::cout << "Invalid input; please re-enter.\n";
            }
            std::remove_if(input2.begin(), input2.end(), isspace);

            if ((*struc_graph).remove(input2,cutcoords[0],cutcoords[1])){ // check with datastructure call to see if there is an atom named __ at __ temp set to true
                //remove atom from data structure
                int k = 0;
                for (int i = cutcoords[0]; i < cutcoords[0] + input2.length(); ++i){
                    (*text_graph)[cutcoords[1]][i] = ' ';
                    ++k;
                }
            }

        } else if (input.compare("rm cut") == 0){
            std::vector<int> cutcoords = get4coords();

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
                if (valid && (*struc_graph).remove(NOT,cutcoords[0],cutcoords[1], cutcoords[2], cutcoords[3])){
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
        } else if (input.compare("rm gamma cut") == 0){
            std::vector<int> cutcoords = get4coords();

            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1] + 1; i < cutcoords[3]; ++i){
                    printf("%c |\n",(*text_graph)[i][cutcoords[0]]);
                    if ((*text_graph)[i][cutcoords[0]] != ':' || (*text_graph)[i][cutcoords[2]] != ':'){

                        valid = false;
                        break;
                    }
                }
                if (valid && (*struc_graph).remove(BOX,cutcoords[0],cutcoords[1], cutcoords[2], cutcoords[3])){
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        printf("%c -\n",(*text_graph)[cutcoords[1]][i]);
                        if ((*text_graph)[cutcoords[1]][i] != '.' || (*text_graph)[cutcoords[3]][i] != '.'){
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
        std::transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c){ return std::tolower(c); });
        printgraph(text_graph);
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            printoperations(1);
        } else if (input.compare("build") == 0){
            return(1);
        } else if (input.compare("pr graph") == 0){
            std::cout << struct_graph->text() << "\n";
        } else if (input.compare("move") == 0){
            bool valid = move_graph_text(text_graph, struct_graph, false);
            if (!valid){
                std::cout << "INVALID\n";
            }
        } else if (input.compare("add graph") == 0){
            //data struct checks for legality (this checks for correct in space)]
            //needs to build a graph area where I can add cuts etc (mini build mode)
            //this can be done by having the user assign a new build area if space is empty then allow else say not allowed
            //then let user build whatever in there creating a new struct graph

            std::vector<int> cutcoords = get4coords();
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
                graph sub_struc_graph = graph(cutcoords[0], cutcoords[1], cutcoords[2], cutcoords[3]);
                if ((*struct_graph).insertion(sub_struc_graph)){ //need to check legality with graph
                    std::cout << "valid\n";
                    std::vector<std::vector<char>> sub_text_gragh;
                    std::vector<std::vector<char>>* sub_text_gragh_ptr = &sub_text_gragh;

                    //graph sub_struc_graph = graph(cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]); this doesnt work rn but should work eventually
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
                    (*struct_graph).insertion(sub_struc_graph);

                } else {
                    std::cout << "area not clear\n";
                }
            }
        } else if (input.compare("rm graph") == 0){
            //data struct checks for leagality
            //removes everything in coords (all atoms cuts etc)
            std::vector<int> cutcoords = get4coords();
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                std::cout << "here\n";
                bool valid = true;

                graph valid_graph = make_subgraph_from_coords(text_graph,struct_graph, cutcoords);
                if (valid_graph.isEmpty() && (*struct_graph).erasure(valid_graph)){ //check legality with graph object to check that it is a legal move
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        for (int k = cutcoords[1]; k < cutcoords[3]; ++k){
                            (*text_graph)[i][k] = ' ';
                        }
                    }
                }
            }
            
        } else if (input.compare("add dcut") == 0){
            std::vector<int> cutcoords = getdoublecutcoords();

            //checks
            bool valid = true;
            if (cutcoords[0] >= 0 && cutcoords[1] >= 0 && cutcoords[4] > cutcoords[0] && cutcoords[5] > cutcoords[1]
            && cutcoords[6] > cutcoords[4] && cutcoords[7] > cutcoords[5] && cutcoords[2] > cutcoords[6] && cutcoords[3] > cutcoords[7]
            && cutcoords[2] < (*text_graph)[0].size() && cutcoords[3] < text_graph->size()){
                for (int i = cutcoords[1]; i <= cutcoords[3]; ++i){
                    for (int k = cutcoords[0]; k <= cutcoords[2]; ++k){
                        if (!((cutcoords[5]< i && i < cutcoords[7]) && (cutcoords[4]< k && k < cutcoords[6]))){
                            if ((*text_graph)[i][k] != ' '){
                                std::cout << i << k << "\n";
                                valid = false;
                            }
                        }
                    }
                }
 
            } else {
                valid = false;
            }
            if (valid){
                // draw dcut and add to graph data structure
                for (int i = cutcoords[5]; i < cutcoords[7]; ++i){
                        (*text_graph)[i][cutcoords[4]] = '|';
                        (*text_graph)[i][cutcoords[6]] = '|';
                    }
                    for (int i = cutcoords[4]; i <= cutcoords[6]; ++i){
                        (*text_graph)[cutcoords[5]][i] = '-';
                        (*text_graph)[cutcoords[7]][i] = '-';
                    }
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        (*text_graph)[i][cutcoords[0]] = '|';
                        (*text_graph)[i][cutcoords[2]] = '|';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = '-';
                        (*text_graph)[cutcoords[3]][i] = '-';
                    }
            } else {
                std::cout << "coords not right\n";
            }
        } else if (input.compare("rm dcut") == 0){
            std::vector<int> cutcoords = getdoublecutcoords();

            //checks
            bool valid = true;
            if (cutcoords[0] >= 0 && cutcoords[1] >= 0 && cutcoords[4] > cutcoords[0] && cutcoords[5] > cutcoords[1]
            && cutcoords[6] > cutcoords[4] && cutcoords[7] > cutcoords[5] && cutcoords[2] > cutcoords[6] && cutcoords[3] > cutcoords[7]
            && cutcoords[2] < (*text_graph)[4].size() && cutcoords[3] < text_graph->size()){
                for (int i = cutcoords[1]; i <= cutcoords[3]; ++i){
                    for (int k = cutcoords[0]; k <= cutcoords[2]; ++k){

                        if ( !((cutcoords[5]< i && i < cutcoords[7]) && (cutcoords[4]< k && k < cutcoords[6]))){
                            if ( i == cutcoords[1] || i == cutcoords[3]){
                                if ((*text_graph)[i][k] != '-'){
                                    std::cout << i << k << "\n";
                                    valid = false;
                                    break;
                                }
                            } else if ( (i == cutcoords[5] && cutcoords[4] <= k && k <= cutcoords[6]) || (i == cutcoords[7]  && cutcoords[4] <= k && k <= cutcoords[6])){
                                if ((*text_graph)[i][k] != '-'){
                                    std::cout << i << k << "\n";
                                    valid = false;
                                    break;
                                }
                            } else if ((k == cutcoords[4] && (cutcoords[5]) <= i && i <= (cutcoords[7])) || (k == cutcoords[6]  && (cutcoords[5]) <= i && i <= (cutcoords[7]))){
                                if ((*text_graph)[i][k] != '|'){
                                    std::cout << i << k << "\n";
                                    valid = false;
                                    break;
                                }
                            } else if ((k == cutcoords[0] && (cutcoords[1]) <= i && i <= (cutcoords[3])) || (k == cutcoords[2]  && (cutcoords[1]) <= i && i <= (cutcoords[3]))){
                                if ((*text_graph)[i][k] != '|'){
                                    std::cout << i << k << "\n";
                                    valid = false;
                                    break;
                                }
                            } else {
                                if ((*text_graph)[i][k] != ' '){
                                    std::cout << k << i << (*text_graph)[i][k] << "\n";
                                    valid = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (valid == false){
                        break;
                    }
                }
 
            } else {
                valid = false;
            }
            if (valid){
                for (int i = cutcoords[1]; i <= cutcoords[3]; ++i){
                    for (int k = cutcoords[0]; k <= cutcoords[2]; ++k){
                        if ( !((cutcoords[5]< i && i < cutcoords[7]) && (cutcoords[4]< k && k < cutcoords[6]))){
                            (*text_graph)[i][k] = ' ';
                        }
                    }
                    if (valid == false){
                        break;
                    }
                }
            } else {
                std::cout << "Coords Incorrect\n";
            }
        } else if (input.compare("itr graph") == 0){
            std::vector<int> cutcoords = getitrcoords();
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                std::cout << "here\n";
                bool valid = true;

                if (cutcoords[4] >= 0 && cutcoords[4] < (*text_graph)[0].size() && cutcoords[6] > 0 && cutcoords[6] < (*text_graph)[0].size()
                && cutcoords[5] >= 0 && cutcoords[5] < text_graph->size() && cutcoords[7] > 0 && cutcoords[7] < text_graph->size()
                && cutcoords[4] < cutcoords[6] && cutcoords[5] < cutcoords[7]){
                    if (!(cutcoords[2] < cutcoords[4] || cutcoords[0] > cutcoords[6]
                    || cutcoords[3] < cutcoords[5] || cutcoords[1] > cutcoords[7])){
                        valid = false;
                    }
                } else {
                    valid = false;
                }

                for (int i = cutcoords[4]; i < cutcoords[6]; ++i){
                    for (int k = cutcoords[5]; k < cutcoords[7]; ++k){
                        if ((*text_graph)[k][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                    if (!valid){
                        break;
                    }
                }

                if (valid){ //check legality with graph object to check that it is a legal move
                    for (int i = 0; i < cutcoords[2] - cutcoords[0]; ++i){
                        for (int k = 0; k < cutcoords[3] - cutcoords[1]; ++k){ 
                            (*text_graph)[k + cutcoords[5]][i + cutcoords[4]] = (*text_graph)[k + cutcoords[1]][i + cutcoords[0]];
                        }
                    }
                }
            }
        } else if (input.compare("ditr graph") == 0){
            //data struct checks for leagality
            //removes everything in coords (all atoms cuts etc)
            std::vector<int> cutcoords = get4coords();
            bool valid = false;
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                std::cout << "here\n";
                valid = true;
            }
            if (valid){ //check legality with graph object to check that it is a legal move
                for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                    for (int k = cutcoords[1]; k < cutcoords[3]; ++k){
                        (*text_graph)[i][k] = ' ';
                    }
                }
            }
            
        } else if (input.compare("nec") == 0){
            std::vector<int> cutcoords = get4coords();
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
                if (valid){ // check inference rule making sure this cut is happeneing in ONLY the top level
                    
                    
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        (*text_graph)[i][cutcoords[0]] = ':';
                        (*text_graph)[i][cutcoords[2]] = ':';
                    }
                    for (int i = cutcoords[0]; i <= cutcoords[2]; ++i){
                        (*text_graph)[cutcoords[1]][i] = '.';
                        (*text_graph)[cutcoords[3]][i] = '.';
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
        } else if (input.compare("k break") == 0){

        } else if (input.compare("k join") == 0){
            std::vector<int> cutcoords = getkjoincoords();

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