#include <iostream>
#include <cassert>

#include "../src/graph.h"


int main(){
    graph inf = graph();

    assert(inf.insert("hello", -55, 500));
    assert(inf.insert("cringe", 400000, -40000));

    graph smal = graph(-30, -30, 30, 30);

    assert(smal.insert("opps", 9, 9));
    assert(!smal.insert("death, destroyer of worlds", -400, 7));

    assert(smal.insert(NOT, 10, 10, 15, 16));
    assert(smal.insert("f", 11, 11));

    assert(inf.insert(smal));
    assert(inf.remove(smal));


    //testing remove Atom:
    std::cout << "testing remove Atom:" << std::endl;
    assert(!inf.remove("spec", 10, 10));
    assert(inf.remove("hello", -55, 500));

    std::cout << "Setting up remove Graph:" << std::endl;
    graph galaxy = graph(-1000, -1000, 1000, 1000);
    graph system = graph(-100, -100, 100, 100);
    graph planet = graph(-10, -10, 10, 10);

    std::cout << "1" << std::endl;
    assert(system.insert(NOT, -99, -99, 99, 99));
    assert(planet.insert(BOX, -9, -9, 9, 9));
    assert(system.insert(NOT, -84, -66, -55, -30));
    assert(galaxy.insert(BOX, -999, -999, 999, 999));

    std::cout << "2" << std::endl;
    assert(planet.insert("tom", 1, 1));
    assert(planet.insert("jerry", 2, 1));
    assert(system.insert("sun", 0, 0));
    assert(galaxy.insert("sigma", -234, 456));

    std::cout << "3" << std::endl;
    assert(galaxy.insert(system));
    assert(galaxy.insert(planet));

    //testing remove Graph:
    std::cout << "testing remove Graph:" << std::endl;
    assert(!inf.remove(planet));
    assert(inf.remove(smal));
    assert(inf.insert(galaxy));
    assert(inf.remove(system));

    //testing remove Cut:
    std::cout << "testing remove Cut:" << std::endl;
    assert(inf.insert(system));
    assert(inf.remove(BOX, -999, -999, 999, 999));
    assert(inf.remove(NOT, -99, -99, 99, 99));
    assert(!inf.remove(TOP, 5, 5, 6, 6));
    

    std::cout << inf.text() << std::endl;

}