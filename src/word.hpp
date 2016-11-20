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

 public:
  LetterCount(const std::string &word);

  bool operator==(const LetterCount &other) const;

  bool operator<(const LetterCount &other) const;

  bool is_contained(const LetterCount &o, const Analysis *an) const;
};

class Word {
 private:
  std::string word;
  LetterCount count;

 public:
  Word(const std::string &string);

  bool operator==(const Word &other) const;

  bool operator<(const Word &other) const;

  std::string to_string() const;

  static bool is_shorter(const Word &a, const Word &b);

  static bool is_shorter_and_smaller(const Word &a, const Word &b);

  static bool is_contained(const Word &a, const Word &b, const Analysis *an);
};

std::ostream &operator<<(std::ostream &os, const Word &word);

std::istream &operator>>(std::istream &is, Word &word);

#endif
