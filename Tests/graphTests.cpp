#include <iostream>
#include <cassert>

#include "../src/graph.h"


int main(){



    
    std::cout << "testing Graph:" << std::endl;
    graph inf = graph();

    assert(inf.insert("hello", -55, 500));
    assert(inf.insert("cringe", 400000, -40000));
    assert(inf.insert(BOX, -8000, -8000, -7500, -7500));
    
    graph smal = graph(-30, -30, 30, 30);

    assert(smal.insert("opps", 9, 9));
    assert(smal.contains("opps", 9, 9));
    assert(!smal.insert("death, destroyer of worlds", -400, 7));

    assert(smal.insert(NOT, 10, 10, 15, 16));
    assert(smal.insert("f", 11, 11));

    assert(smal.contains(NOT, 10, 10, 15, 16));

    assert(inf.insert(smal));
    assert(inf.contains(smal));


    //testing remove Atom:
    std::cout << "testing remove Atom:" << std::endl;
    assert(!inf.remove("spec", 10, 10));
    assert(inf.remove("hello", -55, 500));

    std::cout << "Setting up remove Graph:" << std::endl;
    graph galaxy = graph(-1000, -1000, 1000, 1000);
    graph system = graph(-100, -100, 100, 100);
    graph planet = graph(-10, -10, 10, 10);

    assert(system.insert(NOT, -99, -99, 99, 99));
    assert(planet.insert(BOX, -9, -9, 9, 9));
    assert(system.insert(NOT, -84, -66, -55, -30));
    assert(galaxy.insert(BOX, -999, -999, 999, 999));

    assert(planet.insert("tom", 1, 1));
    assert(planet.insert("jerry", 2, 2));
    assert(system.insert("sun", -11, 0));
    assert(galaxy.insert("sigma", -234, 456));

    std::cout << galaxy.text() << std::endl;
    std::cout << system.text() << std::endl;
    assert(galaxy.insert(system));
    std::cout << galaxy.text() << std::endl;
    assert(galaxy.contains(system));
    assert(galaxy.insert(planet));

    //testing remove Graph:
    std::cout << "testing remove Graph:" << std::endl;
    assert(!inf.remove(planet));
    assert(inf.remove(smal));
    assert(inf.insert(galaxy));
    assert(!inf.remove(system));
    assert(inf.remove(planet));
    assert(inf.remove(system));

    //testing remove Cut:
    std::cout << "testing remove Cut:" << std::endl;
    assert(inf.insert(system));
    assert(inf.remove(BOX, -999, -999, 999, 999));
    assert(inf.remove(NOT, -99, -99, 99, 99));
    assert(!inf.remove(TOP, 5, 5, 6, 6));

    std::cout << inf.text() << std::endl;

    //Testing iterating down in add 
    //A.k.a test if add subgraph puts things that are inside of it in the right place.
    //TODO: WRITE THESE TESTS

    //testing movecut
    graph foo = graph();
    assert(foo.insert(NOT, 10, 10, 20, 20));
    assert(foo.contains(NOT, 10, 10, 20, 20));
    int coords1[4] = {10, 10, 20, 20};
    assert(foo.moveCut(NOT, coords1, 10, -10));
    assert(foo.contains(NOT, 20, 0, 30, 10));
    assert(foo.insert(BOX, 20, 11, 30, 20));
    int coords2[4] = {20, 11, 30, 20};
    assert(!foo.moveCut(BOX, coords2, 0, -2));

    std::cout << "tests ran sucsessfully" << std::endl;

}