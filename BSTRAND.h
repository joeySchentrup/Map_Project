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
        ~Node();
        Node(Node& n);

        K key;
        V element;
        
        Node* left;
        Node* right;
    };

    Node* root;

    Node* find_next_biggest(Node* root, K key);
    Node* do_copy(Node* root);

    void insert_leaf(V element, K key);
    void insert_root(V element, K key);
    int num_nodes;

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    element = n.element;
        
    left = n.left;
    right = n.right;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND() {
    root = nullptr;
    num_nodes = 0;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::~BSTRAND() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>& BSTRAND) {
    root = new Node(BSTRAND.root);

    if(root) {
        root->left = do_copy(BSTRAND.root->left);
        root->right = do_copy(BSTRAND.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>&& BSTRAND) {
    root = BSTRAND.root;
    BSTRAND.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>& BSTRAND) {
    root = Node(BSTRAND.root);
    
    if(BSTRAND.root) {
        root->left = do_copy(BSTRAND.root->left);
        root->right = do_copy(BSTRAND.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>&& BSTRAND) {
    root = BSTRAND.root;
    BSTRAND.root = nullptr;
    return *this;
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
V& BSTRAND<K,V,cf,ef>::lookup(K key) {
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


//private functions
template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTRAND<K,V,cf,ef>::insert_leaf(V value, K key) {
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
void BSTRAND<K,V,cf,ef>::insert_root(V element, K key) {
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::find_next_biggest(Node* root, K key) {
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
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::do_copy(Node* root) {
    if(!root)
        return nullptr;
    
    Node* new_node = Node(root);
    new_node->left = do_copy(root->left);
    new_node->right = do_copy(root->right);

    return new_node;
};


}
#endif