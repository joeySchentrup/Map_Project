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
    Node* insert_at_root(Node* root, V value, K key);
    Node* r_rotation(Node* root);
    Node* l_rotation(Node* root);

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    element = n.element;
        
    left = n.left;
    right = n.right;
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
    root = new Node(BSTROOT.root);

    if(root) {
        root->left = do_copy(BSTROOT.root->left);
        root->right = do_copy(BSTROOT.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>::BSTROOT(BSTROOT<K,V,cf,ef>&& BSTROOT) {
    root = BSTROOT.root;
    BSTROOT.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>& BSTROOT) {
    root = Node(BSTROOT.root);
    
    if(BSTROOT.root) {
        root->left = do_copy(BSTROOT.root->left);
        root->right = do_copy(BSTROOT.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>&& BSTROOT) {
    root = BSTROOT.root;
    BSTROOT.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTROOT<K,V,cf,ef>::insert( V value, K key ) {
    root = insert_at_root(root, value, key);
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void BSTROOT<K,V,cf,ef>::remove(K key) {
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
V& BSTROOT<K,V,cf,ef>::lookup(K key) {
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
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::find_next_biggest(Node* root, K key) {
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
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::do_copy(Node* root) {
    if(!root)
        return nullptr;
    
    Node* new_node = Node(root);
    new_node->left = do_copy(root->left);
    new_node->right = do_copy(root->right);

    return new_node;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::insert_at_root(Node* root, V value,K key) {
    if(!root) {
        root = new Node(value, key);
    } else if(cf(key, root->key)) {
        insert_at_root(root->left, value, key);
        root = r_rotation(root);
    } else {
        insert_at_root(root->right, value, key);
        root = l_rotation(root);
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::l_rotation(Node* root) {
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::r_rotation(Node* root) {
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
};


}

#endif