#include "tester.h"

TEST_CASE("BSTLEAF:Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}
