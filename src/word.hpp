#ifndef WORD_HPP
#define WORD_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "analyzer.hpp"
#include "rules.hpp"

std::string get_words_filename();

class LetterCount {
 private:
  size_t letter_count = 0;
  uint8_t counters[alphabet_size] = {0};

  size_t get_letter_counter(const char letter) const;

 public:
  LetterCount(const std::string &word);

  bool operator==(const LetterCount &other) const;

  bool operator<(const LetterCount &other) const;

  static bool is_contained(const LetterCount &a, const LetterCount &b,
                           Analysis *analysis) {
    if (a.letter_count > b.letter_count) {
      return false;
    }
    size_t remaining = b.letter_count - a.letter_count;
    for (size_t i = 0; i < alphabet_size; i++) {
      const size_t x = analysis == nullptr ? i : analysis->best_index(i);
      if (a.counters[x] > b.counters[x]) {
        return false;
      }
      // By catching excessive differences we may fail early.
      const size_t difference = b.counters[x] - a.counters[x];
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
  Word();
  Word(const std::string &string);

  bool operator==(const Word &other) const;

  bool operator<(const Word &other) const;

  std::string to_string() const;

  static bool is_contained(const Word &a, const Word &b, Analysis *analysis) {
    return LetterCount::is_contained(a.count, b.count, analysis);
  }

  static bool is_shorter(const Word &a, const Word &b) {
    return a.word.size() < b.word.size();
  }
};

std::ostream &operator<<(std::ostream &os, const Word &word);

std::istream &operator>>(std::istream &is, Word &word);

#endif
