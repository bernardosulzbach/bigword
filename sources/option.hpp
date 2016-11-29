#ifndef OPTION_HPP
#define OPTION_HPP

#include <iomanip>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "clock.hpp"
#include "word.hpp"

struct OptionValue {
  static const OptionValue negative;
  static const OptionValue positive;

  std::string text;
  int64_t integer;

  OptionValue(const std::string &text, const int64_t integer)
      : text(text), integer(integer) {}

  bool operator==(const OptionValue &other) const {
    return text == other.text && integer == other.integer;
  }

  bool is_boolean() const {
    return *this == negative || *this == positive;
  }
  bool to_boolean() const {
    return integer != 0;
  }
};

struct Option {
  std::string name;
  std::string info;
  OptionValue value;

  Option(const std::string &name, const std::string &info,
         const OptionValue value)
      : name(name), info(info), value(value) {}
};

class OptionList {
 private:
  std::map<std::string, Option> map;
  void add_option(Option option);
  OptionValue get_value(const std::string &string) const;

 public:
  OptionList();
  void parse(const std::string &string);
  bool is_timing() const;
  bool is_printing_line_numbers() const;
  std::string get_source_file() const;
  void print_options() const;
};

#endif
