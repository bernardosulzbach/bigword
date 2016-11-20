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
  std::string string;
  while (is >> string) {
    store.words.push_back(Word(string));
  }
  return is;
}

static std::string derive_store_name(const std::string &filename) {
  return filename + ".store";
}

static void dump_word_store(const WordStore &store) {
  std::ofstream ofs(store.store_name);
  ofs << store;
}

// Helper static function: we can't take the address of a constructor.
static Digest digest_file(const std::string &filename) {
  return Digest(filename);
}

static WordStore make_word_store(const std::string &filename) {
  auto future_digest = std::async(std::launch::async, digest_file, filename);
  WordStore store;
  store.store_name = derive_store_name(filename);
  std::string string;
  std::ifstream ifs(filename);
  while (ifs >> string) {
    if (!is_valid_word(string)) {
      continue;
    }
    store.words.push_back(Word(string));
    store.analysis.analyze(string);
  }
  store.source_digest = future_digest.get();
  store.compile();
  return store;
}

/**
 * Loads the WordStore for the specified text file.
 */
WordStore load_word_store(const std::string &filename) {
  const std::string store_filename = derive_store_name(filename);
  std::ifstream ifs;
  ifs.open(store_filename);
  if (ifs.is_open()) {
    auto future_digest = std::async(std::launch::async, digest_file, filename);
    WordStore store;
    ifs >> store;
    return store;
    if (store.source_digest == future_digest.get()) {
      return store;
    }
  }
  WordStore store = make_word_store(filename);
  dump_word_store(store);
  return store;
}
