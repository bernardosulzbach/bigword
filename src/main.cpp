#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "option.hpp"
#include "word.hpp"

// Prevent wrapping.
typedef std::vector<std::unique_ptr<Option>> OptionVector;

static void print_options(void) {
  OptionVector options = get_options();
  std::cout << "The available options are:" << '\n';
  for (auto it = options.begin(); it != options.end(); it++) {
    std::cout << std::setw(4) << ' ';
    std::cout << std::setw(16) << std::left << (**it).name;
    std::cout << ' ' << (**it).info << '\n';
  }
}

static void print_usage(const std::string &program_name) {
  std::cout << "Usage: " << program_name;
  std::cout << ' ' << "[OPTIONS]";
  std::cout << ' ' << "LETTERS";
  std::cout << '\n';
  print_options();
}

/**
 * Reads the command line options.
 */
static OptionVector read_options(int argc, char *argv[]) {
  OptionVector options = get_options();
  OptionVector selected;
  for (int i = 1; i != argc; i++) {
    const std::string argument(argv[i]);
    if (!argument.empty()) {
      if (argument[0] != '-') {
        break;
      }
      for (auto it = options.begin(); it != options.end(); it++) {
        if ((**it).name == argument) {
          selected.push_back(std::move(*it));
          options.erase(it);
          break;
        }
      }
    }
  }
  return selected;
}

/**
 * Reads the input letters and make a word from it.
 *
 * Returns the empty word if there were no good candidates.
 */
static Word read_input(int argc, char *argv[]) {
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

static std::vector<Word> find_matches(Word input, std::vector<Word> words) {
  std::vector<Word> word_vector;
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
      word_vector.push_back(word);
    }
  }
  return word_vector;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  const TimePoint start;
  if (argc < 2) {
    // Fail if there are too few arguments.
    print_usage(std::string(argv[0]));
    return 0;
  }
  const OptionVector options = read_options(argc, argv);
  const Word input = read_input(argc, argv);
  if (input == Word("")) {
    // Fail if there is no valid input multiset of letters.
    print_usage(std::string(argv[0]));
    return 0;
  }
  std::vector<Word> words = read_words(input);
  std::vector<Word> matches = find_matches(input, words);
  const TimePoint end;
  const Duration duration(start, end);
  for (Word match : matches) {
    std::cout << match << '\n';
  }
  for (auto it = options.begin(); it != options.end(); it++) {
    (**it).run(duration, matches);
  }
  return 0;
}
