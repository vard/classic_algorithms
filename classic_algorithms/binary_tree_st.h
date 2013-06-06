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
public:
    BinTreeST();
    bool isEmpty();
    void put(const K key, const V val);
    V get(K key);
    void remove(K key);
    bool contains(K key);
    int size();
  
};

template <typename K, typename V>int BinTreeST<K,V>::size(){
    return NULL;
}

template <typename K, typename V>bool BinTreeST<K,V>::contains(K key){
    return NULL;
}

template <typename K, typename V>void BinTreeST<K,V>::remove(K key){
    //return NULL;
}

template <typename K, typename V>void BinTreeST<K,V>::put(const K key, const V val){
    TreeNode<K,V>* newNode = new TreeNode<K,V>(key, val);
    if(isEmpty()){
        root = newNode;
        return;
    }
    
}

template <typename K, typename V>V BinTreeST<K,V>::get(K key){
    return NULL;
}

template <typename K, typename V>BinTreeST<K,V>::BinTreeST()
        :root(NULL){}

template <typename K, typename V>bool BinTreeST<K,V>::isEmpty(){
    return (NULL == root);
}