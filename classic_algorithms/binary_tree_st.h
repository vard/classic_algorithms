#ifndef __BINARY_TREE_ST_H__
#define __BINARY_TREE_ST_H__

template <typename K, typename V> struct TreeNode{
    K key;
    V value;
    TreeNode<K,V>* left;
    TreeNode<K,V>* right;
    int count;
    TreeNode(const K& key, const V& value);
};

template <typename K, typename V>TreeNode<K,V>::TreeNode(const K& key, const V& value)
:key(key),
value(value),
left(NULL),
right(NULL),
count(1){
}

template <typename K, typename V> class BinTreeST : public SymbolTableInterface<K,V>{
private:
    struct TreeNode<K,V>* root;
    TreeNode<K,V>* put(struct TreeNode<K,V>* node, const K& key, const V& value);
    const TreeNode<K,V>* floor(const TreeNode<K,V>* node, const K& key);
    const TreeNode<K,V>* ceiling(const TreeNode<K,V>* node, const K& key);
    TreeNode<K,V>* remove(TreeNode<K,V>* node, const K& key);
    int size(const TreeNode<K,V>* node);
    int rank(const TreeNode<K,V>* node, const K& key);
    TreeNode<K,V>* deleteMin(TreeNode<K,V>* node);
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
    K floor(const K& key);
    K ceiling(const K& key);
    int rank(const K& key);
    void deleteMin();

};

template <typename K, typename V>void BinTreeST<K,V>::deleteMin(){
    root = deleteMin(root);
}

template <typename K, typename V>TreeNode<K,V>* BinTreeST<K,V>::deleteMin(TreeNode<K,V>* node){
    if(NULL == node) return NULL;
    if(NULL == node->left){
        TreeNode<K,V>* tmpNode = node->right;
        delete node;
        return tmpNode;
    }
    node->left = deleteMin(node->left);
    node->count = 1 + size(node->left) + size(node->right);
    return node;
}

template <typename K, typename V>int BinTreeST<K,V>::rank(const TreeNode<K,V>* node, const K& key){
    if(NULL == node)
        return 0;

    if(key == node->key)
        return size(node->left);
    if(key < node->key)
        return rank(node->left, key);
    if(key > node->key)
        return 1+size(node->left) + rank(node->right, key);
}

template <typename K, typename V>int BinTreeST<K,V>::rank(const K& key){
    return rank(root, key);
}

template <typename K, typename V>int BinTreeST<K,V>::size(){
    return size(root);
}

template <typename K, typename V>int BinTreeST<K,V>::size(const TreeNode<K,V>* node){
    if(NULL == node)
        return 0;
    return node->count;
}

template <typename K, typename V>const TreeNode<K,V>* BinTreeST<K,V>::ceiling(const TreeNode<K,V>* node, const K& key){
  if(NULL==node){
        return NULL;
    }
    if(node->key == key){
        return node;
    }
    if(key > node->key){
        return ceiling(node->right, key);
    }

    const TreeNode<K,V>* tmpNode = ceiling(node->left, key);
    if(NULL == tmpNode)
        return node;
    else
        return tmpNode;
}

template <typename K, typename V>K BinTreeST<K,V>::ceiling(const K& key){
    const TreeNode<K,V>* tmpNode = ceiling(root, key);
    if(NULL==tmpNode)
        return NULL;

    return tmpNode->key;
}

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

template <typename K, typename V>K BinTreeST<K,V>::floor(const K& key){
    const TreeNode<K,V>* tmpNode = floor(root, key);
    if(NULL==tmpNode)
        return NULL;

    return tmpNode->key;
}

template <typename K, typename V>V BinTreeST<K,V>::min(){
    TreeNode<K,V>* largestValueNode = root;
    if(!root){
        return NULL;
    }
    while(NULL!=largestValueNode->left){
        largestValueNode = largestValueNode->left;
    }
    return largestValueNode->value;
}


template <typename K, typename V>V BinTreeST<K,V>::max(){
    TreeNode<K,V>* largestValueNode = root;
    if(!root){
        return NULL;
    }
    while(NULL!=largestValueNode->right){
        largestValueNode = largestValueNode->right;
    }
    return largestValueNode->value;
}

template <typename K, typename V>bool BinTreeST<K,V>::contains(K key){
    return NULL;
}

template <typename K, typename V>TreeNode<K,V>* BinTreeST<K,V>::remove(TreeNode<K,V>* node, const K& key){

}

template <typename K, typename V>void BinTreeST<K,V>::remove(K key){
    remove(root, key);
}

template <typename K, typename V>TreeNode<K,V>* BinTreeST<K,V>::put(struct TreeNode<K,V>* node, const K& key, const V& value){
    if(!node) return new TreeNode<K,V>(key,value);
    if(key<node->key) node->left = put(node->left, key, value);
    else if(key>node->key) node->right = put(node->right, key, value);
    else if(key==node->key) node->value = value;
    node->count = 1 + size(node->left) + size(node->right);
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