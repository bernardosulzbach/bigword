#include "word.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include "rules.hpp"

static void report_unsupported_letter(const char letter) {
  std::cerr << "Found unsupported letter:";
  std::cerr << ' ';
  std::cerr << '"';
  std::cerr << letter;
  std::cerr << '"';
  std::cerr << '\n';
}

std::string get_words_filename() { return "words.txt"; }

LetterCount::LetterCount(const std::string &word) {
  for (const char letter : word) {
    if (is_valid_letter(letter)) {
      counters[get_letter_index(letter)]++;
      letter_count++;
    } else {
      report_unsupported_letter(letter);
    }
  }
}

bool LetterCount::operator==(const LetterCount &other) const {
  return letter_count == other.letter_count && counters == other.counters;
}

bool LetterCount::operator<(const LetterCount &other) const {
  return letter_count < other.letter_count;
}

Word::Word() : Word("") {}

Word::Word(const std::string &string) : count(LetterCount(string)) {
  word = string;
}

bool Word::operator==(const Word &other) const {
  return word == other.word && count == other.count;
}

bool Word::operator<(const Word &other) const { return word < other.word; }

std::string Word::to_string() const { return word; }

std::ostream &operator<<(std::ostream &os, const Word &word) {
  os << word.to_string();
  return os;
}

std::istream &operator>>(std::istream &is, Word &word) {
  std::string string;
  is >> string;
  word = Word(string);
  return is;
}
