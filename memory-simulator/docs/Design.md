# 📘 DESIGN DOCUMENT  
## Memory Management Simulator

---

## 1. Introduction

The **Memory Management Simulator** is a command-line–based educational system that models the internal workings of modern operating system memory management. It simulates memory behavior across multiple layers, including **physical memory allocation**, **buddy allocation**, **CPU cache hierarchy**, and **virtual memory with paging**.

The simulator is designed to bridge the gap between **theoretical OS concepts** and **practical system behavior** by providing step-by-step visualization and statistics of memory operations.

---

## 2. Design Objectives

The primary objectives of the simulator are:

- Faithfully model OS memory management algorithms
- Provide visibility into internal memory states
- Allow experimentation with allocation strategies
- Maintain modular and extensible architecture
- Emphasize correctness over performance
- Clearly separate policy from mechanism

---

## 3. High-Level System Architecture

```text
+--------------------------------------------------+
|                  User / CLI                      |
+---------------------------+----------------------+
                            |
                            v
+--------------------------------------------------+
|               Command Dispatcher                 |
+---------------------------+----------------------+
                            |
        +-------------------+-------------------+
        |                   |                   |
        v                   v                   v
+---------------+   +---------------+   +----------------+
| Allocator     |   | Buddy System  |   | Virtual Memory |
+---------------+   +---------------+   +----------------+
                                              |
                                              v
                                       +-------------+
                                       | Cache System|
                                       +-------------+
                                              |
                                              v
                                       +-------------+
                                       | Main Memory |
                                       +-------------+
Each subsystem operates independently but can be integrated through a unified access pipeline.
```
## 4.Physical Memory Allocation System

### Memory Model
Physical memory is simulated as a contiguous block of memory divided into variable-sized segments.
```text
+------------------------------------------------------+
| Free | Alloc | Free | Alloc | Alloc | Free |  ...   |
+------------------------------------------------------+
```
Each memory block contains:

1. Block ID
2. Start address
3. Block size
4. Allocation status

### Allocation Strategies
First Fit
```text
Scan memory from start → allocate first block large enough
```
Best Fit
```text
Scan all free blocks → allocate smallest suitable block
```
Worst Fit
```text
Scan all free blocks → allocate largest available block
```

### Block Splitting
```text
Before Allocation:
+---------------------- Free (100) ----------------------+

Request: 40

After Allocation:
+-------- Alloc (40) --------+---- Free (60) ----+
```
### Block Coalescing
```text
Before Free:
+---- Free (20) ----+---- Free (30) ----+

After Coalescing:
+----------- Free (50) -----------+
```

### Fragmentation Metrics
1. Internal Fragmentation
Allocated size > requested size

2. External Fragmentation
Free memory exists but not contiguously

## Buddy Memory Allocation System

### Buddy System Overview
The buddy allocator manages memory in power-of-two blocks.
```text
Memory Size = 1024

1024
 ├── 512
 │    ├── 256
 │    │    ├── 128
 │    │    └── 128
 │    └── 256
 └── 512
```
### Allocation Process

1. Round request to nearest power of two
2. Search corresponding free list
3. Recursively split larger blocks if required
4. Allocate final block

### Buddy Address Computation
```text
buddy_address = block_address XOR block_size
```
This enables constant-time buddy lookup.
### Buddy Coalescing
```text
Free Block @ 128 (size 64)
Buddy Block @ 192 (size 64)

→ Merge into 128 (size 128)
```

### Free List Structure
```text
Size 64  → [128, 256]
Size 128 → [512]
Size 256 → [0]
```

## Virtual Memory System

### Virtual Address Structure
```text
Virtual Address
+-------------------+------------------+
| Virtual Page No   | Offset           |
+-------------------+------------------+
```
### Page Table Structure
Each virtual page maps to a page table entry.
```text
Page Table Entry
+-----------+-----------+-------------+
| Present   | Frame No  | Metadata    |
+-----------+-----------+-------------+
```
### Address Translation Flow
```text
Virtual Address
      |
      v
+-------------------+
| Page Number       |
| Offset            |
+-------------------+
      |
      v
+-------------------+
| Page Table Lookup |
+-------------------+
      |
      v
+-------------------+
| Frame Number      |
+-------------------+
      |
      v
Physical Address
```
### Page Fault Handling
```text
Page Fault
    |
    v
Select Victim Page (FIFO)
    |
    v
Evict Page
    |
    v
Load New Page
    |
    v
Update Page Table
```
## Multi-Level Cache Simulation
- The simulator implements a two-level CPU cache hierarchy (L1 and L2) between the CPU and main memory. Both caches are set-associative and use a FIFO (First-In-First-Out) replacement policy.
### Cache Hierarchy
```text
CPU
 |
 v
+---- L1 Cache ----+
 |        MISS
 v
+---- L2 Cache ----+
 |        MISS
 v
Main Memory
```        
- All accesses start at L1
- Misses propagate L1 → L2 → Memory
- Data fetched from lower levels is inserted back into upper caches

### Organization & Policy
- Set-associative mapping
- Configurable cache sizes and associativity
- FIFO eviction per set (oldest line removed on overflow)

### Access Flow
```text
Check L1
 ├─ Hit → Return
 └─ Miss → Check L2
        ├─ Hit → Update L1
        └─ Miss → Fetch from Memory → Update L2 & L1
```
### Miss Propagation & Timing
- Tracks:
L1 misses forwarded to L2
L2 misses forwarded to main memory
- Fixed timing model:
L1 hit: 1 cycle
L2 hit: 10 cycles
Memory access: 100 cycles
Total cycles reported in cache statistics

### Statistic Tracked
- Hits and misses per cache level
- Miss penalty propagation
- Total memory access cycles

### Cache Line Structure
```text
Cache Line
+--------+--------+-----------+
| Tag    | Data   | Metadata  |
+--------+--------+-----------+
```
### Replacement Policy
1. FIFO (First-In-First-Out)
2. Oldest cache line evicted on overflow

### Cache Access Flow
```text
Memory Access
   |
   v
Check L1
   |
   |-- Hit → Return
   |
   v
Check L2
   |
   |-- Hit → Update L1
   |
   v
Fetch from Main Memory
```
## Integrated Memory Access Pipeline
```text
Virtual Address
      |
      v
Page Table Lookup
      |
      v
L1 Cache → L2 Cache
      |
      v
Physical Memory
```
This pipeline enables observation of:

1. Page faults
2. Cache hit/miss behavior
3. Physical memory access patterns

## Error Handling
1. Invalid commands rejected at CLI level
2. Allocation beyond memory size prevented
3. Safe deallocation checks
4. Descriptive runtime error messages

## Extensibility
The design supports future enhancements such as:

1. LRU / LFU cache replacement
2. TLB simulation
3. Demand paging
4. Segmentation
5. Multi-core cache coherence (conceptual)

## Assumptions & Limitations
1. Entirely user-space simulation
2. No concurrency or timing simulation
3. Hardware behavior is abstracted
4. Focus on learning, not benchmarking

## Conclusion
The Memory Management Simulator provides a layered, modular, and deeply educational representation of operating system memory management. Through detailed abstractions and visual flows, it enables learners to understand how memory is allocated, cached, translated, and reclaimed in real operating systems.



