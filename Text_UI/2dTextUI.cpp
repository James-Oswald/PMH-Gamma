
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
#include <cmath>

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


int printgraphwithlabels(std::vector<std::vector<char>>* graph){
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
                std::cout << i;
            }
        }
        std::printf("\n");
    }
    std::vector<std::string> vectortest;
    std::cout << "=";
    for (int i = 0; i < (*graph)[0].size(); ++i){
        vectortest.push_back(std::to_string(i));
    }
    bool first = true;
    while (vectortest.back() != ""){
        for (int i = 0; i < vectortest.size(); ++i){
            if (vectortest[i] == ""){
                std::cout << " ";
            } else {
                char temp = vectortest[i].at(0);
                std::cout << temp;
                vectortest[i].erase(0,1);
            }
        }
        if (first){
            std::cout << "=";
        }
        first = false;
        std::cout << "\n ";
    }
    std::printf("\n");
    return(0);
}

//building mode can add cuts and nodes with no regard to legality (on the tree end)
int buildingmode(std::vector<std::vector<char>>* text_graph, graph* struc_graph, int offsetx = 0, int offsety = 0){
    //offsets are used when creating a graph in a graph and ONLY deal with graph class
    bool labels = false;
    while (true){
        
        std::cout << "build graph (check operations by entering 'operations'):\n";
        
        std::string input;
        
        if (input == ""){
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if (labels){
                printgraphwithlabels(text_graph);
            } else {
                printgraph(text_graph);
            }
        }
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            printoperations(0);
        } else if (input.compare("solve") == 0){
            return(1);
        } else if (input.compare("pr graph") == 0){
            std::cout << struc_graph->text() << "\n";
        } else if (input.compare("yes coords") == 0){
            labels = true;
        } else if (input.compare("no coords") == 0){
            labels = false;
        } else if (input.compare("expand graph") == 0){
            expand_graph(text_graph,struc_graph);
        } else if (input.compare("add cut") == 0){
            std::vector<int> cutcoords = get4coords();
            // check if coords in graph
            bool CutType = true;
            if (!add_cut(text_graph,struc_graph,CutType,cutcoords, true)){
                std::cout << "error with add cut";
            }
        } else if (input.compare("move cut") == 0){
            bool valid = move_graph_text(text_graph, struc_graph, true);
            if (!valid){
                std::cout << "INVALID\n";
            }
        } else if (input.compare("resize cut") == 0){

            bool valid = resize_cut_text(text_graph, struc_graph, true);
            if (!valid){
                std::cout << "INVALID\n";
            }
        } else if (input.compare("add atom") == 0){
            std::vector<int> cutcoords = get2coords();

            std::string input2;
            std::string inp = "";
            int temp;
            while (inp == "") {
                std::cout << "Enter atom\n";
                std::cin >> inp;
                bool valid = true;
                for (int i = 0; i < inp.length(); ++i){
                    if (inp[i] == '.' || inp[i] == ':' || inp[i] == '|' || inp[i] == '-' || inp[i] == ' '){ // these characters are reserved for cuts and empty space so disalow user
                        valid = false;
                        std::cin.clear(); //clear bad input flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        std::cout << "Invalid input; please re-enter.\n";
                        inp = "";
                        break;
                    }
                }
                input2 = inp;
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
            bool CutType = false;
            if (!add_cut(text_graph,struc_graph,CutType,cutcoords,true)){
                std::cout << "error with add cut";
            }
        } else if (input.compare("rm atom") == 0){
            std::vector<int> cutcoords = get2coords();
            
            std::string input2;
            std::string inp = "";
            int temp;
            while (inp == "") {
                std::cout << "Enter atom\n";
                std::cin >> inp;
                bool valid = true;
                for (int i = 0; i < inp.length(); ++i){
                    if (inp[i] == '.' || inp[i] == ':' || inp[i] == '|' || inp[i] == '-' || inp[i] == ' '){ // these characters are reserved for cuts and empty space so disalow user
                        valid = false;
                        std::cin.clear(); //clear bad input flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        std::cout << "Invalid input; please re-enter.\n";
                        inp = "";
                        break;
                    }
                }
                input2 = inp;
            }

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
            // check if coords in graph
            bool CutType = true;
            if (!remove_cut(text_graph,struc_graph,CutType,cutcoords, true)){
                std::cout << "error with add cut";
            }
        } else if (input.compare("rm gamma cut") == 0){
            std::vector<int> cutcoords = get4coords();
            // check if coords in graph
            bool CutType = false;
            if (!remove_cut(text_graph,struc_graph,CutType,cutcoords, true)){
                std::cout << "error with add cut";
            }
        }
        input = "";
        
    } 
}

