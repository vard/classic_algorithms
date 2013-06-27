/* 
 * File:   red_black_tree_st.h
 * Author: vard
 *
 * Created on 23 Июнь 2013 г., 1:24
 */

#ifndef RED_BLACK_TREE_ST_H
#define	RED_BLACK_TREE_ST_H

#include "st.h"

enum NodeColor {
    BLACK,
    RED
};

template <typename K, typename V> struct RBTreeNode {
    K key;
    V value;
    RBTreeNode<K, V>* left;
    RBTreeNode<K, V>* right;
    int count;
    bool color;

    //bool isRed(RBTreeNode<K, V>* node);

    RBTreeNode(const K& key, const V & value, bool nodeColor);
};

template <typename K, typename V>bool isRed(RBTreeNode<K, V>* node) {
    if (NULL == node) return false;
    return RED == node->color;
}

template <typename K, typename V>RBTreeNode<K, V>::RBTreeNode(const K& key, const V& value, bool nodeColor) :
key(key),
value(value),
left(NULL),
right(NULL),
count(1),
color(nodeColor) {

}

template <typename K, typename V> class RBTreeST : public SymbolTableInterface<K, V> {
private:
    RBTreeNode<K, V>* root;
    RBTreeNode<K, V>* rotateLeft(RBTreeNode<K, V>* node);
    RBTreeNode<K, V>* rotateRight(RBTreeNode<K, V>* node);
    void flipColors(RBTreeNode<K, V>* node);
    RBTreeNode<K, V>* put(RBTreeNode<K, V>* node, const K& key, const V& val);
    int size(RBTreeNode<K, V>* node);
public:
    virtual void put(const K key, const V val);
    virtual V get(K key);
    virtual void remove(K key);
    virtual bool contains(K key);
    virtual int size();
    virtual bool isEmpty();
    RBTreeST();
};

template <typename K, typename V>RBTreeST<K, V>::RBTreeST()
: root(NULL) {

}

template <typename K, typename V>bool RBTreeST<K, V>::contains(K key) {
    return (NULL != get(key));
}

template <typename K, typename V>void RBTreeST<K, V>::remove(K key) {

}

template <typename K, typename V>bool RBTreeST<K, V>::isEmpty() {
    return NULL == size(root);
}

template <typename K, typename V>int RBTreeST<K, V>::size(RBTreeNode<K, V>* node) {
    if (NULL == node)
        return 0;
    return node->count;
}

template <typename K, typename V>int RBTreeST<K, V>::size() {
    return size(root);
}

template <typename K, typename V>RBTreeNode<K, V>* RBTreeST<K, V>::put(RBTreeNode<K, V>* node, const K& key, const V& val) {
    if (NULL == node)
        return new RBTreeNode<K, V > (key, val, RED);

    if (key < node->key) node->left = put(node->left, key, val);
    else if (key > node->key) node->right = put(node->right, key, val);
    else node->value = val;

    node->count = size(node->left) + size(node->right)+1;

    if (isRed(node->right) && !isRed(node->left))
        node = rotateLeft(node);

    if (isRed(node->left) && isRed(node->left->left))
        node = rotateRight(node);

    if (isRed(node->left) && isRed(node->right))
        flipColors(node);

    return node;
}

template <typename K, typename V>void RBTreeST<K, V>::put(const K key, const V val) {
    root = put(root, key, val);
}

template <typename K, typename V> void RBTreeST<K, V>::flipColors(RBTreeNode<K, V>* node) {
    (node->left)->color = BLACK;
    (node->right)->color = BLACK;
    node->color = RED;
}

template <typename K, typename V > RBTreeNode<K, V>* RBTreeST<K, V>::rotateLeft(RBTreeNode<K, V>* node) {
    RBTreeNode<K, V>* auxNodePtr = node->right;
    node->right = auxNodePtr->left;
    node->color = RED;
    auxNodePtr->left = node;
    auxNodePtr->color = BLACK;
    node->count = size(node->right) + size(node->left) + 1;
    auxNodePtr->count = size(auxNodePtr->right) + size(auxNodePtr->left) + 1;
    return auxNodePtr;
}

template <typename K, typename V > RBTreeNode<K, V>* RBTreeST<K, V>::rotateRight(RBTreeNode<K, V>* node) {
    RBTreeNode<K, V>* auxNodePtr = node->left;
    node->left = auxNodePtr->right;
    node->color = RED;
    auxNodePtr->right = node;
    auxNodePtr->color = BLACK;
    node->count = size(node->right) + size(node->left) + 1;
    auxNodePtr->count = size(auxNodePtr->right) + size(auxNodePtr->left)+ 1;
    return auxNodePtr;
}

template <typename K, typename V > V RBTreeST<K, V>::get(K key) {
    RBTreeNode<K, V>* auxNodePtr = root;
    while (auxNodePtr) {
        if (key < auxNodePtr->key)
            auxNodePtr = auxNodePtr->left;
        else if (key > auxNodePtr->key)
            auxNodePtr = auxNodePtr->right;
        else
            return auxNodePtr->value;
    }
    return NULL;
}



#endif	/* RED_BLACK_TREE_ST_H */

