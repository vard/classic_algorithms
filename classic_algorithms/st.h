template <typename K, typename V> class SymbolTableInterface {
   public:
    virtual void put(const K key, const V val) = 0;
    virtual V get(K key) = 0;
    virtual void remove(K key) = 0;
    virtual bool contains(K key);
    virtual int size() = 0;
    virtual bool isEmpty() = 0;     
};

template <typename K, typename V> bool SymbolTableInterface<K,V>::contains(K key){
    return get(key);
}