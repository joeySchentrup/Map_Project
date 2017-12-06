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
        ~Node();
        Node(Node& n);

        K key;
        V element;
        
        Node* left;
        Node* right;
    };

    Node* root;
    Node* find_next_biggest(Node* root);
    Node* do_copy(Node* root);

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    element = n.element;
        
    left = n.left;
    right = n.right;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::~BSTLEAF() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>& BSTLEAF) {
    root = new Node(BSTLEAF.root);

    if(root) {
        root->left = do_copy(BSTLEAF.root->left);
        root->right = do_copy(BSTLEAF.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {
    root = BSTLEAF.root;
    BSTLEAF.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>& BSTLEAF) {
    root = Node(BSTLEAF.root);
    
    if(BSTLEAF.root) {
        root->left = do_copy(BSTLEAF.root->left);
        root->right = do_copy(BSTLEAF.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {
    root = BSTLEAF.root;
    BSTLEAF.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTLEAF<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    Node* temp = root;

    while(true) {
        
        if(ef(root->key, key)) {
            temp->element = value;
            return;
        } else if(cf(root->key, key)) {
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

    Node* temp = root;
    Node* temp_parent = root;

    while(!ef(key,temp->key)) {
        if(!temp)
            throw std::runtime_error("BSTLEAF: Item not in Map");
        
        if(cf(temp->key,key)) {
            temp_parent = temp;
            temp = temp->right;
        } else { 
            temp_parent = temp;
            temp = temp->left;
        }
    }

    if(!temp->right && !temp->left) {
        if(temp_parent != temp) {
            if(cf(temp_parent->key, key)
                temp_parent->right = nullptr;
            else
                temp_parent->left = nullptr;
        } else {
            root = nullptr;
        }
        delete temp;
    } else {
        Node* new_temp = find_next_biggest(temp)
        temp->key = new_temp->key;
        temp->value = new_temp->value;
        new_temp->left = new_temp->right = nullptr;
        delete new_temp;
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& BSTLEAF<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("BSTLEAF: Item not in Map");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {
        if(!temp)
            throw std::runtime_error("BSTLEAF: Item not in Map");
    
        if(cf(root->key,key))
            temp = temp->left;
        else
            temp = temp->right;
    }

    return temp->element;
};

//Private functions!!!!

//This takes in the node to be deleted and finds the left most child of it's right child.
//If there is not right child, it takes the right most child of the left child.
//The Node that is returned to not the node intended to be deleted. What is returned is the 
//Node hold the vaules which will replace the vaules of the node to be deleted.
//The root node must have children otherwise this code would not be run. (Check remove function)
template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTLEAF<K,V,cf,ef>::Node* BSTLEAF<K,V,cf,ef>::find_next_biggest(Node* root) {
    if(!root) 
        return nullptr;

    Node* temp = root->right;
    Node* temp_parent = root;

    if(!temp) {
        temp = temp_parent->left;
        temp_parent->left = temp_parent->left->left;
        return temp;
    }

    while(temp->left) {
        temp_parent = temp;
        temp = temp->left;
    }

    temp_parent->left = temp->right;
    return temp;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTLEAF<K,V,cf,ef>::Node* BSTLEAF<K,V,cf,ef>::do_copy(Node* root) {
    if(!root)
        return nullptr;
    
    Node* new_node = Node(root);
    new_node->left = do_copy(root->left);
    new_node->right = do_copy(root->right);

    return new_node;
};


}

#endif