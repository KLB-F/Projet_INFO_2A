#pragma once

#include <unordered_map>

/// PARTIE NODE

struct Node {
    int key;
    double value;

    Node* previous;
    Node* next;
};

/// PARTIE LRUCACHE

class LRUCache {
public:
    explicit LRUCache(int capacity);
    ~LRUCache();

    bool contains(int key) const;
    double get(int key);
    void put(int key, double value);

    int size() const;
    int getCapacity() const;

    void printCache() const;

private:
    void removeNode(Node* node);
    void appendToTail(Node* node);
    void moveToMostRecent(Node* node);

    Node* head;
    Node* tail;
    int capacity;
    std::unordered_map<int, Node*> cache;

    int compteur;

    /*
     * Implementation intentionally left free.
     *
     * The cache must combine:
     * - a doubly linked list to maintain LRU -> MRU order;
     * - a std::unordered_map for fast access by key.
     *
     * You are free to choose:
     * - the Node structure;
     * - the internal fields;
     * - the helper functions;
     * - how the unordered_map refers to the linked-list elements.
     */
};
