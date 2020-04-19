#include "timer.h"
#include <chrono>
#include <iostream>

void Timer::tic() {
    current_start = std::chrono::high_resolution_clock::now();
}

void Timer::toc(const bool) {
    splits.push_back(std::chrono::high_resolution_clock::now() - current_start);
    // tic();
}

void Timer::getLastTimeMs() {
    std::cout << m_name << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(splits.back()).count() << "ms";
}


//ostream operator?