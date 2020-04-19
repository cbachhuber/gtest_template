#include <gtest/gtest.h>

#include "my_project.hpp"
#include <string>
#include <chrono>
#include <thread>

void mysleep(unsigned int ms){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

TEST(Timer, test) {
  std::string unit_name{"name"};
  Timer unit{unit_name};
  unit.tic();
  mysleep(2);
  unit.toc();  // Adds time diff to internal vector. Possibly prints current msmt in ms
  testing::internal::CaptureStdout();
  unit.getLastTimeMs();
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output{unit_name + ": 2ms"};
  EXPECT_EQ(expected_output, output);
  // unit.printStats(); // Prints number of msmts, min, mean, median, max (toggleable)
  // unit.time(functionCall(x,y));  // Performs tictoc
}

// TEST(Timers, test) {
//   Timers unit{};
//   unit.addTimer("Bill");  // Adds timer to internal vector
//   unit.addTimer("Bob");
//   unit["Bill"].tic();
//   sleep(300ms);
//   unit["Bill"].toc();  // Adds time diff to internal vector. Possibly prints current msmt in ms
//   unit["Bob"].time(functionCall(x,y));
//   unit.printAllStats(); // Prints number of msmts, min, mean, median, max (toggleable)
// }