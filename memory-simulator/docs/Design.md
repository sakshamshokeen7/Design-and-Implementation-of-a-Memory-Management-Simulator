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
