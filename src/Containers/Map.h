#pragma once
#include <exception>

#include "ARRAY_t.h"
#include "KVPair.h"


template<typename A, typename B> using Predicate = bool(*)(A, B);




template<typename Tx, typename Ty>
static constexpr bool DefaultComparator(Tx x, Ty y) { return x == y; }

template<typename Tx, typename Ty>
static bool StringComparator(Tx x, Ty y) { return x == 0 || y == 0?false: strcmp(x,y) == 0; }


template<typename _TKey, typename _TVal, Predicate<_TKey, _TKey> comparator = DefaultComparator>
class Map
{
public:
    typedef KVPair<_TKey, _TVal> TNode;
    using TKey = typename TNode::TKey;
    using TVal = typename TNode::TVal;
    Map() = default;
   
    
    

    constexpr int Count()const { return _nodes.Count(); }

    int GetKeyIndex(_TKey key)
    {
        int s = this->_nodes.end() - this->_nodes.begin();
        for (int i = 0; i < s; i++)
        {
            TNode m = this->_nodes[i];
            if (comparator(key, m.key))
                return i;

        }
        return -1;
    }

    ARRAY_t<TNode>& GetNodes() { return _nodes; }

    ARRAY_t<_TKey> GetKeys()
    {
        ARRAY_t<_TKey> keys;
        for(auto& n : _nodes)
            keys.Push(n.key);
        
        return keys;
    }

    ARRAY_t<_TVal> GetValues()
    {
        ARRAY_t<_TVal> values;
        for (auto& n : _nodes)
            values.Push(n.value);

        return values;
    }
    

    _TVal& Get(_TKey key)
    {
        int index = GetKeyIndex(key);
        if (index == -1)
            throw std::exception("Unable to locate node.");
        return this->_nodes[index].value;
    }

    bool TryToGet(_TKey key, _TVal* out_v)
    {
        int index = GetKeyIndex(key);
        if (index < 0)
            return false;
        *out_v = this->_nodes[index].value;
        return true;
    }

    void Set(_TKey key, const _TVal& v)
    {
        const int index = GetKeyIndex(key);
        if (index == -1)
            // Node not found
            return;
        this->_nodes[index] = TNode(key, v);
    }

    void SetOrInsert(_TKey key, const _TVal& v)
    {
        const int index = GetKeyIndex(key);
        if (index == -1)
            // Node not found
            return Insert(key, v);
        this->_nodes[index] = TNode(key, v);
    }

    void Insert(_TKey key, const _TVal& v)
    {
        this->_nodes.Push(TNode(key, v));
    }

    template<typename...Tx>
    void Emplace(_TKey key, const Tx&...args)
    {
        this->_nodes.Push(TNode(key, _TVal(args...)));
    }

    template<typename...Tx>
    void SetOrEmplace(_TKey key, const Tx&...args)
    {
        const int index = GetKeyIndex(key);
        if (index == -1)
            // Node not found
            return Emplace(key, args...);
        this->_nodes[index] = TNode(key, _TVal(args...));
    }

    _TVal& operator[](_TKey key)
    {
        return Get(key);
    }

private:
    //Node<_TKey, _TVal> _default_placeholder;
    ARRAY_t<TNode> _nodes;
};

template<typename TVal>
using StringMap = Map<const char*, TVal, StringComparator>;