#include "Networking.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void networkingThread(SharedData& data) {
    for (int i = 0; i < 5; ++i) {
        // Simulate receiving a network packet
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string msg = "Packet #" + std::to_string(i);

        // Lock before writing to shared message
        {
            std::lock_guard<std::mutex> lock(data.networkMutex);
            data.networkMessage = msg;
            std::cout << "[Networking] Received: " << msg << std::endl;
        }
    }
}
