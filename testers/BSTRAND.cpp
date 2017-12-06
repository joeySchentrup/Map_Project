#include "tester.h"

TEST_CASE("BSTRAND: Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}
