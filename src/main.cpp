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

typedef std::vector<Word> WordVector;

static void print_usage(const std::string &program_name, OptionList options) {
  std::cout << "Usage: " << program_name;
  std::cout << ' ' << "[OPTIONS]";
  std::cout << ' ' << "LETTERS";
  std::cout << '\n';
  options.print_options();
}

/**
 * Reads the command line options.
 */
static OptionList read_options(int argc, char *argv[]) {
  OptionList options;
  for (int i = 1; i != argc; i++) {
    options.parse(std::string(argv[i]));
  }
  return options;
}

/**
 * Reads the input letters and make a word from it.
 *
 * Returns the empty word if there were no good candidates.
 */
static WordVector read_input(int argc, char *argv[]) {
  WordVector words;
  for (int i = 1; i != argc; i++) {
    const std::string argument(argv[i]);
    if (is_valid_word(argument)) {
      words.push_back(Word(argument));
    }
  }
  return words;
}

static WordVector find_matches(WordStore &store, Word input) {
  Word first_match = Word("");
  bool found_match = false;
  WordVector matches;
  const WordVector &words = store.words;
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

static void write_escape() {
  std::cout << "--";
  std::cout << ' ';
}

static void write_duration(const std::string &action, Duration duration) {
  write_escape();
  std::cout << "Finished";
  std::cout << ' ';
  std::cout << action;
  std::cout << ' ';
  std::cout << "after";
  std::cout << ' ';
  write_time(duration.to_nanoseconds());
  std::cout << '.';
  std::cout << '\n';
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  const TimePoint loading_start;
  OptionList options = read_options(argc, argv);
  if (argc < 2) {
    // Fail if there are too few arguments.
    print_usage(std::string(argv[0]), options);
    return 0;
  }
  const WordVector words = read_input(argc, argv);
  if (words.empty()) {
    // Fail if there is no valid input multiset of letters.
    print_usage(std::string(argv[0]), options);
    return 0;
  }
  WordStore store = load_word_store(get_words_filename());
  if (options.is_timing()) {
    write_duration("loading", Duration(loading_start, TimePoint()));
  }
  for (size_t query = 0; query != words.size(); query++) {
    const TimePoint query_start;
    const WordVector matches = find_matches(store, words[query]);
    write_escape();
    std::cout << "Query" << ' ' << query + 1 << ' ';
    if (matches.empty()) {
      std::cout << "did not match any words";
    } else {
      std::cout << "matched" << ' ' << matches.size() << ' ';
      std::cout << (matches.size() == 1 ? "word" : "words");
    }
    if (options.is_timing()) {
      std::cout << ' ';
      std::cout << "after";
      std::cout << ' ';
      write_time(Duration(query_start, TimePoint()).to_nanoseconds());
    }
    std::cout << '.' << '\n';
    for (Word match : matches) {
      std::cout << match << '\n';
    }
  }
  return 0;
}
