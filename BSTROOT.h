#ifndef BSTROOT_H
#define BSTROOT_H

#include "Map.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
class BSTROOT : public Map<K,V,cf,ef> {
public:
    BSTROOT();
    ~BSTROOT() override;
    BSTROOT(BSTROOT<K,V,cf,ef>& BSTROOT); //copy constructor
    BSTROOT(BSTROOT<K,V,cf,ef>&& BSTROOT); //move constructor
    BSTROOT<K,V,cf,ef>& operator=(BSTROOT<K,V,cf,ef>& BSTROOT); // copy assignment operator
    BSTROOT<K,V,cf,ef>& operator=(BSTROOT<K,V,cf,ef>&& BSTROOT); // move assignment

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
    Node* do_remove(Node* root, K key);

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::BSTROOT() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::~BSTROOT() {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::BSTROOT(BSTROOT<K,V,cf,ef>& BSTROOT) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::BSTROOT(BSTROOT<K,V,cf,ef>&& BSTROOT) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>& BSTROOT) {
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>&& BSTROOT) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTROOT<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTROOT<K,V,cf,ef>::remove(K key) {
    if(!root) 
         throw std::runtime_error("BSTROOT: Item not in Map!");

    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& BSTROOT<K,V,cf,ef>::lookup(K key) {
    
};


}

#endif