#ifndef BSTLEAF_H
#define BSTLEAF_H

#include "Map.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
class BSTLEAF : public Map<K,V,cf,ef> {
public:
    BSTLEAF();
    ~BSTLEAF() override;
    BSTLEAF(BSTLEAF<K,V,cf,ef>& BSTLEAF); //copy constructor
    BSTLEAF(BSTLEAF<K,V,cf,ef>&& BSTLEAF); //move constructor
    BSTLEAF<K,V,cf,ef>& operator=(BSTLEAF<K,V,cf,ef>& BSTLEAF); // copy assignment operator
    BSTLEAF<K,V,cf,ef>& operator=(BSTLEAF<K,V,cf,ef>&& BSTLEAF); // move assignment

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
BSTLEAF<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::~BSTLEAF() {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>& BSTLEAF) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>& BSTLEAF) {
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTLEAF<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
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
void BSTLEAF<K,V,cf,ef>::remove(K key) {
    if(!root) 
         throw std::runtime_error("BSTLEAF: Item not in Map!");

    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& BSTLEAF<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("AVL: Item not in Map");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {
        if(!temp)
            throw std::runtime_error("AVL: Item not in Map");
    
        if(cf(root->key,key))
            temp = temp->left;
        else
            temp = temp->right;
    }

    return temp->element;
};


}

#endif