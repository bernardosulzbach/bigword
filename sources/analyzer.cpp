#include <algorithm>
#include <cmath>
#include <iostream>

#include "analyzer.hpp"
#include "rules.hpp"

void Analysis::analyze(const std::string word) {
  words++;
  for (const char letter : word) {
    if (is_valid_letter(letter)) {
      word_count[get_letter_index(letter)]++;
    }
  }
}

void Analysis::compile() {
  find_best_order();
}

struct IndexScore {
  size_t index = 0;
  double score = 0;

  bool operator<(const IndexScore &other) const {
    return score < other.score;
  }
};

/**
 * Determines the best comparison order for letter frequencies based on data.
 *
 * This function runs in O(n) with respect to alphabet size.
 */
void Analysis::find_best_order() {
  // Old Reasoning
  // -------------
  // Letters which are present in most words do not help.
  // Letters which are absent in most words do not help.
  // Letters which are present in about half the words are best.
  //
  // Old Formula
  // -----------
  // Score = abs(0.5 - frequency)
  //
  // Results
  // -------
  // Empirically, I was wrong. Common letters improve comparison performance!
  //
  // Current Formula
  // ---------------
  // Score = 1.0 - frequency
  //
  // Avoid divisions by zero.
  if (words == 0) {
    return;
  }
  IndexScore scores[alphabet_size];
  const double total_words = static_cast<double>(words);
  for (size_t i = 0; i < alphabet_size; i++) {
    scores[i].index = i;
    scores[i].score = 1.0 - word_count[i] / total_words;
  }
  std::sort(scores, scores + alphabet_size);
  for (size_t i = 0; i < alphabet_size; i++) {
    best_order[i] = scores[i].index;
  }
}

size_t Analysis::best_index(const size_t comparison) const {
  return best_order[comparison];
}

std::ostream &operator<<(std::ostream &os, const Analysis &analysis) {
  os << analysis.words;
  os << '\n';
  for (size_t i = 0; i < alphabet_size; i++) {
    os << analysis.word_count[i];
    os << '\n';
  }
  for (size_t i = 0; i < alphabet_size; i++) {
    os << analysis.best_order[i];
    if (i + 1 != alphabet_size) {
      os << '\n';
    }
  }
  return os;
}

std::istream &operator>>(std::istream &is, Analysis &analysis) {
  is >> analysis.words;
  for (size_t i = 0; i < alphabet_size; i++) {
    is >> analysis.word_count[i];
  }
  for (size_t i = 0; i < alphabet_size; i++) {
    is >> analysis.best_order[i];
  }
  return is;
}
