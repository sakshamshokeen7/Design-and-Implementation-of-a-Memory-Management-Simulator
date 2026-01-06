#include "../include/virtual_memory/vm.h"
#include <iostream>

using namespace std;

VirtualMemory::VirtualMemory(int pages, int frames, int pageSize)
    : page_size(pageSize),
      num_pages(pages),
      num_frames(frames),
      page_faults(0),
      accesses(0)
{
    page_table.resize(num_pages, {false, -1});
    frame_used.resize(num_frames, false);
}

void VirtualMemory::access(int virtual_address) {
    accesses++;

    int page = virtual_address / page_size;
    int offset = virtual_address % page_size;

    if (page < 0 || page >= num_pages) {
        cout << "Invalid virtual address\n";
        return;
    }

    if (page_table[page].valid) {
        int frame = page_table[page].frame;
        int physical_address = frame * page_size + offset;
        cout << "Page HIT → Physical address: " << physical_address << endl;
        return;
    }

    page_faults++;
    cout << "Page FAULT → ";

    int frame = -1;

    for (int i = 0; i < num_frames; i++) {
        if (!frame_used[i]) {
            frame = i;
            break;
        }
    }

    if (frame == -1) {
        int victim = fifo.front();
        fifo.pop();
        frame = page_table[victim].frame;
        page_table[victim].valid = false;
        cout << "Evicting page " << victim << " | ";
    }

    page_table[page].valid = true;
    page_table[page].frame = frame;
    frame_used[frame] = true;
    fifo.push(page);

    int physical_address = frame * page_size + offset;
    cout << "Loaded page " << page
         << " → Physical address: " << physical_address << endl;
}

void VirtualMemory::stats() {
    cout << "\n--- Virtual Memory Stats ---\n";
    cout << "Total accesses: " << accesses << endl;
    cout << "Page faults: " << page_faults << endl;
    cout << "Page fault rate: "
         << (accesses ? 100.0 * page_faults / accesses : 0.0)
         << " %\n";
}

int VirtualMemory::translate(int virtual_address, bool &pageFault) {
    accesses++;

    int page = virtual_address / page_size;
    int offset = virtual_address % page_size;

    if (page < 0 || page >= num_pages) {
        pageFault = false;
        return -1;
    }

    if (page_table[page].valid) {
        pageFault = false;
        return page_table[page].frame * page_size + offset;
    }

    pageFault = true;
    page_faults++;

    int frame = -1;
    for (int i = 0; i < num_frames; i++) {
        if (!frame_used[i]) {
            frame = i;
            break;
        }
    }

    if (frame == -1) {
        int victim = fifo.front();
        fifo.pop();
        frame = page_table[victim].frame;
        page_table[victim].valid = false;
    }

    page_table[page].valid = true;
    page_table[page].frame = frame;
    frame_used[frame] = true;
    fifo.push(page);

    return frame * page_size + offset;
}
