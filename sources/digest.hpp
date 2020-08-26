#pragma once

#include <openssl/evp.h>
#include <fstream>

namespace BigWord {
class Digest {
 public:
  static const size_t maximum_size = EVP_MAX_MD_SIZE;

 private:
  unsigned int length = 0;
  unsigned char digest[maximum_size] = {0};

 public:
  Digest() = default;

  /**
   * Constructs a Digest by digesting the contents of the specified file.
   */
  explicit Digest(const std::string &filename);

  bool operator==(const Digest &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Digest &digest);

  friend std::istream &operator>>(std::istream &is, Digest &digest);
};
}  // namespace BigWord