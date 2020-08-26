#pragma once

#include <fstream>
#include <streambuf>

#include "linenumber.hpp"

namespace BigWord {
class LineStream : public std::streambuf {
 private:
  std::streambuf *source;
  std::istream *owner = nullptr;
  LineNumber line_number = 1;

  char buffer = '\0';

 protected:
  int underflow() override {
    // Read the next character.
    const int character = source->sbumpc();
    if (character != EOF) {
      if (buffer == '\n') {
        line_number++;
      }
      buffer = static_cast<char>(character);
      // Set the read area pointers.
      setg(&buffer, &buffer, &buffer + 1);
    }
    return character;
  }

 public:
  explicit LineStream(std::streambuf *source) : source(source) {}

  explicit LineStream(std::istream &stream_owner) {
    // Set the owner buffer to this object.
    owner = &stream_owner;
    // Keep track of the previous buffer so we can restore it in the end.
    source = owner->rdbuf(this);
  }

  ~LineStream() override {
    if (owner != nullptr) {
      // Restore the previous buffer.
      owner->rdbuf(source);
    }
  }

  [[nodiscard]] LineNumber get_line_number() const;
};
}  // namespace BigWord