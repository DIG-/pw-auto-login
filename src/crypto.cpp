#include "crypto.hpp"

#include <mbedtls/aes.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <random>

namespace DIG {
namespace Crypto {

const uint_fast8_t BLOCK_SIZE = 16;

Err extract_key(uint8_t (&key)[32], const std::string& _key) {
  uint_fast8_t key_length = std::min((uint8_t)32, (uint8_t)_key.length());
  memcpy(key, _key.c_str(), key_length);
  if (key_length < 32) {
    memset(&(key[key_length]), 0, 32 - key_length);
  }
  return Err::OK;
}

Err encrypt(std::ostream& output,
            std::istream& input,
            const std::string& _key) {
  uint8_t key[32];
  uint8_t iv[BLOCK_SIZE];
  uint8_t input_v[BLOCK_SIZE];
  uint8_t output_v[BLOCK_SIZE];

  extract_key(key, _key);

  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, key, 256);

  std::default_random_engine rand;
  rand.seed(std::chrono::system_clock::now().time_since_epoch().count() *
            rand());
  for (uint_fast8_t i = 0; i < BLOCK_SIZE; i++) {
    iv[i] = rand();
  }

  output.write((char*)iv, BLOCK_SIZE);
  bool had_padding = false;
  while (input.good() || !had_padding) {
    input.read((char*)input_v, BLOCK_SIZE);
    if (input.gcount() < BLOCK_SIZE) {
      had_padding = true;
      uint_fast8_t pad = BLOCK_SIZE - input.gcount();
      for (uint_fast8_t i = input.gcount(); i < BLOCK_SIZE; i++) {
        input_v[i] = pad;
      }
    }
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, BLOCK_SIZE, iv, input_v,
                          output_v);
    output.write((char*)output_v, BLOCK_SIZE);
  }

  return Err::OK;
}

Err decrypt(std::ostream& output,
            std::istream& input,
            const std::string& _key) {
  uint8_t key[32];
  uint8_t iv[BLOCK_SIZE];
  uint8_t input_v[BLOCK_SIZE];
  uint8_t output_v[BLOCK_SIZE];

  extract_key(key, _key);

  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_dec(&aes, key, 256);

  input.read((char*)iv, BLOCK_SIZE);
  if (input.gcount() != BLOCK_SIZE) {
    return Err::NOT_IMPLEMENTED;
  }

  while (input.good()) {
    input.read((char*)input_v, BLOCK_SIZE);
    if (input.gcount() != BLOCK_SIZE) {
      // While decrypting, source must be equals BLOCK_SIZE
      return Err::NOT_IMPLEMENTED;
    }
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, BLOCK_SIZE, iv, input_v,
                          output_v);
    if (input.eof() || (input.peek() == EOF && input.eof())) {
      auto pad = output_v[BLOCK_SIZE - 1];
      if (pad >= BLOCK_SIZE) {
        continue;
      }
      output.write((char*)output_v, BLOCK_SIZE - pad);
      continue;
    }

    output.write((char*)output_v, BLOCK_SIZE);
  }
  return Err::OK;
}

}  // namespace Crypto
}  // namespace DIG