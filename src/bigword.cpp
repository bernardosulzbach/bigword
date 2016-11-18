#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

static std::string get_words_filename(void);

static bool is_countable_letter(const char letter);

static bool is_valid_word(const std::string &word);

static bool is_big_enough(const std::string &word, const std::string &input);

static std::string get_words_filename(void) { return "words.txt"; }

static bool is_countable_letter(const char letter) {
  return letter >= 'a' && letter <= 'z';
}

static bool is_valid_word(const std::string &word) {
  for (char letter : word) {
    if (!is_countable_letter(letter)) {
      return false;
    }
  }
  return true;
}

static bool is_big_enough(const std::string &word, const std::string &input) {
  return word.size() <= input.size();
}

class LetterCount {
  static const size_t alphabet_size = 'z' - 'a' + 1;

  size_t letter_count = 0;
  std::vector<uint8_t> counters = std::vector<uint8_t>(alphabet_size, 0);

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
    std::cout << "Usage: " << argv[0] << ' ' << "LETTERS" << '\n';
    return 0;
  }
  const Word input_word = Word(std::string(argv[1]));
  std::string string;
  std::vector<Word> words;
  std::ifstream words_file(get_words_filename());
  while (words_file >> string) {
    if (!is_valid_word(string)) {
      continue;
    }
    if (!is_big_enough(string, input_word.to_string())) {
      continue;
    }
    words.push_back(Word(string));
  }
  std::sort(words.begin(), words.end(), Word::compare_by_size);
  for (auto iter = words.rbegin(); iter != words.rend(); iter++) {
    const auto word = *iter;
    if (Word::is_contained(word, input_word)) {
      std::cout << word << '\n';
      break;
    }
  }
  return 0;
}
