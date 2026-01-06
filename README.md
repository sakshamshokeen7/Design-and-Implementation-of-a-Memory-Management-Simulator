# Memory Management Simulator

![Language](https://img.shields.io/badge/language-C++17-blue)
![Build](https://img.shields.io/badge/build-Makefile-green)
![Domain](https://img.shields.io/badge/domain-Operating%20Systems-orange)

A **CLI-based Operating Systems memory management simulator** that models how modern OS kernels manage **physical memory allocation**, **buddy allocation**, **CPU cache hierarchy**, and **virtual memory with paging**.

The simulator emphasizes **systems-level design**, **algorithmic correctness**, and **performance trade-offs** in memory management.

---

## Demo Video
https://github.com/user-attachments/assets/801664f0-acf4-40d4-9fb3-e0c3a020f99a




## 📌 Features Overview

### 1. Physical Memory Allocation
- Simulates a contiguous block of physical memory
- Dynamic allocation and deallocation
- Allocation strategies:
  - First Fit
  - Best Fit
  - Worst Fit
- Block splitting and coalescing
- Real-time statistics:
  - Used / free memory
  - Internal fragmentation
  - External fragmentation
  - Allocation success rate
  - Memory utilization

---

### 2. Buddy Memory Allocator
- Power-of-two memory management
- Allocation rounded to nearest power of two
- Recursive block splitting
- Buddy coalescing using XOR-based address computation
- Free lists maintained per block size
- Visualization via `buddy_dump`

---

### 3. Multi-Level Cache Simulation

- Simulates a two-level CPU cache hierarchy consisting of L1 and L2 caches, integrated with physical memory access.
- Features
- Configurable L1 and L2 cache sizes
- Set-associative cache design
- FIFO replacement policy
- Real-time tracking of:
- Cache hits and misses per level
- Miss propagation from L1 → L2 → main memory
- Total memory access cycles (miss penalty modeling)
- Behavior
- L1 is checked first for every access
- On L1 miss, request is forwarded to L2
- On L2 miss, access is forwarded to main memory
- Blocks are inserted back into upper cache levels following FIFO policy
- This module demonstrates realistic cache behavior and clearly visualizes performance trade-offs in hierarchical memory systems.
---

### 4. Virtual Memory Simulation
- Paging-based virtual memory model
- Virtual → Physical address translation
- Page table management
- Page fault detection and handling
- FIFO page replacement
- Integrated pipeline:


---

##  Simulator Commands

### Memory Allocation
```text
init memory <size>
set <firstfit | bestfit | worstfit>
malloc <size>
free <block_id>
dump memory
stats
```

### Buddy Allocator
```text
buddy_malloc <size>
buddy_free <address> <size>
buddy_dump
```

### Cache
```text
cache_init <l1_size> <l2_size>
cache_access <address>
cache_stats
```
### Virtual Memory
```text
vm_init <pages> <frames> <page_size>
vm_access <virtual_address>
vm_stats
```
### Integrated Access
``` text
access <virtual_address>
---
```


### 🛠 Build Instructions (Windows / MinGW)
Requirements

1) MinGW (g++)
2) mingw32-make

Commands
``` text
1)cd file
2)mingw32-make
3).\memsim.exe
```
---

### 📁 Project Structure
``` text
memory-simulator/
├── src/
│   ├── allocator/
│   ├── buddy/
│   ├── cache/
│   ├── virtual_memory/
│   └── main.cpp
│
├── include/
│   ├── allocator/
│   ├── buddy/
│   ├── cache/
│   └── virtual_memory/
│
├── tests/
│   ├── allocator_test.txt
│   ├── buddy_test.txt
│   ├── cache_test.txt
│   └── vm_test.txt
│
├── docs/
│   └── DESIGN.md
│
├── Makefile
└── README.md
```

---
### 🎯 Learning Outcomes

Understanding memory allocation strategies

Fragmentation analysis

Cache hierarchy behavior

Virtual memory and paging

OS-level abstraction design in user space

---
### 🧠 Design Highlights

Modular separation of allocation strategies

Clear abstraction between memory model and CLI

Efficient coalescing of free blocks

Buddy allocator uses XOR-based buddy computation

Easily extensible for cache and virtual memory modules

---
### ⚠️ Assumptions & Limitations

Simulation runs entirely in user space

No real hardware interaction

Cache and virtual memory extensions are conceptual / optional

Focus is on correctness and visualization, not raw performance
