#ifndef BSTLEAF_H
#define BSTLEAF_H

#include "Map.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
class BSTLEAF : public Map<K,V,cf,ef> {
public:
    BSTLEAF();
    ~BSTLEAF() override;
    BSTLEAF(BSTLEAF<K,V,cf,ef>& BSTLEAF); //copy constructor
    BSTLEAF(BSTLEAF<K,V,cf,ef>&& BSTLEAF); //move constructor
    BSTLEAF<K,V,cf,ef>& operator=(BSTLEAF<K,V,cf,ef>& BSTLEAF); // copy assignment operator
    BSTLEAF<K,V,cf,ef>& operator=(BSTLEAF<K,V,cf,ef>&& BSTLEAF); // move assignment

    void insert( V value, K key ) override;
    void remove(K key) override;
    V& lookup(K key) override;

private:
    struct Node {
        Node(V item, K item_key);
        ~Node();
        Node(Node& n);

        K key;
        V value;
        
        Node* left;
        Node* right;
    };

    Node* root;

    Node* do_copy(Node* n);
    Node* find_pred(Node* n);
    Node* do_remove(Node* n, K key);

};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    value = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    value = n.value;
        
    left = n.left;
    right = n.right;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::BSTLEAF() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::~BSTLEAF() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>& BSTLEAF) {
    root = new Node(*BSTLEAF.root);

    if(root) {
        root->left = do_copy(BSTLEAF.root->left);
        root->right = do_copy(BSTLEAF.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>::BSTLEAF(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {
    root = BSTLEAF.root;
    BSTLEAF.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>& BSTLEAF) {
    root = new Node(*BSTLEAF.root);
    
    if(BSTLEAF.root) {
        root->left = do_copy(BSTLEAF.root->left);
        root->right = do_copy(BSTLEAF.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTLEAF<K,V,cf,ef>& BSTLEAF<K,V,cf,ef>::operator=(BSTLEAF<K,V,cf,ef>&& BSTLEAF) {
    root = BSTLEAF.root;
    BSTLEAF.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTLEAF<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    Node* temp = root;

    while(true) {
        if(ef(temp->key, key)) {
            temp->value = value;
            return;
        } else if(cf(temp->key, key)) {
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

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTLEAF<K,V,cf,ef>::remove(K key) {
    root = do_remove(root, key);    
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
V& BSTLEAF<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("BSTLEAF: Item not in Map. Root DNE!");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {
        if(cf(temp->key,key))
            temp = temp->right;
        else
            temp = temp->left;

        if(!temp)
            throw std::runtime_error("BSTLEAF: Item not in Map. Cannot lookup!");
    }

    return temp->value;
};

//Private functions!!!!


template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTLEAF<K,V,cf,ef>::Node* BSTLEAF<K,V,cf,ef>::do_remove(Node* n, K key) {
    Node* temp;
    if(!n) {
        throw std::runtime_error("BSTLEAF: Tried to remove item not in Map!");
    }
    if(ef(n->key, key)) {
        if(!n->right && !n->left) {
            n->right = n->left = nullptr;
            delete n;
            return nullptr;
        }
        else if(!n->right || !n->left) {
            if(!n->right) {
                temp = n->left;
                n->right = n->left = nullptr;
                delete n;
                return temp;
            }
            else {
                temp = n->right;
                n->right = n->left = nullptr;
                delete n;
                return temp;
            }
        }
        else {
            temp = find_pred(n->left);
            n->value = temp->value;
            n->key = temp->key;
            n->left = do_remove(n->left, n->key);
            return n;
        }
    }
    else if(cf(n->key, key)) {
        n->right = do_remove(n->right, key);
    }
    else if(cf(key, n->key)) {
        n->left = do_remove(n->left, key);
    }
    return n;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTLEAF<K,V,cf,ef>::Node* BSTLEAF<K,V,cf,ef>::find_pred(Node* n) {
    static Node* pred;
    if(!n) {
        return pred;
    }
    else {
        pred = n;
        return find_pred(n->right);
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTLEAF<K,V,cf,ef>::Node* BSTLEAF<K,V,cf,ef>::do_copy(Node* n) {
    if(!n)
        return nullptr;
    
    Node* new_node = new Node(*n);
    new_node->left = do_copy(n->left);
    new_node->right = do_copy(n->right);

    return new_node;
};


}

#endif