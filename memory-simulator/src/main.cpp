#include <iostream>
#include <string>
#include "buddy/buddy.h"
#include "allocator/allocator.h"
#include "cache/cache.h"
using namespace std;

int main(){
    cout<<"Memory Simulator Started\n";
    MemoryAllocator* allocator=nullptr;
    BuddyAllocator* buddyAllocator=nullptr;
    CacheSystem* cache=nullptr;
    string command;
    while(true){
        cout<<" > ";
        getline(cin,command);
        if(command=="init"){
            string type;
            int size;
            cin>>type>>size;
            cin.ignore();
            if(type=="memory"){
                delete allocator;
                allocator=new MemoryAllocator(size);
                buddyAllocator=new BuddyAllocator(size);
                cout<<"Initialized memory allocator of size "<<size<<endl;
            }            
        }
        else if(command=="set"){
            string algo;
            cin>>algo;
            cin.ignore();
            if(!allocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            if(algo=="firstfit"){
                allocator->allocator_type=FIRST_FIT;
            }
            else if(algo=="bestfit"){
                allocator->allocator_type=BEST_FIT;
            }
            else if(algo=="worstfit"){
                allocator->allocator_type=WORST_FIT;
            }
            cout<<"Allocator set to "<<algo<<endl;
        }
        else if(command=="malloc"){
            int size;
            cin>>size;
            cin.ignore();
            if(!allocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            allocator->mallocMem(size);
        }
        else if(command=="free"){
            int id;
            cin>>id;
            cin.ignore();
            if(!allocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            allocator->freeMem(id);
        }
        else if(command=="dump"){
            string what;
            cin>>what;
            cin.ignore();
            if(what=="memory" && allocator){
                allocator->dump();
            }
            else{
                cout<<"nothing to dump\n";
            }
        }
        else if(command=="stats"){
            if(!allocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            allocator->stats();
        }
        else if(command=="buddy_malloc"){
            int size;
            cin>>size;
            cin.ignore();
            if(!buddyAllocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            buddyAllocator->allocate(size);
        }
        else if(command=="buddy_free"){
            int address,size;
            cin>>address>>size;
            if(!buddyAllocator){
                cout<<"Initialize memory first using 'init memory <size>' command\n";
                continue;
            }
            buddyAllocator->freeBlock(address,size);
        }
        else if(command=="buddy_dump"){
            if(buddyAllocator){
                buddyAllocator->dump();
            }
            else{
                cout<<"nothing to dump\n";
            }
        }
        else if(command=="cache_init"){
            int l1_size,l2_size;
            cin>>l1_size>>l2_size;
            cin.ignore();
            delete cache;
            cache=new CacheSystem(l1_size,l2_size);
            cout << "Cache initialized (L1=" << l1_size << ", L2=" << l2_size << ")\n";
        }
        else if(command=="cache_access"){
            int address;
            cin>>address;
            cin.ignore();
            if(!cache){
                cout<<"initialize cache first"<<endl;
                continue;
            }
            cache->access(address);
        }
        else if(command=="cache_stats"){
            if(cache){
                cache->stats();
            }
            else{
                cout<<"nothing to show\n";
            }
        }
        else if(command=="exit"){
            cout<<"Exiting Memory Simulator\n";
            break;
        }
        else{
            cout<<"Unknown command: "<<command<<endl;
        }
    }
    delete allocator;
    delete buddyAllocator;
    return 0;
}

