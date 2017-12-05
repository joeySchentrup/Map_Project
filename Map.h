#ifndef MAP_H
#define MAP_H

#include <iostream>

namespace cop3530 {

template<typename Key_Type, typename Value_Type,  bool (*comparison_function)(Key_Type,Key_Type), bool (*equality_function)(Key_Type,Key_Type) >
class Map {
public:
    virtual ~Map() {};

    virtual void insert( Value_Type element, Key_Type key ) = 0;
    virtual void remove(Key_Type key) = 0;
    virtual Value_Type& lookup(Key_Type key) = 0;

};

}
#endif