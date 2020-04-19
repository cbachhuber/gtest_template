
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <vector>

class Timer {
 public:
  Timer(const std::string& name) : m_name{name} {
    // tic();
  }
  void tic();
  void toc(const bool print_me = false);
  void getLastTimeMs();

 private:
  const std::string m_name;
  std::vector<std::chrono::nanoseconds> m_splits;
  std::chrono::high_resolution_clock::time_point m_current_start;
};
#endif  // TIMER_H

// class Timers