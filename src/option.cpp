#include "option.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include "clock.hpp"

typedef std::string string;

OptionList::OptionList() {
  add_option(Option("--time", "Output computation times.", false));
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

bool OptionList::is_timing() {
  const auto iter = map.find("--time");
  if (iter == map.end()) {
    return false;
  }
  return iter->second.value;
}

void OptionList::print_options() const {
  for (auto it = map.begin(); it != map.end(); it++) {
    std::cout << std::setw(4) << ' ';
    std::cout << std::setw(16) << std::left << it->second.name;
    std::cout << ' ' << it->second.info << '\n';
  }
}
