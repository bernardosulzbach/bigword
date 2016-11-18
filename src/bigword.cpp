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

static void print_usage(const std::string &program_name) {
  std::cout << "Usage: " << program_name;
  std::cout << ' ' << "[OPTIONS]";
  std::cout << ' ' << "LETTERS";
  std::cout << '\n';
}

/**
 * Reads the input letters and make a word from it.
 *
 * Returns the empty word if there were no good candidates.
 */
static Word read_input_letters(int argc, char *argv[]) {
  for (int i = 1; i != argc; i++) {
    const std::string argument(argv[i]);
    if (!argument.empty()) {
      if (argument[0] == '-') {
        continue;
      }
      // First not empty that starts with something other than a dash.
      return Word(argument);
    }
  }
  return Word("");
}

static void print_matches(Word input, std::vector<Word> words) {
  Word match = Word("");
  bool found = false;
  for (auto iter = words.rbegin(); iter != words.rend(); iter++) {
    const auto word = *iter;
    if (found) {
      // Stop if we reached smaller words.
      if (Word::compare_by_size(word, match)) {
        break;
      }
    }
    if (Word::is_contained(word, input)) {
      if (!found) {
        found = true;
        // Update the first match.
        match = word;
      }
      std::cout << word << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  if (argc < 2) {
    // Fail if there are too few arguments.
    print_usage(std::string(argv[0]));
    return 0;
  }
  const Word input_word = read_input_letters(argc, argv);
  if (input_word == Word("")) {
    // Fail if there is no valid input multiset of letters.
    print_usage(std::string(argv[0]));
    return 0;
  }
  std::vector<Word> words = read_words(input_word);
  print_matches(input_word, words);
  return 0;
}
