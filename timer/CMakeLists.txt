ADD_LIBRARY(timer timer.cpp)

ADD_EXECUTABLE (timer_spec timer_spec.cpp)
TARGET_LINK_LIBRARIES (
    timer_spec 
    PRIVATE timer 
    PRIVATE gtest_main)

ADD_GTEST(timer_spec)