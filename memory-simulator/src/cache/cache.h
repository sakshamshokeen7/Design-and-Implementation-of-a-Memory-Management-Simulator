#ifndef CACHE_H
#define CACHE_H
#include <queue>
#include <unordered_set>
using namespace std;

class Cache{
    private:
    int capacity;
    queue<int> fifo;
    unordered_set<int> lookup;
    int hits;
    int misses;
    public:
    Cache(int cap);
    bool access(int address);
    void insert(int address);
    void stats(const char* name);
};
class CacheSystem{
    private:
    Cache l1;
    Cache l2;
    public:
    CacheSystem(int l1_size,int l2_size);
    void access(int address);
    void stats();
};

#endif
