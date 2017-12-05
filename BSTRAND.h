#ifndef BSTRAND_H
#define BSTRAND_H

#include "Map.h"
#include <cstdlib>

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
    Node* do_remove(Node* root, K key;);
    void insert_leaf(V element, K key);
    void insert_root(V element, K key);
    int num_nodes;

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
    num_nodes = 0;
        
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
    ++num_nodes;
    if(!root) {
        root = new Node(value, key);
        return;
    }
    srand (time(NULL));
    
    if(rand() > RAND_MAX/num_nodes)
        insert_leaf(value, key);
    else
        insert_root(value, key);
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::remove(K key) {
    --num_nodes;
    if(!root) 
         throw std::runtime_error("BSTRAND: Item not in Map!");

    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& BSTRAND<K,V,cf,ef>::lookup(K key) {
    
};


}

//private functions
template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::insert_leaf(V element, K key) {
    Node* temp = root;

    while(true) {
        
        if(ef(root, key)) {
            temp->element = value;
            return;
        } else if(cf(root, key)) {
            if(temp->right) {
                temp = temp->right;
            } else {
                temp->right = new Node(value, key);
                return;
            }
        } else {
            if(temp->left) {
                temp = temp->left;
            } else {  
                temp->left = new Node(value, key);
                return;
            }
        }
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::insert_root(V element, K key) {
    
};



#endif