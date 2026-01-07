#include "../include/cache/cache.h"
#include <iostream>
using namespace std;


CacheSet::CacheSet(int cap) : capacity(cap) {}

bool CacheSet::access(int address) {
    return lookup.count(address);
}

void CacheSet::insert(int address) {
    if (lookup.count(address)) return;

    if ((int)fifo.size() == capacity) {
        int old = fifo.front();
        fifo.pop();
        lookup.erase(old);
    }
    fifo.push(address);
    lookup.insert(address);
}


Cache::Cache(int cap, int assoc)
    : capacity(cap), associativity(assoc), hits(0), misses(0) {

    num_sets = capacity / associativity;
    for (int i = 0; i < num_sets; i++) {
        sets.emplace_back(associativity);
    }
}

int Cache::getSetIndex(int address) {
    return address % num_sets;
}

bool Cache::access(int address) {
    int setIndex = getSetIndex(address);
    if (sets[setIndex].access(address)) {
        hits++;
        return true;
    }
    misses++;
    return false;
}

void Cache::insert(int address) {
    sets[getSetIndex(address)].insert(address);
}

void Cache::stats(const char* name) const {
    cout << name << " Cache Stats:\n";
    cout << "Hits   : " << hits << endl;
    cout << "Misses : " << misses << endl;
}


CacheSystem::CacheSystem(int l1_size, int l2_size)
    : CacheSystem(l1_size, l2_size, 2) {}

CacheSystem::CacheSystem(int l1_size, int l2_size, int assoc)
    : l1(l1_size, assoc),
      l2(l2_size, assoc),
      l1_miss_forwarded(0),
      l2_miss_forwarded(0),
      total_cycles(0) {}

void CacheSystem::access(int address) {
    total_cycles += 1; 

    if (l1.access(address)) {
        cout << "L1 hit\n";
        total_cycles += 1;
    }
    else {
        l1_miss_forwarded++;

        if (l2.access(address)) {
            cout << "L1 miss\nL2 hit\n";
            total_cycles += 10;
            l1.insert(address);
        }
        else {
            l2_miss_forwarded++;
            cout << "L2 miss -> memory access from cpu\n";
            total_cycles += 100;
            l2.insert(address);
            l1.insert(address);
        }
    }
}

void CacheSystem::stats()  {
    cout << "\n========== Cache Statistics ==========\n";
    l1.stats("L1");
    l2.stats("L2");

    cout << "\nMiss Penalty Propagation:\n";
    cout << "L1 misses forwarded to L2     : " << l1_miss_forwarded << endl;
    cout << "L2 misses forwarded to memory : " << l2_miss_forwarded << endl;

    cout << "\nTiming Model:\n";
    cout << "Total cycles consumed : " << total_cycles << endl;
}
