#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>
#include <string>

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

void write_time_with_unit(const uint64_t number, std::string name);

void write_time(const double nanoseconds);

#endif
