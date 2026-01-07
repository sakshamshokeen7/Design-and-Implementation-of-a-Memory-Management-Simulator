#ifndef CACHE_H
#define CACHE_H

#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

class CacheSet {
public:
    int capacity;
    queue<int> fifo;
    unordered_set<int> lookup;

    CacheSet(int cap);
    bool access(int address);
    void insert(int address);
};

class Cache {
private:
    int capacity;
    int associativity;
    int num_sets;
    int hits, misses;
    vector<CacheSet> sets;

    int getSetIndex(int address);

public:
    Cache(int cap, int assoc);
    bool access(int address);
    void insert(int address);
    void stats(const char* name) const;

    int getHits() const { return hits; }
    int getMisses() const { return misses; }
};

class CacheSystem {
private:
    Cache l1;
    Cache l2;

    int l1_miss_forwarded;
    int l2_miss_forwarded;
    int total_cycles;

public:
    CacheSystem(int l1_size, int l2_size);
    CacheSystem(int l1_size, int l2_size, int assoc);

    void access(int address);
    void stats() ;
};

#endif
