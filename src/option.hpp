#ifndef OPTION_HPP
#define OPTION_HPP

#include <iomanip>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "clock.hpp"
#include "word.hpp"

struct Option {
  std::string name;
  std::string info;
  bool value;

  Option(const std::string &name, const std::string &info, const bool value) {
    this->name = name;
    this->info = info;
    this->value = value;
  }
};

class OptionList {
 private:
  std::map<std::string, Option> map;
  void add_option(Option option);

 public:
  OptionList();

  void parse(const std::string &string);

  bool is_timing();

  void print_options() const;
};

#endif
