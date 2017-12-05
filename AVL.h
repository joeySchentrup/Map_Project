#ifndef AVL_H
#define AVL_H

#include "Map.h"
#include "./imports/Stack.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
class AVL : public Map<K,V,cf,ef> {
public:
    AVL();
    ~AVL() override;
    AVL(AVL<K,V,cf,ef>& AVL); //copy constructor
    AVL(AVL<K,V,cf,ef>&& AVL); //move constructor
    AVL<K,V,cf,ef>& operator=(AVL<K,V,cf,ef>& AVL); // copy assignment operator
    AVL<K,V,cf,ef>& operator=(AVL<K,V,cf,ef>&& AVL); // move assignment

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
        int left_height;
        Node* right;
        int right_height;
    };

    Node* root;
    Node* do_remove(Node* root, K key;)
    
    Node* ll_rotation(Node* root);
    Node* lr_rotation(Node* root);
    Node* rl_rotation(Node* root);
    Node* rr_rotation(Node* root);

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    element = item;
        
    left = nullptr;
    left_height = 0;
    right = nullptr;
    right_height = 0 ;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::Node::~Node() {
    delete left;
    delete right;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::AVL() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::~AVL() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::AVL(AVL<K,V,cf,ef>& AVL) {
    Stack<Node>* stack = new Stack<Node>();
    stack->push(AVL.root);
    Node* temp = root = new Node(AVL.root);

    while(!stack->isEmpty()) {
        if(temp->left)
            stack->push(temp->left);
        if(temp->right)
            stack->push(temp->right);
        
        
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>::AVL(AVL<K,V,cf,ef>&& AVL) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>& AVL<K,V,cf,ef>::operator=(AVL<K,V,cf,ef>& AVL) {
    
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
AVL<K,V,cf,ef>& AVL<K,V,cf,ef>::operator=(AVL<K,V,cf,ef>&& AVL) {

};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void AVL<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    Node* temp = root;
    while(true) {
        if(cf(temp->key,key)) {
            temp->left_height += 1;
            if(temp->left) {
                temp = temp->left;
             } else {
                temp->left = new Node(value, key);
                return;
            }
        } else if(ef(temp->key, key)) {
            throw std::runtime_error("AVL: Item already in Map!");
        } else {
            temp->right_height += 1;
            if(temp->right) {
                temp = temp->right;
             } else {
                temp->right = new Node(value, key);
                return;
            }
        }
    }

    if(root->left_height - root->right_height > 1) {
        if(root->left->left_height - root->left->right_height > 0) root = ll_rotation(root);
        else root = lr_rotation(root);
    }
    else if(root->left_height - root->right_height < 1) {
        if(root->right->left_height - root->right->right_height < 0) root = rr_rotation(root);
        else root = rl_rotation(root);
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void AVL<K,V,cf,ef>::remove(K key) {
    if(!root) 
         throw std::runtime_error("AVL: Item not in Map!");

    root = do_remove(root, key);

    if(root->left_height - root->right_height > 1) {
        if(root->left->left_height - root->left->right_height > 0) root = ll_rotation(root);
        else root = lr_rotation(root);
    }
    else if(root->left_height - root->right_height < 1) {
        if(root->right->left_height - root->right->right_height < 0) root = rr_rotation(root);
        else root = rl_rotation(root);
    }
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
V& AVL<K,V,cf,ef>::lookup(K key) {
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

//private functions
template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::ll_rotation(Node* root) {
    Node* temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;

    return root;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::lr_rotation(Node* root) {
    root = rr_rotation(root->left);
    return ll_rotation(root);
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::rl_rotation(Node* root) {
    root = ll_rotation(root->right);
    return rr_rotation(root);
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::rr_rotation(Node* root) {
    Node* temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;

    return root;
};

template<typename K, typename V,  bool (*cf)(V,V),  bool (*ef)(V,V)>
void AVL<K,V,cf,ef>::do_remove(K key) {
    if(!root) 
         throw std::runtime_error("AVL: Item not in Map!");

    Node* temp = root;
    Node* temp_parent = root;
    while(true) {
        if(cf(temp->key,key)) {
            if(!temp->left) 
                throw std::runtime_error("AVL: Item not in Map!");

            temp_parent = temp;
            temp->left_height -= 1;
            temp = temp->left;
        } else if(ef(temp->key, key)) {
            if(!temp->left && !temp->right) {
                if(temp == temp_parent->right)
                    temp_parent->right = nullptr;
                else
                    temp_parent->left = nullptr;

                delete temp;
            } else if(!temp->left) {
                if(temp == temp_parent->right)
                    temp_parent->right = temp->right;
                else
                    temp_parent->left = temp->right;
                
                delete temp
            } else if(!temp->right) {
                if(temp == temp_parent->right)
                    temp_parent->right = temp->left;
                else
                    temp_parent->left = temp->left;
                
                delete temp
            } else {
                while(temp) {
                   
                }
            }
        } else {
            if(!temp->right) 
                throw std::runtime_error("AVL: Item not in Map!");

            temp_parent = temp;
            temp->right_height -= 1;
            temp = temp->right;
        }
    }

    if(root->left_height - root->right_height > 1) {
        if(root->left->left_height - root->left->right_height > 0) root = ll_rotation(root);
        else root = lr_rotation(root);
    }
    else if(root->left_height - root->right_height < 1) {
        if(root->right->left_height - root->right->right_height < 0) root = rr_rotation(root);
        else root = rl_rotation(root);
    }
};

}

#endif