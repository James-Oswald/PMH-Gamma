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

    std::cout << inf.text() << std::endl;

}