#include "timer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>

static int castToMilliseconds(const std::chrono::nanoseconds& nanoseconds) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(nanoseconds).count();
}

void Timer::tic() {
  m_current_start = std::chrono::high_resolution_clock::now();
}

void Timer::toc(const bool) {
  m_splits.push_back(std::chrono::high_resolution_clock::now() - m_current_start);
  tic();
}

void Timer::printLastSplitMs() {
  std::cout << m_name << ": " << castToMilliseconds(m_splits.back()) << "ms";
}

void Timer::printStatsMs() {
  // Prints number of msmts, min, mean, median, max (toggleable)
  std::vector<unsigned int> splits_ms{};
  for (const auto& split : m_splits) {
    splits_ms.push_back(castToMilliseconds(split));
  }

  std::sort(splits_ms.begin(), splits_ms.end());

  const auto minimum = splits_ms.front();
  const auto median = splits_ms[splits_ms.size() / 2];
  const auto mean = std::accumulate(splits_ms.begin(), splits_ms.end(), 0.0f) / splits_ms.size();
  const auto maximum = splits_ms.back();
  std::cout << m_name << " stats:\n";
  std::cout << "  Minimum: " << minimum << "ms\n";
  std::cout << "  Median:  " << median << "ms\n";
  std::cout << "  Mean:    " << mean << "ms\n";
  std::cout << "  Maximum: " << maximum << "ms\n";
}

// ostream operator?