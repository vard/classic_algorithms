#ifndef __BINARY_TREE_ST_H__
#define __BINARY_TREE_ST_H__

template <typename K, typename V> struct TreeNode{
    K key;
    V value;
    TreeNode<K,V>* left;
    TreeNode<K,V>* right;
    TreeNode(const K& key, const V& value);
};

template <typename K, typename V>TreeNode<K,V>::TreeNode(const K& key, const V& value)
:key(key),
value(value),
left(NULL),
right(NULL){
}

template <typename K, typename V> class BinTreeST : public SymbolTableInterface<K,V>{
private:
    struct TreeNode<K,V>* root;
    TreeNode<K,V>* put(struct TreeNode<K,V>* node, const K& key, const V& value);
    const TreeNode<K,V>* floor(const TreeNode<K,V>* Node, const K& key);
public:
    BinTreeST();
    bool isEmpty();
    void put(const K key, const V val);
    V get(K key);
    void remove(K key);
    bool contains(K key);
    int size();
    V max();
    V min();
    K floor(K key);
};

template <typename K, typename V>const TreeNode<K,V>* BinTreeST<K,V>::floor(const TreeNode<K,V>* Node, const K& key){
    if(NULL==Node){
        return NULL;
    }
    if(Node->key == key){
        return Node;
    }
    if(key < Node->key){
        return floor(Node->left, key);
    }

    const TreeNode<K,V>* tmpNode = floor(Node->right, key);
    if(NULL == tmpNode)
        return Node;
    else 
        return tmpNode;
    
}

template <typename K, typename V>K BinTreeST<K,V>::floor(K key){
    const TreeNode<K,V>* tmpNode = floor(root, key);
    if(NULL==tmpNode)
        return NULL;

    return tmpNode->key;
}

template <typename K, typename V>V BinTreeST<K,V>::min(){
    TreeNode<K,V>* largestValueNode = root;
    if(!root){
        return null;
    }
    while(NULL!=largestValueNode->left){
        largestValueNode = largestValueNode->left;
    }
    return largestValueNode->value;
}


template <typename K, typename V>V BinTreeST<K,V>::max(){
    TreeNode<K,V>* largestValueNode = root;
    if(!root){
        return null;
    }
    while(NULL!=largestValueNode->right){
        largestValueNode = largestValueNode->right;
    }
    return largestValueNode->value;
}

template <typename K, typename V>int BinTreeST<K,V>::size(){
    return NULL;
}

template <typename K, typename V>bool BinTreeST<K,V>::contains(K key){
    return NULL;
}

template <typename K, typename V>void BinTreeST<K,V>::remove(K key){
    //return NULL;
}

template <typename K, typename V>TreeNode<K,V>* BinTreeST<K,V>::put(struct TreeNode<K,V>* node, const K& key, const V& value){
    if(!node) return new TreeNode<K,V>(key,value);
    if(key<node->key) node->left = put(node->left, key, value);
    if(key>node->key) node->right = put(node->right, key, value);
    if(key==node->key) node->value = value;
    return node;
}

template <typename K, typename V>void BinTreeST<K,V>::put(const K key, const V val){
    root = put(root, key, val);
}

template <typename K, typename V>V BinTreeST<K,V>::get(K key){
    TreeNode<K,V>* tempNode = root;
    while(NULL!=tempNode){
        if(key<(tempNode->key)) tempNode = tempNode->left;
        if(key>(tempNode->key)) tempNode = tempNode->right;
        if(key==(tempNode->key)) return tempNode->value;
    }
    return NULL;
}

template <typename K, typename V>BinTreeST<K,V>::BinTreeST()
:root(NULL){}

template <typename K, typename V>bool BinTreeST<K,V>::isEmpty(){
    return (NULL == root);
}

#endif