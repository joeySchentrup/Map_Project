#ifndef BSTROOT_H
#define BSTROOT_H

#include "Map.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
class BSTROOT : public Map<K,V,cf,ef> {
public:
    BSTROOT();
    ~BSTROOT() override;
    BSTROOT(BSTROOT<K,V,cf,ef>& BSTROOT); //copy constructor
    BSTROOT(BSTROOT<K,V,cf,ef>&& BSTROOT); //move constructor
    BSTROOT<K,V,cf,ef>& operator=(BSTROOT<K,V,cf,ef>& BSTROOT); // copy assignment operator
    BSTROOT<K,V,cf,ef>& operator=(BSTROOT<K,V,cf,ef>&& BSTROOT); // move assignment

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

    Node* do_copy(Node* root);
    Node* find_pred(Node* n);
    Node* do_remove(Node* n, K key);

    Node* insert_at_root(Node* root, V value, K key);
    Node* r_rotation(Node* root);
    Node* l_rotation(Node* root);

};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    value = item;
        
    left = nullptr;
    right = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::Node::~Node() {
    delete right;
    delete left;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    value = n.value;
        
    left = n.left;
    right = n.right;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::BSTROOT() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::~BSTROOT() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::BSTROOT(BSTROOT<K,V,cf,ef>& BSTROOT) {
    root = new Node(*BSTROOT.root);

    if(root) {
        root->left = do_copy(BSTROOT.root->left);
        root->right = do_copy(BSTROOT.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>::BSTROOT(BSTROOT<K,V,cf,ef>&& BSTROOT) {
    root = BSTROOT.root;
    BSTROOT.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>& BSTROOT) {
    root = new Node(*BSTROOT.root);
    
    if(BSTROOT.root) {
        root->left = do_copy(BSTROOT.root->left);
        root->right = do_copy(BSTROOT.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
BSTROOT<K,V,cf,ef>& BSTROOT<K,V,cf,ef>::operator=(BSTROOT<K,V,cf,ef>&& BSTROOT) {
    root = BSTROOT.root;
    BSTROOT.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTROOT<K,V,cf,ef>::insert( V value, K key ) {
    root = insert_at_root(root, value, key);
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void BSTROOT<K,V,cf,ef>::remove(K key) {
    root = do_remove(root, key);  
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
V& BSTROOT<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("BSTROOT: Item not in Map");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {
        if(cf(temp->key,key))
            temp = temp->right;
        else
            temp = temp->left;

        if(!temp)
            throw std::runtime_error("BSTROOT: Item not in Map");
    }

    return temp->value;
};

//private functions

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::do_remove(Node* n, K key) {
    Node* temp;
    if(!n) {
        throw std::runtime_error("BSTROOT: Tried to remove item not in Map!");
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
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::find_pred(Node* n) {
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
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::do_copy(Node* root) {
    if(!root)
        return nullptr;
    
    Node* new_node = new Node(*root);
    new_node->left = do_copy(root->left);
    new_node->right = do_copy(root->right);

    return new_node;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::insert_at_root(Node* n, V value, K key) {
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
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::l_rotation(Node* n) {
    Node* temp = n->right;
    n->right = temp->left;
    temp->left = n;
    return temp;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename BSTROOT<K,V,cf,ef>::Node* BSTROOT<K,V,cf,ef>::r_rotation(Node* n) {
    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;
    return temp;
};


}

#endif