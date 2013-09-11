#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <memory>

namespace trie{

#define DEFAULT_TRIE_ALPHABET_SIZE 256

    template<typename ItemType> struct TrieNode{
    public:
        static const uint32_t alphabetSize = DEFAULT_TRIE_ALPHABET_SIZE;
        ItemType value;
        std::vector<std::shared_ptr<TrieNode> > next;
        TrieNode();
        //TrieNode& operator=(const TrieNode& rhs);
    };

   

  /*  template<typename ItemType>
    TrieNode& trie::TrieNode<ItemType>::operator=( const TrieNode& rhs ){
        this.alphabetSize = ths.alphabetSize;
        this.value = rhs.value;
        this.next
    }*/

    template<typename ItemType>
    trie::TrieNode<ItemType>::TrieNode(){
        
        next.resize(alphabetSize);
    }

    template<typename ItemType> class Trie{
    private:
        std::shared_ptr<TrieNode<ItemType>> root; 
        std::shared_ptr<TrieNode<ItemType>> get(std::shared_ptr<TrieNode<ItemType>> node, const std::string& key, int32_t d);
        std::shared_ptr<TrieNode<ItemType>> put(std::shared_ptr<TrieNode<ItemType>> node, const std::string& key, const ItemType& value, int32_t d);
    public:
        void put(const std::string& key, const ItemType& value);
        bool get(const std::string& key, ItemType& item);
        bool contains(const std::string& key) const;
        Trie();
    };


    template<typename ItemType>
    std::shared_ptr<TrieNode<ItemType>> trie::Trie<ItemType>::get( std::shared_ptr<TrieNode<ItemType>> node, const std::string& key, int32_t d ){
        if(nullptr == node)
            return std::shared_ptr<TrieNode<ItemType>>(nullptr);

        if(d==key.size()-1)
            return node;

        char c = key.at(d);
        return get(node->next[c], key, d+1);
    }

    template<typename ItemType>
    bool trie::Trie<ItemType>::get( const std::string& key, ItemType& item){
        std::shared_ptr<TrieNode<ItemType>> node = get(root, key, 0);
        if(node){
            item = node->value;
            return true;
        } else {
            return false;
        }
    }

    template<typename ItemType>
    std::shared_ptr<TrieNode<ItemType>> Trie<ItemType>::put(std::shared_ptr<TrieNode<ItemType>> node, const std::string& key, const ItemType& value, int32_t d){
        if(!node){           
            node = std::shared_ptr<TrieNode<ItemType>>(new TrieNode<ItemType>());
        }

        if(d == key.size()-1){
            node->value = value;
            return node;
        }

        char c = key.at(d);
        node->next[c] = put(node->next[c], key, value, d+1);
        return node;
    }

    template<typename ItemType>
    void trie::Trie<ItemType>::put( const std::string& key, const ItemType& value ){
        root = put(root, key, value, 0);
    }


    template<typename ItemType>
    trie::Trie<ItemType>::Trie()
    {

    }

}