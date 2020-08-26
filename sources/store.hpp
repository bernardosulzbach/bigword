#pragma once

#include <string>
#include <vector>

#include "analyzer.hpp"
#include "digest.hpp"
#include "word.hpp"

namespace BigWord {
/**
 * A database of Words.
 *
 * Includes the Digest of the text file used to create the store.
 */
struct WordStore {
  std::string store_name;
  Digest source_digest;
  Analysis analysis;
  std::vector<Word> words;

  void include(const std::string &string);
  void compile();
};

/**
 * Loads the WordStore for the specified text file.
 */
WordStore load_word_store(const std::string &filename);
}  // namespace BigWord