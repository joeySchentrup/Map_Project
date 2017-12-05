#ifndef BSTRAND_H
#define BSTRAND_H

#include "Map.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
class BSTRAND : public Map<K,V,cf,ef> {
public:
    BSTRAND();
    ~BSTRAND() override;
    BSTRAND(BSTRAND<K,V,cf,ef>& BSTRAND); //copy constructor
    BSTRAND(BSTRAND<K,V,cf,ef>&& BSTRAND); //move constructor
    BSTRAND<K,V,cf,ef>& operator=(BSTRAND<K,V,cf,ef>& BSTRAND); // copy assignment operator
    BSTRAND<K,V,cf,ef>& operator=(BSTRAND<K,V,cf,ef>&& BSTRAND); // move assignment

    void insert( V element, K key ) override;
    void remove(K key) override;
    V& lookup(K key) override;

private:
    struct Node {
        Node(V item, K item_key);

        K key;
        V element;
        
        Node* left;
        Node* right;
    };

    Node* root;
    Node* do_remove(Node* root, K key;)

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::~BSTRAND() {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>& BSTRAND) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>&& BSTRAND) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>& BSTRAND) {
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>&& BSTRAND) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::remove(K key) {
    if(!root) 
         throw std::runtime_error("BSTRAND: Item not in Map!");

    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& BSTRAND<K,V,cf,ef>::lookup(K key) {
    
};


}

#endif