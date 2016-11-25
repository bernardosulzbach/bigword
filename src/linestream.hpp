#ifndef LINESTREAM_H
#define LINESTREAM_H

#include <fstream>
#include <streambuf>
#include "linenumber.hpp"

class LineStream : public std::streambuf {
 private:
  std::streambuf* source;
  std::istream* owner = nullptr;
  LineNumber line_number = 1;

  char buffer;

 protected:
  int underflow() {
    // Read the next character.
    const int character = source->sbumpc();
    if (character != EOF) {
      buffer = character;
      // Set the read area pointers.
      setg(&buffer, &buffer, &buffer + 1);
      if (buffer == '\n') {
        line_number++;
      }
    }
    return character;
  }

 public:
  LineStream(std::streambuf* source) : source(source) {}

  LineStream(std::istream& stream_owner) {
    // Set the owner buffer to this object.
    owner = &stream_owner;
    // Keep track of the previous buffer so we can restore it in the end.
    source = owner->rdbuf(this);
  }

  ~LineStream() {
    if (owner != nullptr) {
      // Restore the previous buffer.
      owner->rdbuf(source);
    }
  }

  LineNumber get_line_number() const;
};

#endif
