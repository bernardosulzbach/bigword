#ifndef DATA_HPP
#define DATA_HPP

#include <string>

void dump_safe_string(std::ostream &os, const std::string &string);
void dump_unsafe_string(std::ostream &os, const std::string &string);

std::string read_safe_string(std::istream &is);
std::string read_unsafe_string(std::istream &is);

#endif
