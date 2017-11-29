#ifndef MAP_H
#define MAP_H

namespace cop3530 {

template<typename T>
class Map {
public:
    virtual ~Map() {};

    virtual void insert( T element, int key ) = 0;
    virtual void remove(int key) = 0;
    virtual T search(int key) = 0;

};

}
#endif