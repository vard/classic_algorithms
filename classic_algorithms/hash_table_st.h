#include "boost/functional/hash.hpp"
#include <vector>

using namespace std;

template <typename K, typename V> struct HTNode{
    K key;
    V value;
    HTNode* next;
    HTNode();
    HTNode(const K& nodeKey, const V& nodeVal);
};

template <typename K, typename V> HTNode<K, V>::HTNode()
:next(NULL){
}

template <typename K, typename V> HTNode<K, V>::HTNode(const K& nodeKey, const V& nodeVal)
:key(nodeKey),
 value(nodeVal),
 next(NULL){
}

template <typename K, typename V> class HashTableST : public SymbolTableInterface<K, V>{
private:
    static const int M = 1024;
    HTNode<K, V>* remove(HTNode<K, V>* node, const K& key);
    HTNode<K, V>** hashTable;
public:
    HashTableST();
    virtual ~HashTableST();
    virtual V get(K key);
    virtual void put(const K key, const V val);
    virtual void remove(K key);
    virtual bool contains(K key);
    virtual int size();
    virtual bool isEmpty();    
};

template <typename K, typename V> HashTableST<K, V>::HashTableST()
    :hashTable(new HTNode<K, V>*[M]())
{

}

template <typename K, typename V>bool HashTableST<K, V>::isEmpty(){
    return false;
}

template <typename K, typename V>int HashTableST<K, V>::size(){
    return 0;
}

template <typename K, typename V>bool HashTableST<K, V>::contains(K key){
    return NULL != this->get(key);
}

template <typename K, typename V>HTNode<K, V>* HashTableST<K, V>::remove(HTNode<K, V>* node, const K& key){
    if(NULL == node)
        return NULL;

    if(node->key == key){
        HTNode<K, V> copyNode(*node);
        delete node;
        return copyNode.next;
    }

    remove(node->next, key);
}

template <typename K, typename V>void HashTableST<K, V>::remove(K key){
    boost::hash<K> keyHash;
    std::size_t hashCode = keyHash(key);
    unsigned int tableIndex = hashCode % M;
   HTNode<K, V>** nodePtr = &hashTable[tableIndex];
   *nodePtr = remove(*nodePtr, key);
}

template <typename K, typename V>void HashTableST<K, V>::put(const K key, const V val){    
        boost::hash<K> keyHash;
        std::size_t hashCode = keyHash(key);
        unsigned int tableIndex = hashCode % M;
        HTNode<K, V>** nodePtr = &hashTable[tableIndex];
        while(NULL != *nodePtr){
            if(key == (*nodePtr)->key){
                (*nodePtr)->value = val;
                return;
            }
            nodePtr = &((*nodePtr)->next);
        }      
        *nodePtr = new HTNode<K, V>(key ,val);        
}

template <typename K, typename V>V HashTableST<K, V>::get(K key){
    boost::hash<K> keyHash;
    std::size_t hashCode = keyHash(key);
    unsigned int tableIndex = hashCode % M;
    HTNode<K, V>* nodePtr = hashTable[tableIndex];
    while(NULL != nodePtr){
        if(nodePtr->key == key)
            return nodePtr->value;
        nodePtr = nodePtr->next;
    }

    return NULL;
}

template <typename K, typename V>HashTableST<K, V>::~HashTableST(){

}
