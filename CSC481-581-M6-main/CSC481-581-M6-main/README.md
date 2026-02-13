# CSC481-581 Module 6: Multithreading

## Overview
This module introduces **multithreading** in C++ with a focus on:
- Lock-free multithreading
- Networking with threads
- Implementing a **Job System** with worker threads
- Using `std::atomic` and `std::mutex` for concurrency

### Learning Objectives
- **LO 6.1**: Design a multithreaded networked game engine
- **LO 6.2**: Implement a multithreaded network server
- **LO 6.3**: Implement multithreading techniques in a game engine

---

## Features
1. **Atomic Counter Demo**
   - Multiple threads increment a shared atomic counter.
   - Verifies correctness by comparing expected vs actual values.

2. **Job System**
   - Implements a simple lock-free job system.
   - Workers fetch and execute jobs concurrently.

3. **Networking Thread**
   - Runs independently of the main loop.
   - Simulates receiving network packets and updates shared state safely.

---

## Project Structure
```

.
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── SharedData.h
│   ├── JobSystem.h
│   ├── JobSystem.cpp
│   ├── Networking.h
│   └── Networking.cpp
└── README.md
```
---

## ⚙️ Build & Run
### Prerequisites
- C++17 or newer
- CMake ≥ 3.16

### Build
```bash
git clone https://github.com/AlexanderCard/CSC481-581-M6.git
cd CSC481-581-M6
mkdir build && cd build
cmake ..
make
```

### Run
```
./multithreading_demo
```
### Sample Output with Race Condition
```
--- Part 1: Simple Counter with Race Condition ---
Expected counter: 3000000 | Actual: 1244949
--- Part 2: Job System with Worker Threads ---
Expected from jobs: 25 | Actual: 25
[Networking] Received: Packet #0
...
[Networking] Received: Packet #4
[Main] Last network message: Packet #4
```

### Sample Output
```
--- Lock-Free Multithreading with Networking Thread ---

--- Part 1: Simple Atomic Counter ---
Expected counter: 3000000 | Actual: 3000000

--- Part 2: Job System with Worker Threads ---
Expected from jobs: 25 | Actual: 25
[Networking] Received: Packet #0
...
[Networking] Received: Packet #4
[Main] Last network message: Packet #4
```

### References
- [C++ Reference: std::thread](https://en.cppreference.com/w/cpp/thread/thread)
- [C++ Reference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic)
- [C++ Reference: std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
