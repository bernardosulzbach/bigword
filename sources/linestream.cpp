#include "linestream.hpp"

namespace BigWord {
LineNumber LineStream::get_line_number() const {
  return line_number;
}
}  // namespace BigWord