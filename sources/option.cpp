#include "option.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include "clock.hpp"
#include "configuration.hpp"

const OptionValue OptionValue::negative = OptionValue("Negative", 0);
const OptionValue OptionValue::positive = OptionValue("Positive", 1);

static const std::string option_name_time = "--time";
static const std::string option_info_time = "Output computation times.";

static const std::string option_name_source = "--source";
static const std::string option_info_source = "Set the source file.";

static const std::string option_name_line_number = "--line-number";
static const std::string option_info_line_number = "Output line numbers.";

std::string OptionInfo::get_name() const {
  return name;
}

std::string OptionInfo::get_info() const {
  return info;
}

OptionList::OptionList() {
  OptionInfo time_info(option_name_time, option_info_time);
  add_option(Option(time_info, OptionValue::negative));
  OptionInfo source_info(option_name_source, option_info_source);
  add_option(Option(source_info, OptionValue(default_source, 0)));
  OptionInfo line_number_info(option_name_line_number, option_info_line_number);
  add_option(Option(line_number_info, OptionValue::negative));
}

void OptionList::add_option(Option option) {
  map.insert({option.info.get_name(), option});
}

void OptionList::parse(const std::string &string) {
  for (auto it = map.begin(); it != map.end(); it++) {
    // Setting boolean options.
    if (it->first == string && it->second.value.is_boolean()) {
      it->second.value = OptionValue::positive;
    }
  }
}

OptionValue OptionList::get_value(const std::string &string) const {
  const auto iter = map.find(string);
  if (iter == map.end()) {
    return OptionValue::negative;
  }
  return iter->second.value;
}

bool OptionList::is_timing() const {
  return get_value(option_name_time).to_boolean();
}

bool OptionList::is_printing_line_numbers() const {
  return get_value(option_name_line_number).to_boolean();
}

std::string OptionList::get_source_file() const {
  return get_value(option_name_source).text;
}

void OptionList::print_options() const {
  // These will be sorted by option name because maps are sorted.
  for (auto it = map.begin(); it != map.end(); it++) {
    std::cout << std::setw(4) << ' ';
    std::cout << std::setw(16) << std::left;
    std::cout << it->second.info.get_name();
    std::cout << ' ';
    std::cout << it->second.info.get_info();
    std::cout << '\n';
  }
}
