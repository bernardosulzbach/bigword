#include "data.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

static const size_t limit_size = std::numeric_limits<uint32_t>::max();
static const char separator = ':';

using std::istream;
using std::ostream;

void dump_safe_string(ostream &os, const std::string &string) {
  os << string << '\n';
}

void dump_unsafe_string(ostream &os, const std::string &string) {
  const size_t size = string.size();
  if (size > limit_size) {
    os << limit_size << separator << string.substr(size) << '\n';
  } else {
    os << size << separator << string << '\n';
  }
}

std::string read_safe_string(istream &is) {
  std::string string;
  is >> string;
  return string;
}

std::string read_unsafe_string(istream &is) {
  size_t size;
  is >> size;
  is.ignore();
  std::string string;
  string.resize(size);
  is.read(&string[0], size);
  return string;
}
