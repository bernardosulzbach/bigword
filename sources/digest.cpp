#include "digest.hpp"

#include <algorithm>
#include <limits>

#include <openssl/evp.h>

namespace BigWord {
static const size_t buffer_size = 8192;

Digest::Digest(const std::string &filename) {
  unsigned char buffer[buffer_size];
  bool digesting = true;
  EVP_MD_CTX *md_context = EVP_MD_CTX_create();
  std::ifstream input(filename);
  OpenSSL_add_all_digests();
  EVP_DigestInit_ex(md_context, EVP_sha256(), NULL);
  while (digesting) {
    input.read((char *)buffer, buffer_size);
    const size_t read_bytes = input.gcount();
    EVP_DigestUpdate(md_context, buffer, read_bytes);
    digesting = read_bytes == buffer_size;
  }
  EVP_DigestFinal_ex(md_context, digest, &length);
  EVP_MD_CTX_destroy(md_context);
}

bool Digest::operator==(const Digest &other) const noexcept {
  if (length != other.length) {
    return false;
  }
  return std::equal(std::begin(digest), std::end(digest),
                    std::begin(other.digest));
}

static void write_base_16(std::ostream &os, const int x) {
  if (x >= 10) {
    os << static_cast<char>('a' + (x - 10));
  } else {
    os << static_cast<char>('0' + x);
  }
}

static int read_base_16(std::istream &is) {
  char c = 0;
  is >> c;
  if (c >= 'a') {
    return 10 + (c - 'a');
  }
  return c - '0';
}

std::ostream &operator<<(std::ostream &os, const Digest &digest) {
  os << digest.length << '\n';
  for (size_t i = 0; i < digest.length; i++) {
    // Give a proper representation of the hash.
    const auto double_byte = static_cast<unsigned char>(digest.digest[i]);
    write_base_16(os, double_byte / 16);
    write_base_16(os, double_byte % 16);
  }
  return os;
}

std::istream &operator>>(std::istream &is, Digest &digest) {
  is >> digest.length;
  // Must erase the newline we wrote before.
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::fill(digest.digest, digest.digest + Digest::maximum_size, 0);
  for (size_t i = 0; i < digest.length; i++) {
    digest.digest[i] = 16 * read_base_16(is);
    digest.digest[i] += read_base_16(is);
  }
  return is;
}
}  // namespace BigWord