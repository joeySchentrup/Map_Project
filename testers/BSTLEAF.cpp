#include "tester.h"

TEST_CASE("BSTLEAF:Tests search/insert on terrible order") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);

}

TEST_CASE("BSTLEAF:Tests search/insert on 'random' order") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map->lookup(temp) == temp);
    }

}
