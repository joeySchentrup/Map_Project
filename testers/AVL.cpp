#define CATCH_CONFIG_MAIN
#include "tester.h"

TEST_CASE("AVL: Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}