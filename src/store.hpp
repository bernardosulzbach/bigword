#ifndef STORE_HPP
#define STORE_HPP

#include <string>
#include <vector>
#include "digest.hpp"
#include "word.hpp"

/**
 * A database of Words.
 *
 * Includes the Digest of the text file used to create the store.
 */
struct WordStore {
  std::string store_name;
  Digest source_digest;
  std::vector<Word> words;
};

/**
 * Loads the WordStore for the specified text file.
 */
WordStore load_word_store(const std::string &filename);

#endif
