# Memory Management Simulator

![Language](https://img.shields.io/badge/language-C++17-blue)
![Build](https://img.shields.io/badge/build-Makefile-green)
![Domain](https://img.shields.io/badge/domain-Operating%20Systems-orange)

A **CLI-based Operating Systems memory management simulator** that models how modern OS kernels manage **physical memory allocation**, **buddy allocation**, **CPU cache hierarchy**, and **virtual memory with paging**.

The simulator emphasizes **systems-level design**, **algorithmic correctness**, and **performance trade-offs** in memory management.

---

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
- Simulates CPU cache hierarchy:
  - L1 Cache
  - L2 Cache
- FIFO replacement policy
- Tracks:
  - Cache hits and misses per level
  - Miss propagation to lower levels
- Integrated with physical memory accesses

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

### Buddy Allocator
buddy_malloc <size>
buddy_free <address> <size>
buddy_dump

### Cache
cache_init <l1_size> <l2_size>
cache_access <address>
cache_stats

### Virtual Memory
vm_init <pages> <frames> <page_size>
vm_access <virtual_address>
vm_stats

### Integrated Access
access <virtual_address>
---

🛠 Build Instructions (Windows / MinGW)
Requirements

1) MinGW (g++)
2) mingw32-make

Commands

1)cd file
2)mingw32-make
3).\memsim.exe

---

### 📁 Project Structure
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

---
###🎯 Learning Outcomes

Understanding memory allocation strategies

Fragmentation analysis

Cache hierarchy behavior

Virtual memory and paging

OS-level abstraction design in user space

---
###🧠 Design Highlights

Modular separation of allocation strategies

Clear abstraction between memory model and CLI

Efficient coalescing of free blocks

Buddy allocator uses XOR-based buddy computation

Easily extensible for cache and virtual memory modules

---
###⚠️ Assumptions & Limitations

Simulation runs entirely in user space

No real hardware interaction

Cache and virtual memory extensions are conceptual / optional

Focus is on correctness and visualization, not raw performance