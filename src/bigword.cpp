#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "word.hpp"

static std::vector<Word> read_words(const Word &word) {
  std::vector<Word> words;
  std::string string;
  std::ifstream words_file(get_words_filename());
  while (words_file >> string) {
    if (!is_valid_word(string)) {
      continue;
    }
    if (!is_big_enough(string, word.to_string())) {
      continue;
    }
    words.push_back(Word(string));
  }
  std::sort(words.begin(), words.end(), Word::compare_by_size);
  return words;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << ' ' << "LETTERS" << '\n';
    return 0;
  }
  const Word input_word = Word(std::string(argv[1]));
  std::vector<Word> words = read_words(input_word);
  for (auto iter = words.rbegin(); iter != words.rend(); iter++) {
    const auto word = *iter;
    if (Word::is_contained(word, input_word)) {
      std::cout << word << '\n';
      break;
    }
  }
  return 0;
}
