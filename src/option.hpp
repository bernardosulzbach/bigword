#ifndef OPTION_HPP
#define OPTION_HPP

#include <memory>
#include <string>
#include <vector>
#include "clock.hpp"
#include "word.hpp"

class Option {
 public:
  std::string name;
  std::string info;

  Option(std::string name, std::string info) : name(name), info(info) {}

  bool operator<(const Option &other) const { return name < other.name; }

  virtual void run(const Duration duration, const std::vector<Word> &words) = 0;
};

/**
 * Returns a vector of unique pointers to all available options.
 */
std::vector<std::unique_ptr<Option>> get_options();

#endif
