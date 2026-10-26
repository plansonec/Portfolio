# CPU Process Scheduler Simulator & Custom Template Data Structures (C++17)

**Course:** CS 221 — Computer Science II: Data Structures (University of Alabama in Huntsville)  
**Author:** Emma Planson (`@plansonec`)  
**Tech Stack:** C++17, Object-Oriented Polymorphism, Generic Programming (C++ Templates), Custom Iterators, `std::chrono` High-Resolution Benchmarking, GNU Make

## Executive Overview

This project implements a discrete-event **Operating System CPU Process Scheduler Simulator** (`schedulesim`) backed entirely by custom-built generic C++ template data structures. It evaluates how underlying data structure selection directly impacts scheduling overhead and process fairness across mixed workloads of **CPU-bound** and **I/O-bound** processes.

Three scheduling architectures are implemented and benchmarked head-to-head:
1. **`RoundRobin` (backed by `ArrayList<Process*>`)**: Uses a dynamically resizing contiguous array queue. Demonstrates $O(n)$ front-removal overhead when rotating processes.
2. **`FastRoundRobin` (backed by `LinkedList<Process*>`)**: Uses a singly/doubly-ended pointer queue with `head` and `tail` pointers to achieve $O(1)$ `pushBack` and $O(1)$ `popFront` rotation.
3. **`CompletelyFair` (backed by `BSTMultimap<int, Process*>`)**: Models the Linux Completely Fair Scheduler (CFS) using a binary search tree multimap keyed by accumulated `cpuTime`. Always dispatches the unblocked process with the lowest CPU time via `BSTForwardIterator`.

## Custom Generic Data Structures & Time Complexity

| Data Structure | Source Files | Key Operations & Asymptotic Complexity | Role in Scheduler |
| :--- | :--- | :--- | :--- |
| `List<item_t>` | `List.hpp` | Pure virtual interface defining `pushBack`, `popBack`, `pushFront`, `popFront`, `insert`, `remove`, `getItem`, `setItem`. | Polymorphic base interface for queue-backed schedulers. |
| `ArrayList<item_t>` | `ArrayList.hpp`, `ArrayList.tpp` | `pushBack`: $O(1)$ amortized (2x capacity doubling)<br>`popFront` / `insert(0)`: $O(n)$ element shift<br>`getItem(i)`: $O(1)$ random access | Backing store for baseline `RoundRobin` scheduler and simulation statistics arrays. |
| `LinkedList<item_t>` | `LinkedList.hpp`, `LinkedList.tpp`, `LinkedListNode.hpp/.tpp` | `pushFront` / `popFront`: $O(1)$<br>`pushBack`: $O(1)$ (via `tail` pointer)<br>`insert(i)` / `remove(i)`: $O(n)$ traversal | Backing store for `FastRoundRobin`, eliminating array shift overhead during queue rotation. |
| `BSTMultimap<key_t, val_t>` | `BSTMultimap.hpp`, `BSTMultimap.tpp`, `BSTNode.hpp/.tpp` | `insert`: $O(h)$ average $O(\log n)$<br>`getMin` / `getMax`: $O(h)$<br>`findFirst` / `findLast`: $O(h)$<br>`remove(iterator)`: $O(h)$ tree splice & successor replacement | Backing priority store for `CompletelyFair` scheduler, indexing processes by `cpuTime` and supporting duplicate keys. |
| `BSTForwardIterator<key_t, val_t>` | `BSTForwardIterator.hpp`, `BSTForwardIterator.tpp` | `next()`: $O(h)$ in-order successor traversal (`rightChild` minimum or ancestor climb)<br>`getKey()` / `getValue()`: $O(1)$ | Traverses `BSTMultimap` in ascending order of CPU time to locate the first unblocked process. |

## Empirical Benchmark Results (`schedulesim`)

Using `std::chrono::nanoseconds`, `Simulate.cpp` measures the mean scheduling overhead per `popNext()` call and tracks average CPU time and wait time across simulated CPU cycles (`sliceSize = 10` cycles):

### Workload A: 10 CPU-Bound + 10 I/O-Bound Processes (100,000 Cycles)

| Scheduler Architecture | Backing Data Structure | Mean Overhead / Dispatch (ns) | Avg CPU-Bound CPU Time | Avg I/O-Bound CPU Time | Avg I/O-Bound Wait Time |
| :--- | :--- | ---: | ---: | ---: | ---: |
| **Round Robin** | `ArrayList<Process*>` | 54.09 ns | 6,390.0 cycles | 3,610.0 cycles | 51,719.2 cycles |
| **Fast Round Robin** | `LinkedList<Process*>` | 73.17 ns | 6,388.0 cycles | 3,612.2 cycles | 51,563.0 cycles |
| **Completely Fair (CFS)** | `BSTMultimap<int, Process*>` | 229.83 ns | 5,004.0 cycles | 4,996.5 cycles | **32,279.9 cycles** |

### Workload B: 100 CPU-Bound + 100 I/O-Bound Processes (100,000 Cycles)

| Scheduler Architecture | Backing Data Structure | Mean Overhead / Dispatch (ns) | Avg CPU-Bound CPU Time | Avg I/O-Bound CPU Time | Avg I/O-Bound Wait Time |
| :--- | :--- | ---: | ---: | ---: | ---: |
| **Round Robin** | `ArrayList<Process*>` | 74.85 ns | 593.9 cycles | 406.1 cycles | 94,569.2 cycles |
| **Fast Round Robin** | `LinkedList<Process*>` | **67.34 ns** | 593.1 cycles | 406.9 cycles | 94,527.1 cycles |
| **Completely Fair (CFS)** | `BSTMultimap<int, Process*>` | 408.63 ns | **500.0 cycles** | **500.0 cycles** | **93,293.5 cycles** |

**Key Engineering Takeaways:**
1. **Fairness & I/O Responsiveness**: `CompletelyFair` equalizes CPU allocation between CPU-bound and I/O-bound processes (`5,004` vs. `4,996.5` cycles in Workload A; `500.0` vs. `500.0` in Workload B) and cuts I/O-bound wait time by **37.6%** in Workload A because waking I/O processes have lower accumulated `cpuTime` and are immediately prioritized at the left of the BST.
2. **Asymptotic Queue Scaling**: For small queues ($N = 20$), `ArrayList` benefits from CPU cache locality (`54.09 ns`), but as process count scales ($N = 200$), `FastRoundRobin` (`LinkedList`) overtakes `ArrayList` (`67.34 ns` vs. `74.85 ns`) because $O(1)$ pointer unlinking avoids shifting hundreds of pointers on every `popFront()`.

## How to Build, Test, and Benchmark

```bash
# Compile simulator and all 5 unit test suites
make all

# Run all 5 automated unit test suites (ArrayList, LinkedList, BSTMultimap, RoundRobin, CompletelyFair)
make test

# Run live scheduler benchmarks
./schedulesim 10 10 100000
./schedulesim 100 100 100000
```
