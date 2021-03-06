#ifndef AVL_H
#define AVL_H

#include "Map.h"
#include "./imports/Stack.h"

namespace cop3530 {

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
class AVL : public Map<K,V,cf,ef> {
public:
    AVL();
    ~AVL() override;
    AVL(AVL<K,V,cf,ef>& AVL); //copy constructor
    AVL(AVL<K,V,cf,ef>&& AVL); //move constructor
    AVL<K,V,cf,ef>& operator=(AVL<K,V,cf,ef>& AVL); // copy assignment operator
    AVL<K,V,cf,ef>& operator=(AVL<K,V,cf,ef>&& AVL); // move assignment

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
        
        Node* left = nullptr;
        int left_height = 0;
        Node* right = nullptr;
        int right_height = 0;
    };

    Node* root;
    Node* find_pred(Node* n);
    Node* do_remove(Node* n, K key);
    Node* do_copy(Node* root);
    
    Node* ll_rotation(Node* root);
    Node* lr_rotation(Node* root);
    Node* rl_rotation(Node* root);
    Node* rr_rotation(Node* root);

};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::Node::Node(V item, K item_key) {
    key = item_key;
    value = item;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::Node::~Node() {
    delete left;
    delete right;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::Node::Node(Node& n) {
    key = n.key;
    value = n.value;
        
    left = n.left;
    left_height = n.left_height;
    right = n.right;
    right_height = n.right_height;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::AVL() {
    root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::~AVL() {
    delete root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::AVL(AVL<K,V,cf,ef>& AVL) {
    root = new Node(*AVL.root);

    if(root) {
        root->left = do_copy(AVL.root->left);
        root->right = do_copy(AVL.root->right); 
    }
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>::AVL(AVL<K,V,cf,ef>&& AVL) {
    root = AVL.root;
    AVL.root = nullptr;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>& AVL<K,V,cf,ef>::operator=(AVL<K,V,cf,ef>& AVL) {
    root = new Node(*AVL.root);
    
    if(AVL.root) {
        root->left = do_copy(AVL.root->left);
        root->right = do_copy(AVL.root->right); 
    }

    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
AVL<K,V,cf,ef>& AVL<K,V,cf,ef>::operator=(AVL<K,V,cf,ef>&& AVL) {
    root = AVL.root;
    AVL.root = nullptr;
    return *this;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void AVL<K,V,cf,ef>::insert( V value, K key ) {
    if(!root) {
        root = new Node(value, key);
        return;
    }
    
    Node* temp = root;

    while(true) {
        if(ef(temp->key, key)) {
            throw std::runtime_error("AVL: Item already in Map!");
        } else if(cf(temp->key, key)) {
            temp->right_height += 1;
            if(temp->right) {
                temp = temp->right;
             } else {
                temp->right = new Node(value, key);
                return;
            }
        } else {
            temp->left_height += 1;
            if(temp->left) {
                temp = temp->left;
            } else {
                temp->left = new Node(value, key);
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

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
void AVL<K,V,cf,ef>::remove(K key) {
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

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
V& AVL<K,V,cf,ef>::lookup(K key) {
    if(!root) {
        throw std::runtime_error("AVL: Item not in Map");
    }
    
    Node* temp = root;

    while(!ef(key,temp->key)) {    
        if(cf(temp->key,key))
            temp = temp->right;
        else
            temp = temp->left;
        
        if(!temp)
            throw std::runtime_error("AVL: Item not in Map");
    }

    return temp->value;
};

//private functions
template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::do_remove(Node* n, K key) {
    Node* temp;
    if(!n) {
        throw std::runtime_error("AVL: Tried to remove item not in Map!");
    }
    if(ef(n->key, key)) {
        if(!n->right && !n->left) {
            n->right = n->left = nullptr;
            delete n;
            return nullptr;
        } else if(!n->right || !n->left) {
            if(!n->right) {
                temp = n->left;
                n->right = n->left = nullptr;
                delete n;
                return temp;
            } else {
                temp = n->right;
                n->right = n->left = nullptr;
                delete n;
                return temp;
            }
        } else {
            temp = find_pred(n->left);
            n->value = temp->value;
            n->key = temp->key;
            //TODO: figure out how to do this. With this uncommented, it cause a seg fault
            //n->left_height -= 1;
            n->left = do_remove(n->left, n->key);
            return n;
        }
    } else if(cf(n->key, key)) {
        //n->right_height -= 1;
        n->right = do_remove(n->right, key);
    } else if(cf(key, n->key)) {
        //n->left_height -= 1;
        n->left = do_remove(n->left, key);
    }
    
    return n;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::find_pred(Node* n) {
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
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::ll_rotation(Node* root) {
    Node* temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;

    return root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::lr_rotation(Node* root) {
    root->left = rr_rotation(root->left);
    return ll_rotation(root);
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::rl_rotation(Node* root) {
    root->right = ll_rotation(root->right);
    return rr_rotation(root);
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::rr_rotation(Node* root) {
    Node* temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;

    return root;
};

template<typename K, typename V,  bool (*cf)(K,K),  bool (*ef)(K,K)>
typename AVL<K,V,cf,ef>::Node* AVL<K,V,cf,ef>::do_copy(Node* root) {
    if(!root)
        return nullptr;
    
    Node* new_node = new Node(*root);
    new_node->left = do_copy(root->left);
    new_node->right = do_copy(root->right);

    return new_node;
};

}

#endif