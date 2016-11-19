#include "digest.hpp"
#include <openssl/evp.h>

bool Digest::operator==(const Digest &other) const {
  if (length != other.length) {
    return false;
  }
  for (size_t i = 0; i < static_cast<size_t>(length); i++) {
    if (digest[i] != other.digest[i]) {
      return false;
    }
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, const Digest &digest) {
  os << digest.length;
  os << '\n';
  for (size_t i = 0; i < EVP_MAX_MD_SIZE; i++) {
    os << digest.digest[i];
  }
  return os;
}

std::istream &operator>>(std::istream &is, Digest &digest) {
  is >> digest.length;
  for (size_t i = 0; i < EVP_MAX_MD_SIZE; i++) {
    is >> digest.digest[i];
  }
  return is;
}

Digest digest_file(const std::string &filename) {
  EVP_MD_CTX *mdctx;
  const size_t buffer_size = 4096;
  unsigned char buffer[buffer_size];
  bool digesting = true;
  mdctx = EVP_MD_CTX_create();
  std::ifstream input(filename);
  OpenSSL_add_all_digests();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
  while (digesting) {
    input.read((char *)buffer, buffer_size);
    const size_t read_bytes = input.gcount();
    EVP_DigestUpdate(mdctx, buffer, read_bytes);
    digesting = read_bytes == buffer_size;
  }
  Digest digest;
  EVP_DigestFinal_ex(mdctx, digest.digest, &digest.length);
  EVP_MD_CTX_destroy(mdctx);
  return digest;
}
