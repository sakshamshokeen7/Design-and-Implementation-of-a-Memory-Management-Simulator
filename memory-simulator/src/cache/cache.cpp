#include "cache.h"
#include <iostream>
using namespace std;

Cache::Cache(int cap):capacity(cap),hits(0),misses(0){}

bool Cache::access(int address){
    if(lookup.count(address)){
        hits++;
        return true;
    }
    misses++;
    return false;
}
void Cache::insert(int address){
    if(lookup.count(address)){
        return;
    }
    if(fifo.size()==capacity){
        int old=fifo.front();
        fifo.pop();
        lookup.erase(old);        
    }
    fifo.push(address);
    lookup.insert(address);
}

void Cache::stats(const char* name){
    cout<<name<<" Cache Stats: \n";
    cout<<"Hits: "<<hits<<endl;
    cout<<"Misses: "<<misses<<endl;    
}

CacheSystem::CacheSystem(int l1_size,int l2_size):l1(l1_size),l2(l2_size){}

void CacheSystem::access(int address){
    if(l1.access(address)){
        cout<<"L1 hit"<<endl;
    }
    else if(l2.access(address)){
        cout<<"L1 miss "<<endl;
        cout<<"L2 hit"<<endl;
        l1.insert(address);
    }
    else{
        cout<<"L2 miss-> memory access from cpu"<<endl;
        l2.insert(address);
        l1.insert(address);
    }
}
void CacheSystem::stats(){
    l1.stats("L1");
    l2.stats("L2");
}