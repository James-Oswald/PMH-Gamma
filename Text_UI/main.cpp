<<<<<<< HEAD

#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>


int check_legal_start(std::string input){ // this code checks parenthasis to make sure all starts have endings
    std::vector<char> comp;
    for(char& c : input) {
        if (c == ' '){ // NO SPACES
            return(2);
        }
        if (c == '[' || c =='('){
            comp.push_back(c);
        } else if (c == ']'){
            if (comp.back() == '['){
                comp.pop_back();
            } else {
                return(1);
            }
        } else if (c ==')'){
            if (comp.back() == '('){
                comp.pop_back();
            } else {
                return(1);
            }
        }
    }
    if (comp.empty()){
        return(0);
    }
    return(1);
}


int main(){
    std::vector<std::string> logs;

    while (true){ // loops until valid starting existential graph
        std::cout << "input your valid gamma existential graph (enter 'quit' to quit):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            break;
            std::printf("done\n");
            return(0);
        }
        int legal = check_legal_start(input);
        if (legal == 1){
            std::cout << "error with parenthasis\n";
        } else if (legal == 2){
            std::cout << "NO SPACES\n";
        } else {
            logs.push_back(input);
            break;
        }
    }
    while (true){
        std::cout << "input operation (check operations by entering 'operations'):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            break;
        } else if (input.compare("operations") == 0){
            std::printf("Insertion: insert\n Erasure: erase\n");
            std::printf("Double cut: dcut\n Iteration: iter\n");
            std::printf("Quit: quit\n Check logs: logs\n");
        } else if (input.compare("logs") == 0){
            for(const std::string& i : logs) 
                std::cout << i << std::endl;
        }
    }
    std::printf("done\n");
    return(0);
=======

#include <cstdio>
#include<list>
#include<vector>
#include<string>
#include <iostream>


int check_legal_start(std::string input){ // this code checks parenthasis to make sure all starts have endings
    std::vector<char> comp;
    for(char& c : input) {
        if (c == ' '){ // NO SPACES
            return(2);
        }
        if (c == '[' || c =='('){
            comp.push_back(c);
        } else if (c == ']'){
            if (comp.back() == '['){
                comp.pop_back();
            } else {
                return(1);
            }
        } else if (c ==')'){
            if (comp.back() == '('){
                comp.pop_back();
            } else {
                return(1);
            }
        }
    }
    if (comp.empty()){
        return(0);
    }
    return(1);
}


int main(){
    std::vector<std::string> logs;

    while (true){ // loops until valid starting existential graph
        std::cout << "input your valid gamma existential graph (enter 'quit' to quit):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            break;
            std::printf("done\n");
            return(0);
        }
        int legal = check_legal_start(input);
        if (legal == 1){
            std::cout << "error with parenthasis\n";
        } else if (legal == 2){
            std::cout << "NO SPACES\n";
        } else {
            logs.push_back(input);
            break;
        }
    }
    while (true){
        std::cout << "input operation (check operations by entering 'operations'):\n";
        std::string input;
        std::getline(std::cin, input);
        if (input.compare("quit") == 0){
            break;
        } else if (input.compare("operations") == 0){
            std::printf("Insertion: insert\n Erasure: erase\n");
            std::printf("Double cut: dcut\n Iteration: iter\n");
            std::printf("Quit: quit\n Check logs: logs\n");
        } else if (input.compare("logs") == 0){
            for(const std::string& i : logs) 
                std::cout << i << std::endl;
        }
    }
    std::printf("done\n");
    return(0);
>>>>>>> 701eca42d07ee7aeadc0beaa62ee324f73456774
}