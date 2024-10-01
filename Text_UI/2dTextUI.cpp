
#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>


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
int buildingmode(std::vector<std::vector<char>> graph){
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
            std::cout<< "Enter x1\n";
            int temp;
            std::cin >> temp;
            cutcoords.push_back(temp);
            std::cout<< "Enter y1\n";
            std::cin >> temp;
            cutcoords.push_back(temp);
            std::cout<< "Enter x2\n";
            std::cin >> temp;
            cutcoords.push_back(temp);
            std::cout<< "Enter y2\n";
            std::cin >> temp;
            cutcoords.push_back(temp);
            // check if coords in graph
            if (cutcoords[0] >= 0 && cutcoords[0] < graph[0].size() && cutcoords[2] > 0 && cutcoords[2] < graph[0].size()
            && cutcoords[1] >= 0 && cutcoords[1] < graph.size() && cutcoords[3] > 0 && cutcoords[3] < graph.size()
            && cutcoords[0] < cutcoords[2] && cutcoords[1] < cutcoords[3]){
                bool valid = true;
                for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                    if (graph[i][cutcoords[0]] != ' ' || graph[i][cutcoords[2]] != ' '){
                        valid = false;
                        break;
                    }
                }
                if (valid){
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        if (graph[cutcoords[1]][i] != ' ' || graph[cutcoords[3]][i] != ' '){
                            valid = false;
                            break;
                        }
                    }
                }

                if (valid){
                    // CALL FUNCTION DATA STRUCTURE TO ADD CUT
                    
                    for (int i = cutcoords[0]; i < cutcoords[2]; ++i){
                        graph[cutcoords[1]][i] = '-';
                        graph[cutcoords[3]][i] = '-';
                    }
                    for (int i = cutcoords[1]; i < cutcoords[3]; ++i){
                        graph[i][cutcoords[0]] = '|';
                        graph[i][cutcoords[2]] = '|';
                    }
                } else {
                    std::printf("Illegal cut\n");
                }
            } else {
                std::printf("coords out of bounds\n");
            }
        }
        printgraph(graph);
    }
}

int solvemode(std::vector<std::vector<char>> graph){
    return(0);
}

int main(){
    int width;
    int length;
    std::vector<std::vector<char>> graph;
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
        graph.push_back(matrixwidth);
    }

    // main loop
    while (true){
        int x = buildingmode(graph);
        if (x == 0){
            printf("done\n");
            break;
        } else {
            x = solvemode(graph);
            if (x == 0){
                printf("done\n");
                break;
            }
        }
    }
}