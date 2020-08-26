#include "rules.hpp"
#include <string>

namespace BigWord {
bool is_valid_word(const std::string &word) {
  if (word.empty()) {
    return false;
  }
  for (char letter : word) {
    if (!is_valid_letter(letter)) {
      return false;
    }
  }
  return true;
}
}  // namespace BigWord