#pragma once

#include <array>
#include <cstdint>

#include "rules.hpp"

namespace BigWord {
/**
 * An analysis of the most efficient way to compare two letter counts.
 *
 * Analyze the words read to later improve filtering speed.
 */
class Analysis {
 private:
  // How many words have at least one occurrence of this letter.
  uint32_t words = 0;
  std::array<uint32_t, alphabet_size> word_count = {0};
  std::array<size_t, alphabet_size> best_order = {0};

  void find_best_order();

 public:
  void analyze(const std::string word);
  void compile();
  size_t best_index(const size_t comparison) const;

  friend std::ostream &operator<<(std::ostream &os, const Analysis &analysis);
  friend std::istream &operator>>(std::istream &is, Analysis &analysis);
};
}  // namespace BigWord
