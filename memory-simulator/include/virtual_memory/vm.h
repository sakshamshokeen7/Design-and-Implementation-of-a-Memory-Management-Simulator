#ifndef VM_H
#define VM_H

#include <vector>
#include <queue>
using namespace std;

struct PageTableEntry {
    bool valid;
    int frame;
};

class VirtualMemory {
private:
    int page_size;
    int num_pages;
    int num_frames;

    vector<PageTableEntry> page_table;
    queue<int> fifo;
    vector<bool> frame_used;

    int page_faults;
    int accesses;

public:
    VirtualMemory(int pages, int frames, int pageSize);
    int translate(int virtual_address, bool &pageFault);
    void access(int virtual_address);
    void stats();
};

#endif
