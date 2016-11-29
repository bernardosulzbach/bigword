#include "option.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include "clock.hpp"

static const std::string option_name_time = "--time";
static const std::string option_name_line_number = "--line-number";

OptionList::OptionList() {
  add_option(Option(option_name_time, "Output computation times.", false));
  add_option(Option(option_name_line_number, "Output line numbers.", false));
}

void OptionList::add_option(Option option) {
  map.insert({option.name, option});
}

void OptionList::parse(const std::string &string) {
  for (auto it = map.begin(); it != map.end(); it++) {
    if (it->first == string) {
      it->second.value = true;
    }
  }
}

bool OptionList::get_value(const std::string &string) const {
  const auto iter = map.find(string);
  if (iter == map.end()) {
    return false;
  }
  return iter->second.value;
}

bool OptionList::is_timing() const {
  return get_value(option_name_time);
}

bool OptionList::is_printing_line_numbers() const {
  return get_value(option_name_line_number);
}

void OptionList::print_options() const {
  // These will be sorted by option name because maps are sorted.
  for (auto it = map.begin(); it != map.end(); it++) {
    std::cout << std::setw(4) << ' ';
    std::cout << std::setw(16) << std::left << it->second.name;
    std::cout << ' ' << it->second.info << '\n';
  }
}
