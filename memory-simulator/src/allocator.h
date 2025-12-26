#ifndef allocator_h
#define allocator_h
#include <vector>
using namespace std;

struct Block {
    int start;
    int size;
    int requested; 
    bool free;
    int id;
};

enum Allocator_type{
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class MemoryAllocator {
    private:
        vector<Block> blocks;
        int total_memory;
        int next_id;
        int total_requests;
        int successful_allocs;
        int findBlock(int size, Allocator_type type);
        void mergeFreeBlocks();
    public:
        MemoryAllocator(int memorysize);
        void setallocator(Allocator_type type);
        void mallocMem(int size); 
        void freeMem(int id);
        void dump();
        void stats();
        Allocator_type allocator_type; 
};

#endif