#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <bitset>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static std::string get_words_filename(void);

static std::string get_words_filename(void) { return "words"; }

class LetterCount {
  static const size_t alphabet_size = 'z' - 'a' + 1;

  size_t letter_count = 0;
  std::vector<uint8_t> counters = std::vector<uint8_t>(alphabet_size, 0);

  bool is_countable_letter(const char letter) {
    return letter >= 'a' && letter <= 'z';
  }

  size_t get_letter_counter(const char letter) {
    return static_cast<size_t>(letter - 'a');
  }

 public:
  LetterCount(const std::string &word) {
    for (const char letter : word) {
      if (is_countable_letter(letter)) {
        counters[get_letter_counter(letter)]++;
        letter_count++;
      }
    }
  }

  bool operator<(const LetterCount &other) const {
    return letter_count < other.letter_count;
  }

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
  std::string word;
  LetterCount count;

 public:
  Word(const std::string &string) : count(LetterCount(string)) {
    word = string;
  }

  bool operator<(const Word &other) const { return word < other.word; }

  static bool is_contained(const Word &a, const Word &b) {
    return LetterCount::is_contained(a.count, b.count);
  }

  std::string to_string(void) const { return word; }

  size_t size(void) const { return word.size(); }

  static bool compare_by_size(const Word &a, const Word &b) {
    return a.size() < b.size();
  }
};

std::ostream &operator<<(std::ostream &stream, const Word &word);

std::ostream &operator<<(std::ostream &stream, const Word &word) {
  stream << word.to_string();
  return stream;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  if (argc < 2) {
    std::cout << "Pass the lettes as arguments to the program." << '\n';
    return 0;
  }
  const Word input_word = Word(std::string(argv[1]));
  std::string string;
  std::vector<Word> words;
  std::ifstream words_file(get_words_filename());
  while (words_file >> string) {
    words.push_back(Word(string));
  }
  std::sort(words.begin(), words.end(), Word::compare_by_size);
  auto upper = std::upper_bound(words.begin(), words.end(), input_word);
  while (true) {
    auto word = *upper;
    if (Word::is_contained(word, input_word)) {
      std::cout << word << '\n';
      break;
    }
    if (upper == words.begin()) {
      break;
    }
    upper--;
  }
  return 0;
}
