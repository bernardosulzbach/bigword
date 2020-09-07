#pragma once

#include <string>

namespace BigWord {
constexpr size_t AlphabetSize = 'z' - 'a' + 1;

/**
 * Returns whether or not a letter should be counted.
 */
inline bool is_valid_letter(const char letter) {
  return letter >= 'a' && letter <= 'z';
}

inline size_t get_letter_index(const char letter) {
  return static_cast<size_t>(letter - 'a');
}

bool is_valid_word(const std::string &word);
}  // namespace BigWord