#include "../include/allocator/allocator.h"
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

MemoryAllocator::MemoryAllocator(int memorysize) {
    total_memory = memorysize;
    next_id = 1;
    total_requests = 0;
    successful_allocs = 0;
    blocks.push_back({0, memorysize, 0, true, -1});
    allocator_type = FIRST_FIT;
}

int MemoryAllocator::findBlock(int size, Allocator_type allocator_type){
    int index=-1;
    if(allocator_type==FIRST_FIT){
        for(int i=0;i<blocks.size();++i){
            if(blocks[i].free && blocks[i].size>=size){
               return i;
            }
        }
    }
    if(allocator_type==BEST_FIT){
        int best=INT_MAX;
        for(int i=0;i<blocks.size();++i){
            if(blocks[i].free && blocks[i].size>=size && blocks[i].size<best){
                best=blocks[i].size;
                index=i;
            }

        }
    }
    if(allocator_type==WORST_FIT){
        int worst=-1;
        for(int i=0;i<blocks.size();++i){
            if(blocks[i].free && blocks[i].size>=size && blocks[i].size>worst){
                worst=blocks[i].size;
                index=i;
            }
        }
    }
    return index;
}

void MemoryAllocator::mallocMem(int size) {
    total_requests++;

    int idx = findBlock(size, allocator_type);
    if (idx == -1) {
        cout << "Allocation failed for size " << size << endl;
        return;
    }
    successful_allocs++;
    int start = blocks[idx].start;
    int oldSize = blocks[idx].size;
    blocks[idx].size = size;
    blocks[idx].requested = size;
    blocks[idx].free = false;
    blocks[idx].id = next_id++;
    if (oldSize > size) {
        Block newBlock;
        newBlock.start = start + size;
        newBlock.size = oldSize - size;
        newBlock.requested = 0;
        newBlock.free = true;
        newBlock.id = -1;
        blocks.insert(blocks.begin() + idx + 1, newBlock);
    }
    cout << "Allocated block id " << blocks[idx].id
         << " at address=0x" << hex << blocks[idx].start
         << dec << " of size " << size << endl;
}


void MemoryAllocator::freeMem(int id){
    for(auto &b:blocks){
        if(!b.free && b.id==id){
            b.free=true;
            b.id=-1;
            b.requested=0;
            mergeFreeBlocks();
            cout<<"Freed block id "<<id<<endl;
            return;
        }
    }
    cout<<"invalid block id "<<id<<endl;
}

void MemoryAllocator::mergeFreeBlocks(){
    for(int i=0;i<blocks.size()-1;++i){
        if(blocks[i].free && blocks[i+1].free){
            blocks[i].size+=blocks[i+1].size;
            blocks.erase(blocks.begin()+i+1);
            --i;
        }
    }
}

void MemoryAllocator::dump(){
    cout<<dec;
    for(auto &b:blocks){
        cout<<"[0X"<<hex<<b.start<<"-0X"<<b.start+b.size-1<<"] ";
        if(b.free){
            cout<<"Free"<<endl;
        }
        else{
            cout<<"USED ( id="<<dec<<b.id<<")\n";
        }
    }
}
void MemoryAllocator::stats(){
    cout<<dec;
    int used=0,freemem=0,internal_frag=0,largest_free=0;
    for(auto &b:blocks){
        if(b.free){
            freemem+=b.size;
            largest_free=max(largest_free,b.size);
        }
        else{
            used+=b.size;
            internal_frag+=b.size-b.requested;
        }
    }
    double external_frag =
    (freemem > 0)
        ? 100.0 * (double)(freemem - largest_free) / freemem
        : 0.0;
    double utilization=100.0*used/total_memory;
    double success_rate=100.0*successful_allocs/total_requests;
    cout<<"\n--- Memory Statistics ---\n";
    cout<<"Total memory: "<<total_memory<<" bytes\n";
    cout<<"Used memory: "<<used<<" bytes\n";
    cout<<"Free memory: "<<freemem<<" bytes\n";
    cout<<"Internal fragmentation: "<<internal_frag<<" bytes\n";
    cout<<"External fragmentation: "<<fixed<<setprecision(2)<<external_frag<<" %\n";
    cout<<"Memory utilization: "<<fixed<<setprecision(2)<<utilization<<" %\n";
    cout<<"Allocation success rate: "<<fixed<<setprecision(2)<<success_rate<<" %\n";
}
void MemoryAllocator::setallocator(Allocator_type type){
    allocator_type=type;
}

