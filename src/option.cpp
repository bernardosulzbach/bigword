#include "option.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include "clock.hpp"

class TimeOption : public Option {
 public:
  TimeOption() : Option("--time", "Output execution time.") {}

  void run(const Duration duration, const std::vector<Word>&) {
    std::cout << "Done after";
    std::cout << ' ';
    std::cout << duration.to_nanoseconds() / 1000000.0;
    std::cout << ' ';
    std::cout << "milliseconds" << '.' << '\n';
  }
};

/**
 * Returns a vector of unique pointers to all available options.
 */
std::vector<std::unique_ptr<Option>> get_options(void) {
  std::vector<std::unique_ptr<Option>> options;
  options.push_back(std::unique_ptr<Option>(new TimeOption));
  return options;
}
