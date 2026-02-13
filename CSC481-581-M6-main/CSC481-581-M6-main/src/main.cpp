#include <iostream>
#include <thread>
#include <vector>
#include "SharedData.hpp"
#include "JobSystem.hpp"
#include "Networking.hpp"

int main() {
    std::cout << "--- Lock-Free Multithreading with Networking Thread ---\n";

    SharedData sharedData;

    // Start networking in its own thread
    std::thread netThread(networkingThread, std::ref(sharedData));

    // --- Part 1: Simple Atomic Counter Demo ---
    std::cout << "\n--- Part 1: Simple Atomic Counter ---\n";
    const int numIncrements = 1000000;
    auto incrementTask = [&sharedData, numIncrements]() {
        for (int i = 0; i < numIncrements; ++i) {
            sharedData.counter++;
        }
    };

    std::vector<std::thread> threads;
    const int numThreads = 3;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementTask);
    }
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Expected counter: " << numThreads * numIncrements
              << " | Actual: " << sharedData.counter << "\n";

    // --- Part 2: Job System ---
    std::cout << "\n--- Part 2: Job System with Worker Threads ---\n";
    JobQueue jobQueue;
    for (int i = 0; i < 50; ++i) {
        jobQueue.push_back([i, &sharedData]() {
            if (i % 2 == 0) {
                sharedData.counter++;
            }
        });
    }

    sharedData.counter = 0;
    sharedData.nextJobIndex = 0;
    threads.clear();

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, std::ref(sharedData), std::ref(jobQueue));
    }
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Expected from jobs: " << jobQueue.size() / 2
              << " | Actual: " << sharedData.counter << "\n";

    // --- Wait for networking thread to finish ---
    netThread.join();

    // Read last message safely
    {
        std::lock_guard<std::mutex> lock(sharedData.networkMutex);
        std::cout << "[Main] Last network message: " << sharedData.networkMessage << "\n";
    }

    return 0;
}
