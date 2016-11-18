#ifndef WORD_HPP
#define WORD_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::string get_words_filename(void);

bool is_countable_letter(const char letter);

bool is_valid_word(const std::string &word);

bool is_big_enough(const std::string &word, const std::string &input);

class LetterCount {
 private:
  static const size_t alphabet_size = 'z' - 'a' + 1;

  size_t letter_count = 0;
  uint8_t counters[alphabet_size] = {0};

  size_t get_letter_counter(const char letter) const;

 public:
  LetterCount(const std::string &word);

  bool operator==(const LetterCount &other) const;

  bool operator<(const LetterCount &other) const;

  static bool is_contained(const LetterCount &a, const LetterCount &b) {
    if (a.letter_count > b.letter_count) {
      return false;
    }
    size_t remaining = b.letter_count - a.letter_count;
    for (size_t i = 0; i < alphabet_size; i++) {
      if (a.counters[i] > b.counters[i]) {
        return false;
      }
      // By catching excessive differences we may fail early.
      const size_t difference = b.counters[i] - a.counters[i];
      if (difference > remaining) {
        return false;
      }
      remaining -= difference;
    }
    return true;
  }
};

class Word {
 private:
  std::string word;
  LetterCount count;

 public:
  Word(const std::string &string);

  bool operator==(const Word &other) const;

  bool operator<(const Word &other) const;

  std::string to_string(void) const;

  static bool is_contained(const Word &a, const Word &b) {
    return LetterCount::is_contained(a.count, b.count);
  }

  static bool compare_by_size(const Word &a, const Word &b) {
    return a.word.size() < b.word.size();
  }
};

std::ostream &operator<<(std::ostream &stream, const Word &word);

#endif
