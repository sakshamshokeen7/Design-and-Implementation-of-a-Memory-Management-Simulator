#include "buddy.h"
#include <iostream>
#include <cmath>
using namespace std;

BuddyAllocator::BuddyAllocator(int size){
    max_size=size;
    freeLists[size].push_back(0);
}
int BuddyAllocator::next_power_of_two(int size){
    if(size <= 0) return 1;
    return pow(2, ceil(log2(size)));
}
int BuddyAllocator::buddy_of(int address,int size){
    return address ^ size;
}
int BuddyAllocator::allocate(int size){
    int req=next_power_of_two(size);
    for(int s=req;s<max_size;s*=2){
        if(!freeLists[s].empty()){
            int address=freeLists[s].back();
            freeLists[s].pop_back();
            while(s>req){
                s/=2;
                freeLists[s].push_back(address+s);
            }
            cout<<"Allocated "<<req<<" bytes at address "<<address<<endl;
            return address;
        }    
    }
    cout<<"Allocation failed for "<<size<<" bytes"<<endl;
    return -1;
}
void BuddyAllocator::freeBlock(int address,int size){
    int s=next_power_of_two(size);
    while(s<max_size){
        int buddy=buddy_of(address,s);
        auto &list=freeLists[s];
        auto it=find(list.begin(),list.end(),buddy);
        if(it!=list.end()){
            list.erase(it);
            address=min(address,buddy);
            s*=2;
        }else{
            break;
        }
    }
    freeLists[s].push_back(address);
    cout<<"block freed at address "<<address<<" of size "<<s<<endl;
}
void BuddyAllocator::dump(){
    cout<<"\n --Free Buddy Lists --\n"<<endl;
    for(auto &p:freeLists){
        cout<<"SIZE"<<p.first<<": ";
        for(int address:p.second){
            cout<<address<<" ";
        }
        cout<<endl;
    }
}
