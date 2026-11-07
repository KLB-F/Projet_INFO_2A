#pragma once

#include "LRUCache.hpp"

struct freq_var {
    long long unsigned temps_arr;
    int compte;
};

class LFUCache : public LRUCache{
public:
    explicit LFUCache(int capacite);
    double get(int key) override;
    void put(int key, double value) override;
    ~LFUCache();
    void printCache() const override;

protected:
    std::unordered_map<int, freq_var*> freq_dict;
    long long unsigned temps;

};

