#include "tester.h"

TEST_CASE("BSTRAND: Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}

/*TEST_CASE("BSTRAND: Tests search/insert on 'random' order") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();

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
    
}*/

TEST_CASE("BSTRAND:Tests remove") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) {
        map->insert(i, i);
    }

    for(int i = 0; i != 50; ++i) {
        map->remove(i);
    }

    for(int i = 0; i != 100; ++i) {
        if(i < 50 )REQUIRE_THROWS(map->lookup(i));
        else REQUIRE(map->lookup(i) == i);
    }
}

TEST_CASE("BSTRAND:Tests copy constructor") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) {
        map->insert(i, i);
    }

    BSTRAND<int, int, Functions::cf, Functions::ef>* map2 = new BSTRAND<int, int, Functions::cf, Functions::ef>(*map);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map2->lookup(i) == i);
}

TEST_CASE("BSTRAND:Tests Move Constructor") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) {
        map->insert(i, i);
    }

    BSTRAND<int, int, Functions::cf, Functions::ef> map2 = std::move(*map);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map2.lookup(i) == i);
}

TEST_CASE("BSTRAND:Tests Copy Assignment") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) {
        map->insert(i, i);
    }

    BSTRAND<int, int, Functions::cf, Functions::ef> map2 = BSTRAND<int, int, Functions::cf, Functions::ef>();
    map2 = *map;

    for(int i = 0; i != 100; ++i)
        REQUIRE(map2.lookup(i) == i);
}

TEST_CASE("BSTRAND:Tests Move Assignment") { 

    BSTRAND<int, int, Functions::cf, Functions::ef>* map = new BSTRAND<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) {
        map->insert(i, i);
    }

    BSTRAND<int, int, Functions::cf, Functions::ef> map2 = BSTRAND<int, int, Functions::cf, Functions::ef>();
    map2 = std::move(*map);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map2.lookup(i) == i);
}

