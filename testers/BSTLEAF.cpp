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

TEST_CASE("BSTLEAF:Tests remove") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
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

TEST_CASE("BSTLEAF:Tests copy constructor on 'random' order") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map2 = new BSTLEAF<int, int, Functions::cf, Functions::ef>(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2->lookup(temp) == temp);
    }
}

TEST_CASE("BSTLEAF:Tests Move Constructor on 'random' order") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTLEAF<int, int, Functions::cf, Functions::ef> map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("BSTLEAF:Tests Copy Assignment on 'random' order") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTLEAF<int, int, Functions::cf, Functions::ef> map2 = BSTLEAF<int, int, Functions::cf, Functions::ef>();
    map2 = *map;

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("BSTLEAF:Tests Move Assignment on 'random' order") { 

    BSTLEAF<int, int, Functions::cf, Functions::ef>* map = new BSTLEAF<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    BSTLEAF<int, int, Functions::cf, Functions::ef> map2 = BSTLEAF<int, int, Functions::cf, Functions::ef>();
    map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}
