#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include "option.hpp"
#include "store.hpp"
#include "word.hpp"

// Prevent wrapping.
typedef std::vector<std::unique_ptr<Option>> OptionVector;

static void print_options() {
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

static std::vector<Word> find_matches(Word input) {
  WordStore store = load_word_store(get_words_filename());
  Word first_match = Word("");
  bool found_match = false;
  std::vector<Word> matches;
  const std::vector<Word> &words = store.words;
  Analysis *analysis = &store.analysis;
  auto iter =
      std::upper_bound(words.begin(), words.end(), input, Word::is_shorter);
  while (true) {
    if (iter == words.begin()) {
      // Stop if it is not possible to step back.
      break;
    }
    iter--;
    const auto word = *iter;
    if (found_match) {
      // Stop if we reached smaller words.
      if (Word::is_shorter(word, first_match)) {
        break;
      }
    }
    if (Word::is_contained(word, input, analysis)) {
      if (!found_match) {
        found_match = true;
        first_match = word;
      }
      matches.push_back(word);
    }
  }
  std::reverse(matches.begin(), matches.end());
  return matches;
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
  const std::vector<Word> matches = find_matches(input);
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
