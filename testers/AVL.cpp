#define CATCH_CONFIG_MAIN
#include "tester.h"

TEST_CASE("AVL: Tests search") { 

    Map<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    for(int i = 0; i != 100; ++i) 
        map->insert(i, i);

    for(int i = 0; i != 100; ++i)
        REQUIRE(map->lookup(i) == i);
    
}

TEST_CASE("AVL: Tests search/insert on 'random' order") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();

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

TEST_CASE("AVL:Tests remove") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
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

TEST_CASE("AVL:Tests copy constructor on 'random' order") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    AVL<int, int, Functions::cf, Functions::ef>* map2 = new AVL<int, int, Functions::cf, Functions::ef>(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2->lookup(temp) == temp);
    }
}

TEST_CASE("AVL:Tests Move Constructor on 'random' order") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    AVL<int, int, Functions::cf, Functions::ef> map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("AVL:Tests Copy Assignment on 'random' order") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    AVL<int, int, Functions::cf, Functions::ef> map2 = AVL<int, int, Functions::cf, Functions::ef>();
    map2 = *map;

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

TEST_CASE("AVL:Tests Move Assignment on 'random' order") { 

    AVL<int, int, Functions::cf, Functions::ef>* map = new AVL<int, int, Functions::cf, Functions::ef>();
    
    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        map->insert(temp, temp);
    }

    AVL<int, int, Functions::cf, Functions::ef> map2 = AVL<int, int, Functions::cf, Functions::ef>();
    map2 = std::move(*map);

    srand(7);
    for(int i = 0; i != 100; ++i) {
        int temp = rand();
        REQUIRE(map2.lookup(temp) == temp);
    }
}

