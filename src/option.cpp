#include "option.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include "clock.hpp"

static const double thousand = 1000.0;
static const double million = thousand * thousand;
static const double billion = thousand * thousand * thousand;

static void write_time_with_unit(const uint64_t number, std::string name) {
  if (number == 1) {
    std::cout << number << ' ' << name;
  } else {
    std::cout << number << ' ' << name << 's';
  }
}

static void write_time(const double nanoseconds) {
  if (nanoseconds >= billion) {
    const double seconds = nanoseconds / billion;
    write_time_with_unit(std::floor(seconds), "second");
  } else if (nanoseconds >= million) {
    const double milliseconds = nanoseconds / million;
    write_time_with_unit(std::floor(milliseconds), "millisecond");
  } else if (nanoseconds >= thousand) {
    const double microseconds = nanoseconds / thousand;
    write_time_with_unit(std::floor(microseconds), "microsecond");
  } else {
    write_time_with_unit(std::floor(nanoseconds), "nanosecond");
  }
}

class TimeOption : public Option {
 public:
  TimeOption() : Option("--time", "Output execution time.") {}

  void run(const Duration duration, const std::vector<Word>&) {
    std::cout << "Done after";
    std::cout << ' ';
    write_time(duration.to_nanoseconds());
    std::cout << '.';
    std::cout << '\n';
  }
};

/**
 * Returns a vector of unique pointers to all available options.
 */
std::vector<std::unique_ptr<Option>> get_options() {
  std::vector<std::unique_ptr<Option>> options;
  options.push_back(std::unique_ptr<Option>(new TimeOption));
  return options;
}
