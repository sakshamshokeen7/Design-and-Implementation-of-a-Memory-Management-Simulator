#ifndef VM_H
#define VM_H

#include <vector>
#include <queue>

struct PageTableEntry {
    bool valid;
    int frame;
};

class VirtualMemory {
private:
    int page_size;
    int num_pages;
    int num_frames;

    std::vector<PageTableEntry> page_table;
    std::queue<int> fifo;
    std::vector<bool> frame_used;

    int page_faults;
    int accesses;

public:
    VirtualMemory(int pages, int frames, int pageSize);

    void access(int virtual_address);
    void stats();
};

#endif
