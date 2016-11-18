#include "clock.hpp"
#include <chrono>

TimePoint::TimePoint() { now = std::chrono::high_resolution_clock::now(); }

Duration::Duration(TimePoint begin, TimePoint end) {
  duration = end.now - begin.now;
}

double Duration::to_nanoseconds() const {
  auto us = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
  return us.count();
}
