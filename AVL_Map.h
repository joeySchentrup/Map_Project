#ifndef AVL_MAP_H
#define AVL_MAP_H

#include "Map.h"

namespace cop3530 {

template<typename T>
class AVL_Map : public Map<T> {
public:
    AVL_Map();
    ~AVL_Map() override;
    AVL_Map(AVL_Map<T>& AVL_Map); //copy constructor
    AVL_Map(AVL_Map<T>&& AVL_Map); //move constructor
    AVL_Map<T>& operator=(AVL_Map<T>& AVL_Map); // copy assignment operator
    AVL_Map<T>& operator=(AVL_Map<T>&& AVL_Map); // move assignment

    void insert( T element, int key ) override;
    void remove(int key) override;
    T search(int key) override;

private:
    struct Node {
        Node(T item, int item_key);

        int key;
        T element;
        
        Node* left;
        int left_height;
        Node* right;
        int right_height;
    };

    Node* root;
    
    Node* ll_rotation(Node* root);
    Node* lr_rotation(Node* root);
    Node* rl_rotation(Node* root);
    Node* rr_rotation(Node* root);

};

template<typename T>
AVL_Map<T>::Node::Node(T item, int item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    left_height = 0;
    right = nullptr;
    right_height = 0 ;
};

template<typename T>
AVL_Map<T>::AVL_Map() {

};

template<typename T>
AVL_Map<T>::~AVL_Map() {

};

template<typename T>
AVL_Map<T>::AVL_Map(AVL_Map<T>& AVL_Map) {

};

template<typename T>
AVL_Map<T>::AVL_Map(AVL_Map<T>&& AVL_Map) {

};

template<typename T>
AVL_Map<T>& AVL_Map<T>::operator=(AVL_Map<T>& AVL_Map) {
    
};

template<typename T>
AVL_Map<T>& AVL_Map<T>::operator=(AVL_Map<T>&& AVL_Map) {

};

template<typename T>
void AVL_Map<T>::insert( T element, int key ) {
    Node* new_node = new Node(element, key);
    if(root->key < key) {

    } else {

    }
};

template<typename T>
void AVL_Map<T>::remove(int key) {
    
};

template<typename T>
T AVL_Map<T>::search(int key) {
    Node* temp = root;

    while(key != temp->key) {
        if(!temp)
            throw std::runtime_error("Item not in AVL_Map");
    
        if(temp->key < key)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return temp->element;
};

//private functions
template<typename T>
typename AVL_Map<T>::Node* AVL_Map<T>::ll_rotation(Node* root) {
    Node* temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;

    return root;
};

template<typename T>
typename AVL_Map<T>::Node* AVL_Map<T>::lr_rotation(Node* root) {
    root = rr_rotation(root);
    return ll_rotation(root);
};

template<typename T>
typename AVL_Map<T>::Node* AVL_Map<T>::rl_rotation(Node* root) {
    root = ll_rotation(root);
    return rr_rotation(root);
};

template<typename T>
typename AVL_Map<T>::Node* AVL_Map<T>::rr_rotation(Node* root) {
    Node* temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;

    return root;
};

}

#endif