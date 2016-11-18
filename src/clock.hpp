#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class TimePoint {
 public:
  std::chrono::high_resolution_clock::time_point now;
  TimePoint();
};

class Duration {
  std::chrono::high_resolution_clock::duration duration;

 public:
  Duration(TimePoint begin, TimePoint end);
  double to_nanoseconds() const;
};

#endif
