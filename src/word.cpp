#include "word.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

static void report_unsupported_letter(const char letter) {
  std::cerr << "Found unsupported letter:";
  std::cerr << ' ';
  std::cerr << '"';
  std::cerr << letter;
  std::cerr << '"';
  std::cerr << '\n';
}

std::string get_words_filename(void) { return "words.txt"; }

bool is_countable_letter(const char letter) {
  return letter >= 'a' && letter <= 'z';
}

bool is_valid_word(const std::string &word) {
  for (char letter : word) {
    if (!is_countable_letter(letter)) {
      return false;
    }
  }
  return true;
}

bool is_big_enough(const std::string &word, const std::string &input) {
  return word.size() <= input.size();
}

size_t LetterCount::get_letter_counter(const char letter) const {
  return static_cast<size_t>(letter - 'a');
}

LetterCount::LetterCount(const std::string &word) {
  for (const char letter : word) {
    if (is_countable_letter(letter)) {
      counters[get_letter_counter(letter)]++;
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

std::string Word::to_string(void) const { return word; }

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
