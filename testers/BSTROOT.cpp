#include "tester.h"

TEST_CASE("BSTROOT: Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}

TEST_CASE("BSTROOT: Tests search/insert on 'random' order") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();

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

TEST_CASE("BSTROOT:Tests remove") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    srand(7);
    for(int i = 0; i != 50; ++i) {
        int temp = rand();
        map->remove(temp);
    }

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        if(i < 50 )REQUIRE_THROWS(map->lookup(temp));
        else REQUIRE(map->lookup(temp) == temp);
    }
}

TEST_CASE("BSTROOT:Tests copy constructor on 'random' order") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTROOT<int, int, Functions::cf, Functions::ef>* map2 = new BSTROOT<int, int, Functions::cf, Functions::ef>(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2->lookup(temp) == temp);
    }
}

TEST_CASE("BSTROOT:Tests Move Constructor on 'random' order") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTROOT<int, int, Functions::cf, Functions::ef> map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("BSTROOT:Tests Copy Assignment on 'random' order") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTROOT<int, int, Functions::cf, Functions::ef> map2 = BSTROOT<int, int, Functions::cf, Functions::ef>();
    map2 = *map;

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("BSTROOT:Tests Move Assignment on 'random' order") { 

    BSTROOT<int, int, Functions::cf, Functions::ef>* map = new BSTROOT<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTROOT<int, int, Functions::cf, Functions::ef> map2 = BSTROOT<int, int, Functions::cf, Functions::ef>();
    map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