int solvemode(std::vector<std::vector<char>>* text_graph, graph* struct_graph){
    bool labels = false;
    while(true){
        std::cout << "solve graph (check operations by entering 'operations'):\n";
        std::string input;
        if (input == ""){
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if (labels){
                printgraphwithlabels(text_graph);
            } else {
                printgraph(text_graph);
            }
        }
        if (input.compare("quit") == 0){
            return(0);
        } else if (input.compare("operations") == 0){
            printoperations(1);
        } else if (input.compare("yes coords") == 0){
            labels = true;
        } else if (input.compare("no coords") == 0){
            labels = false;
        } else if (input.compare("build") == 0){
            return(1);
        } else if (input.compare("expand graph") == 0){
            expand_graph(text_graph,struct_graph);
        } else if (input.compare("pr graph") == 0){
            std::cout << struct_graph->text() << "\n";
        } else if (input.compare("move cut") == 0){
            bool valid = move_graph_text(text_graph, struct_graph, true);
            if (!valid){
                std::cout << "INVALID\n";
            }
        } else if (input.compare("resize cut") == 0){

            bool valid = resize_cut_text(text_graph, struct_graph, true);
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
                bool valid = true;
                graph return_graph = graph(cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]);
                graph* return_graph_ptr = &return_graph;
                valid = make_subgraph_from_coords(text_graph,struct_graph,return_graph_ptr, cutcoords);
                if (valid && (*struct_graph).erasure(return_graph)){ //check legality with graph object to check that it is a legal move
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
            const int cut1[4] = {cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]};
            const int cut2[4] = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
            if ((*struct_graph).doubleCutIntroduction(cut1,cut2)){
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
            const int cut1[4] = {cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]};
            const int cut2[4] = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
            if (valid && (*struct_graph).doubleCutElimination(cut1,cut2)){
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
                graph return_graph = graph(cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]);
                graph* return_graph_ptr = &return_graph;
                if (valid){
                    valid = make_subgraph_from_coords(text_graph,struct_graph,return_graph_ptr,cutcoords);
                }
                if (valid && (*struct_graph).iteration(return_graph)){ //check legality with graph object to check that it is a legal move
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
            std::vector<int> cutcoords = ditergraphcoords();
            bool valid = false;
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < (*text_graph)[0].size() && cutcoords[2] > 0 && cutcoords[2] < (*text_graph)[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < text_graph->size() && cutcoords[3] > 0 && cutcoords[3] < text_graph->size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){

                valid = true;
            }
            graph return_graph = graph(cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]);
            graph* return_graph_ptr = &return_graph;
            if (valid){
                valid = make_subgraph_from_coords(text_graph,struct_graph,return_graph_ptr,cutcoords);
            }
            if (valid && (*struct_graph).deiteration(return_graph)){ //check legality with graph object to check that it is a legal move
                for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                    for (int k = cutcoords[1]; k < cutcoords[3]; ++k){
                        (*text_graph)[i][k] = ' ';
                    }
                }
            }
            
        } else if (input.compare("nec") == 0){ // neccessity
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
            std::vector<int> cut_coords = getkbreakcoords();
            bool valid = true;
            if (!(cut_coords[0] <= cut_coords[4] && cut_coords[1] <= cut_coords[5] && cut_coords[0] <= cut_coords[8] && cut_coords[1] <= cut_coords[9] &&
            cut_coords[2] >= cut_coords[6] && cut_coords[3] >= cut_coords[7] && cut_coords[2] >= cut_coords[10] && cut_coords[3] >= cut_coords[11])){
                valid = false;
            }
            std::vector<int> overlapcoords = {cut_coords[4],cut_coords[5],cut_coords[6],cut_coords[7],cut_coords[8],cut_coords[9],cut_coords[10],cut_coords[11]};
            valid = !overlap(overlapcoords);
            for (int i = cut_coords[0]; i <= cut_coords[2]; ++i){
                if (!valid){
                        break;
                    }
                for (int k = cut_coords[1]; k <= cut_coords[3]; ++k){
                    if (!valid){
                        break;
                    }
                    if ((i <= cut_coords[6] && i >= cut_coords[4] && k <= cut_coords[7] && k >= cut_coords[5]) || 
                    (i <= cut_coords[10] && i >= cut_coords[8] && k <= cut_coords[11] && k >= cut_coords[9])){
                        continue;
                    } else {
                        if ((*text_graph)[k][i] != ' '){
                            valid = false;
                        }
                    }
                }
            }
            if (valid /*&& struct_graph->kBreak(graph1,graph2,outercut)*/ ){
                std::vector<int> graph1coords = {cut_coords[4],cut_coords[5],cut_coords[6],cut_coords[7]};
                std::vector<int> graph2coords = {cut_coords[8],cut_coords[9],cut_coords[10],cut_coords[11]};
                remove_cut(text_graph,struct_graph,false,cut_coords,false);
                add_cut(text_graph,struct_graph,false,graph1coords,false);
                add_cut(text_graph,struct_graph,false,graph2coords,false);
                
            } else {
                std::cout << "Error with k break\n";
            }
        } else if (input.compare("k join") == 0){
            std::vector<int> cutcoords = getkjoincoords();
            const int outercut[4] = {std::min(cutcoords[0],cutcoords[4]), std::min(cutcoords[1],cutcoords[5]),std::max(cutcoords[2],cutcoords[6]),std::max(cutcoords[3],cutcoords[7])};
            bool legal = true;
            for (int i = outercut[0]; i <= outercut[2]; ++i){
                if (!legal){
                        break;
                    }
                for (int k = outercut[1]; k <= outercut[3]; ++k){
                    if (!legal){
                        break;
                    }
                    if ((i <= cutcoords[2] && i >= cutcoords[0] && k <= cutcoords[3] && k >= cutcoords[1]) || 
                    (i <= cutcoords[6] && i >= cutcoords[4] && k <= cutcoords[7] && k >= cutcoords[5])){
                        continue;
                    } else {
                        if ((*text_graph)[k][i] != ' '){
                            legal = false;
                        }
                    }
                }
            }
            const int graph1[4] = {cutcoords[0],cutcoords[1],cutcoords[2],cutcoords[3]};
            const int graph2[4] = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
            if (legal && struct_graph->kJoin(graph1,graph2,outercut)){
                std::vector<int> endcoords = {outercut[0],outercut[1],outercut[2],outercut[3]};
                std::vector<int> coordsgraph2 = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
                remove_cut(text_graph,struct_graph,false,cutcoords,false);
                remove_cut(text_graph,struct_graph,false,coordsgraph2,false);
                add_cut(text_graph,struct_graph,false,endcoords,false);
            } else {
                std::cout << "Error with k join\n";
            }
        } else if (input.compare("dmn") == 0){
            std::vector<int> cutcoords = dmncoords();
            bool valid = true;
            valid = !overlap(cutcoords);
            if (valid){
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
                }
                if (cutcoords[4] >= 0 && cutcoords[4] < (*text_graph)[0].size() && cutcoords[6] > 0 && cutcoords[6] < (*text_graph)[0].size()
                    && cutcoords[5] >= 0 && cutcoords[5] < text_graph->size() && cutcoords[7] > 0 && cutcoords[7] < text_graph->size()
                    && cutcoords[4] < cutcoords[6] && cutcoords[5] +1 < cutcoords[7]){
                    bool valid = true;
                    for (int i = cutcoords[5]; i < cutcoords[7]; ++i){
                        if ((*text_graph)[i][cutcoords[4]] != ' ' || (*text_graph)[i][cutcoords[6]] != ' '){
                            valid = false;
                            break;
                        }
                    }
                    if (valid){
                        for (int i = cutcoords[4]; i < cutcoords[6]; ++i){
                            if ((*text_graph)[cutcoords[5]][i] != ' ' || (*text_graph)[cutcoords[7]][i] != ' '){
                                valid = false;
                                break;
                            }
                        }
                    }
                }

            }
            if (valid /*&& check valid with graph struct*/){
                add_cut(text_graph,struct_graph, false,cutcoords, false);
                std::vector<int> secondcut = {cutcoords[4],cutcoords[5],cutcoords[6],cutcoords[7]};
                add_cut(text_graph,struct_graph,  false, secondcut, false);
            }
        }
        input = "";
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