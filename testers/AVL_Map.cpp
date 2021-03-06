#define CATCH_CONFIG_MAIN
#include "tester.h"

TEST_CASE("Tests search") { 

    Map<int>* map = new AVL_Map<int>();

    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->search(i) == i);
    
}
