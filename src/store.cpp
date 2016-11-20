#include "store.hpp"
#include <openssl/evp.h>
#include <fstream>
#include <future>
#include <string>
#include <thread>
#include "rules.hpp"

void WordStore::compile() {
  std::sort(words.begin(), words.end(), Word::is_shorter);
  analysis.compile();
}

static std::ostream &operator<<(std::ostream &os, const WordStore &store) {
  os << store.store_name << '\n';
  os << store.source_digest << '\n';
  os << store.analysis << '\n';
  os << store.words.size() << '\n';
  for (Word word : store.words) {
    os << word << '\n';
  }
  return os;
}

static std::istream &operator>>(std::istream &is, WordStore &store) {
  size_t word_count = 0;
  is >> store.store_name;
  is >> store.source_digest;
  is >> store.analysis;
  is >> word_count;
  store.words.reserve(word_count);
  Word word;
  while (is >> word) {
    store.words.push_back(word);
  }
  return is;
}

static std::string derive_store_name(const std::string &filename) {
  return filename + ".store";
}

static WordStore recover_word_store(const std::string &store_name) {
  WordStore store;
  std::ifstream ifs(store_name);
  ifs >> store;
  return store;
}

static void dump_word_store(const WordStore &store) {
  std::ofstream ofs(store.store_name);
  ofs << store;
}

static WordStore make_word_store(const std::string &filename) {
  WordStore store;
  store.store_name = derive_store_name(filename);
  store.source_digest = Digest(filename);
  std::string string;
  std::ifstream ifs(filename);
  while (ifs >> string) {
    if (!is_valid_word(string)) {
      continue;
    }
    store.words.push_back(Word(string));
    store.analysis.analyze(string);
  }
  store.compile();
  return store;
}

// Helper static function: we can't take the address of a constructor.
static Digest digest_file(const std::string &filename) {
  return Digest(filename);
}

/**
 * Loads the WordStore for the specified text file.
 */
WordStore load_word_store(const std::string &filename) {
  auto future = std::async(digest_file, filename);
  const std::string store_filename = derive_store_name(filename);
  WordStore store = recover_word_store(store_filename);
  const Digest digest = future.get();
  if (store.source_digest == digest) {
    return store;
  } else {
    store = make_word_store(filename);
    dump_word_store(store);
    return store;
  }
}
