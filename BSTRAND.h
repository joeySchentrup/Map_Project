#ifndef BSTRAND_H
#define BSTRAND_H

#include "Map.h"
#include <cstdlib>
#include <string>

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
class BSTRAND : public Map<K,V,cf,ef> {
public:
    BSTRAND();
    ~BSTRAND() override;
    BSTRAND(BSTRAND<K,V,cf,ef>& BSTRAND); //copy constructor
    BSTRAND(BSTRAND<K,V,cf,ef>&& BSTRAND); //move constructor
    BSTRAND<K,V,cf,ef>& operator=(BSTRAND<K,V,cf,ef>& BSTRAND); // copy assignment operator
    BSTRAND<K,V,cf,ef>& operator=(BSTRAND<K,V,cf,ef>&& BSTRAND); // move assignment

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

    void insert_at_leaf(V value, K key);
    Node* insert_at_root(Node* n, V value, K key);
    int num_nodes;

    Node* r_rotation(Node* n);
    Node* l_rotation(Node* n);
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    value = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    value = n.value;
        
    left = n.left;
    right = n.right;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::BSTRAND() {
    root = nullptr;
    num_nodes = 0;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::~BSTRAND() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>& BSTRAND) {
    root = new Node(*BSTRAND.root);
    num_nodes = BSTRAND.num_nodes;
    if(root) {
        root->left = do_copy(BSTRAND.root->left);
        root->right = do_copy(BSTRAND.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>::BSTRAND(BSTRAND<K,V,cf,ef>&& BSTRAND) {
    root = BSTRAND.root;
    num_nodes = BSTRAND.num_nodes;
    BSTRAND.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>& BSTRAND) {
    root = new Node(*BSTRAND.root);
    num_nodes = BSTRAND.num_nodes;
    if(BSTRAND.root) {
        root->left = do_copy(BSTRAND.root->left);
        root->right = do_copy(BSTRAND.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTRAND<K,V,cf,ef>& BSTRAND<K,V,cf,ef>::operator=(BSTRAND<K,V,cf,ef>&& BSTRAND) {
    root = BSTRAND.root;
    num_nodes = BSTRAND.num_nodes;
    BSTRAND.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTRAND<K,V,cf,ef>::insert( V value, K key ) {
    ++num_nodes;
    //srand (time(NULL));
    
    if(rand() > RAND_MAX/num_nodes)
        insert_at_leaf(value, key);
    else
        root = insert_at_root(root, value, key);
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTRAND<K,V,cf,ef>::remove(K key) {
    --num_nodes;
    root = do_remove(root, key);  
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
V& BSTRAND<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("BSTRAND: Item not in Map. Root DNE!");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {
        if(cf(temp->key,key))
            temp = temp->right;
        else
            temp = temp->left;

        if(!temp)
            throw std::runtime_error("BSTRAND: Item not in Map. Cannot lookup!");
    }

    return temp->value;
};


//private functions
template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTRAND<K,V,cf,ef>::insert_at_leaf(V value, K key) {
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
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::insert_at_root(Node* n, V value, K key) {
    if(!n) {
        return new Node(value, key);
    } else if(cf(key, n->key)) {
        n->left = insert_at_root(n->left, value, key);
        return r_rotation(n);
    } else {
        n->right = insert_at_root(n->right, value, key);
        return l_rotation(n);
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::do_remove(Node* n, K key) {
    Node* temp;
    if(!n) {
        throw std::runtime_error("BSTRAND: Tried to remove item not in Map!");
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
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::find_pred(Node* n) {
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
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::do_copy(Node* n) {
    if(!n)
        return nullptr;
    
    Node* new_node = new Node(*n);
    new_node->left = do_copy(n->left);
    new_node->right = do_copy(n->right);

    return new_node;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::l_rotation(Node* n) {
    Node* temp = n->right;
    n->right = temp->left;
    temp->left = n;
    return temp;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTRAND<K,V,cf,ef>::Node* BSTRAND<K,V,cf,ef>::r_rotation(Node* n) {
    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;
    return temp;
};

}
#endif