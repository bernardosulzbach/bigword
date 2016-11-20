#include "rules.hpp"
#include <string>

bool is_valid_letter(const char letter) {
  return letter >= 'a' && letter <= 'z';
}

bool is_valid_word(const std::string &word) {
  for (char letter : word) {
    if (!is_valid_letter(letter)) {
      return false;
    }
  }
  return true;
}

size_t get_letter_index(const char letter) {
  return static_cast<size_t>(letter - 'a');
}
