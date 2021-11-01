#pragma once
template<typename K, typename V>
class KVPair
{
public:
    typedef K TKey;
	typedef V TVal;
    
    K key{};
    V value{};
    KVPair() {  }
    KVPair(const K& k, const V& v) : key(k), value(v) {}
};