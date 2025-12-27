#ifndef buddy_h
#define buddy_h

#include <map>
#include <vector>
using namespace std;

class BuddyAllocator {
    private:
    int max_size;
    map<int,vector<int>> freeLists;
    int next_power_of_two(int size);
    int buddy_of(int address,int size);
    public:
    BuddyAllocator(int size);
    int allocate(int size);
    void freeBlock(int adderess, int size);
    void dump();
};

#endif
    