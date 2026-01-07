#include <iostream>
#include <string>
#include <limits>

#include "../include/buddy/buddy.h"
#include "../include/allocator/allocator.h"
#include "../include/cache/cache.h"
#include "../include/virtual_memory/vm.h"

using namespace std;


void printHeader(const string &title) {
    cout << "\n========================================\n";
    cout << " " << title << "\n";
    cout << "========================================\n";
}

void printInfo(const string &msg) {
    cout << "[INFO] " << msg << endl;
}

void printSuccess(const string &msg) {
    cout << "[SUCCESS] " << msg << endl;
}

void printError(const string &msg) {
    cout << "[ERROR] " << msg << endl;
}


int main() {
    printHeader("Memory Management Simulator");
    printInfo("Simulator started");

    MemoryAllocator *allocator = nullptr;
    BuddyAllocator *buddyAllocator = nullptr;
    CacheSystem *cache = nullptr;
    VirtualMemory *vm = nullptr;

    string command;

    while (true) {
        cout << "\n[memsim] > ";
        getline(cin, command);

        if (command.empty())
            continue;
        if (command == "init") {
            string type;
            int size;
            cin >> type >> size;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (type == "memory") {
                delete allocator;
                delete buddyAllocator;

                allocator = new MemoryAllocator(size);
                buddyAllocator = new BuddyAllocator(size);

                printHeader("Physical Memory Initialization");
                printSuccess("Memory initialized with size " + to_string(size));
            }
        }

        else if (command == "set") {
            string algo;
            cin >> algo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!allocator) {
                printError("Initialize memory first");
                continue;
            }

            if (algo == "firstfit")
                allocator->allocator_type = FIRST_FIT;
            else if (algo == "bestfit")
                allocator->allocator_type = BEST_FIT;
            else if (algo == "worstfit")
                allocator->allocator_type = WORST_FIT;

            printSuccess("Allocation strategy set to " + algo);
        }

        else if (command == "malloc") {
            int size;
            cin >> size;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!allocator) {
                printError("Initialize memory first");
                continue;
            }

            printHeader("Memory Allocation");
            allocator->mallocMem(size);
        }

        else if (command == "free") {
            int id;
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!allocator) {
                printError("Initialize memory first");
                continue;
            }

            printHeader("Memory Deallocation");
            allocator->freeMem(id);
        }

        else if (command == "dump") {
            string what;
            cin >> what;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (what == "memory" && allocator) {
                printHeader("Memory Dump");
                allocator->dump();
            } else {
                printError("Nothing to dump");
            }
        }

        else if (command == "stats") {
            if (!allocator) {
                printError("Initialize memory first");
                continue;
            }

            printHeader("Memory Statistics");
            allocator->stats();
        }

        else if (command == "buddy_malloc") {
            int size;
            cin >> size;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!buddyAllocator) {
                printError("Initialize memory first");
                continue;
            }

            printHeader("Buddy Allocation");
            buddyAllocator->allocate(size);
        }

        else if (command == "buddy_free") {
            int address, size;
            cin >> address >> size;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!buddyAllocator) {
                printError("Initialize memory first");
                continue;
            }

            printHeader("Buddy Deallocation");
            buddyAllocator->freeBlock(address, size);
        }

        else if (command == "buddy_dump") {
            if (buddyAllocator) {
                printHeader("Buddy Free Lists");
                buddyAllocator->dump();
            } else {
                printError("Nothing to dump");
            }
        }

        else if (command == "cache_init") {
            int l1_size, l2_size;
            cin >> l1_size >> l2_size;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            delete cache;
            cache = new CacheSystem(l1_size, l2_size);

            printHeader("Cache Initialization");
            printSuccess("L1 = " + to_string(l1_size) +
                         ", L2 = " + to_string(l2_size));
        }

        else if (command == "cache_access") {
            int address;
            cin >> address;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!cache) {
                printError("Initialize cache first");
                continue;
            }

            printHeader("Cache Access");
            cache->access(address);
        }

        else if (command == "cache_stats") {
            if (cache) {
                printHeader("Cache Statistics");
                cache->stats();
            } else {
                printError("Nothing to show");
            }
        }

        else if (command == "vm_init") {
            int pages, frames, pageSize;
            cin >> pages >> frames >> pageSize;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            delete vm;
            vm = new VirtualMemory(pages, frames, pageSize);

            printHeader("Virtual Memory Initialization");
            printSuccess("Pages=" + to_string(pages) +
                         ", Frames=" + to_string(frames) +
                         ", Page Size=" + to_string(pageSize));
        }

        else if (command == "vm_access") {
            int address;
            cin >> address;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!vm) {
                printError("Initialize virtual memory first");
                continue;
            }

            printHeader("Virtual Memory Access");
            vm->access(address);
        }

        else if (command == "vm_stats") {
            if (vm) {
                printHeader("Virtual Memory Statistics");
                vm->stats();
            } else {
                printError("Nothing to show");
            }
        }

        else if (command == "access") {
            int vaddr;
            cin >> vaddr;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!vm || !cache || !allocator) {
                printError("Initialize memory, cache, and virtual memory first");
                continue;
            }

            bool pageFault;
            int paddr = vm->translate(vaddr, pageFault);

            if (paddr == -1) {
                printError("Invalid virtual address");
                continue;
            }

            printHeader("Integrated Memory Access");
            cout << "Virtual Address : " << vaddr << endl;
            cout << "Physical Address: " << paddr << endl;

            if (pageFault)
                printInfo("Page fault handled");

            cache->access(paddr);
            cout << "physical memory accessed\n";
        }

        else if (command == "exit") {
            printInfo("Exiting simulator");
            break;
        }
        else {
            printError("Unknown command: " + command);
        }
    }

    delete allocator;
    delete buddyAllocator;
    delete cache;
    delete vm;

    return 0;
}
