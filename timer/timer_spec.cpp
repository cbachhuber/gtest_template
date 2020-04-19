#include <gtest/gtest.h>

#include <chrono>
#include <string>
#include <thread>
#include "timer.h"

void mysleep(const unsigned int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

TEST(Timer, ConstructorCallsTic) {
  std::string unit_name{"name"};
  std::string expected_output{unit_name + ": 1ms"};

  Timer unit{unit_name};
  mysleep(1);
  unit.toc();

  testing::internal::CaptureStdout();
  unit.printLastSplitMs();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(expected_output, output);
}

class TimerFixture : public ::testing::Test {
 protected:
  std::string m_unit_name{"name"};
  Timer m_unit{m_unit_name};

  void addSplit(const unsigned int milliseconds) {
    m_unit.tic();
    mysleep(milliseconds);
    m_unit.toc();
  }

  std::string getStdoutOfSplit() {
    testing::internal::CaptureStdout();
    m_unit.printLastSplitMs();
    return testing::internal::GetCapturedStdout();
  }

  std::string getStdoutOfStats() {
    testing::internal::CaptureStdout();
    m_unit.printStatsMs();
    return testing::internal::GetCapturedStdout();
  }
};

TEST_F(TimerFixture, TocCallsTic) {
  std::string expected_output{m_unit_name + ": 2ms"};

  mysleep(1);
  m_unit.toc();
  mysleep(2);
  m_unit.toc();

  std::string output = getStdoutOfSplit();

  EXPECT_EQ(expected_output, output);
}

TEST_F(TimerFixture, OneMillisecond) {
  addSplit(1);
  std::string expected_output{m_unit_name + ": 1ms"};

  std::string output = getStdoutOfSplit();

  EXPECT_EQ(expected_output, output);
}

TEST_F(TimerFixture, TwoMilliseconds) {
  addSplit(2);
  std::string expected_output{m_unit_name + ": 2ms"};

  std::string output = getStdoutOfSplit();

  EXPECT_EQ(expected_output, output);
}

TEST_F(TimerFixture, PrintStats) {
  addSplit(1);
  addSplit(1);
  addSplit(5);
  addSplit(1);
  std::string expected_output{m_unit_name + " stats:\n" + "  Minimum: 1ms\n" + "  Median:  1ms\n" + "  Mean:    2ms\n" +
                              "  Maximum: 5ms\n"};

  std::string output = getStdoutOfStats();
  EXPECT_EQ(expected_output, output);
}

// TEST_F(TimerFixture, PrintStats) {
// m_unit.time(functionCall(x,y));  // tictoc wrapper
// }
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