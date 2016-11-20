#ifndef RULES_H
#define RULES_H

#include <string>

const size_t alphabet_size = 'z' - 'a' + 1;

/**
 * Returns whether or not a letter should be counted.
 */
bool is_valid_letter(const char letter);

bool is_valid_word(const std::string &word);

size_t get_letter_index(const char letter);

#endif
