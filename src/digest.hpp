#ifndef DIGEST_HPP
#define DIGEST_HPP

#include <openssl/evp.h>
#include <fstream>

struct Digest {
  unsigned int length = 0;  // OpenSSL API uses unsigned int.
  unsigned char digest[EVP_MAX_MD_SIZE] = {0};

  bool operator==(const Digest &other) const;
};

std::ostream &operator<<(std::ostream &os, const Digest &digest);

std::istream &operator>>(std::istream &is, Digest &digest);

/**
 * Produces a Digest object from the contents of a file.
 */
Digest digest_file(const std::string &filename);

#endif
