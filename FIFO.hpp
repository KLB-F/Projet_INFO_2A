#pragma once

#include "LRUCache.hpp"

class FIFO : public LRUCache {
public:
    explicit FIFO(int capacite);
    double get(int key) override;
    void put(int key, double value) override;
    void printCache() const override;
};