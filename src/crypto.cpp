#include "crypto.hpp"

#include <mbedtls/aes.h>
#include <mbedtls/base64.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <random>
#include <sstream>

namespace DIG {
namespace Crypto {

#ifndef DISABLE_ENCRYPT

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

#else

Err encrypt(std::ostream& output,
            std::istream& input,
            const std::string& _key) {
  output << input.rdbuf();
  return Err::OK;
}

Err decrypt(std::ostream& output,
            std::istream& input,
            const std::string& _key) {
  output << input.rdbuf();
  return Err::OK;
}

#endif

Err encode(std::ostream& output, std::istream& input) {
  constexpr auto LEN = 24;
  constexpr auto LEN_O = 4 * LEN / 3;
  char input_b[LEN];
  char output_b[LEN_O];
  std::size_t o_len = 0;
  while (input.good()) {
    input.read(input_b, LEN);
    mbedtls_base64_encode((unsigned char*)output_b, LEN_O, &o_len,
                          (unsigned char*)input_b, input.gcount());
    output.write(output_b, o_len);
  }

  return Err::OK;
}

Err dencode(std::ostream& output, std::istream& input) {
  constexpr auto LEN = 24;
  constexpr auto LEN_O = 3 * LEN / 4;
  char input_b[LEN];
  char output_b[LEN_O];
  std::size_t o_len = 0;
  while (input.good()) {
    input.read(input_b, LEN);
    mbedtls_base64_decode((unsigned char*)output_b, LEN_O, &o_len,
                          (unsigned char*)input_b, input.gcount());
    output.write(output_b, o_len);
  }

  return Err::OK;
  return Err::OK;
}

std::string random(const uint_fast8_t& length) {
  std::random_device rd;
  std::uniform_int_distribution<uint8_t> dist(33, 125);
  std::stringstream ss;
  for (uint_fast16_t i = 0; i < length; i++) {
    ss << (char)dist(rd);
  }
  return ss.str();
}

}  // namespace Crypto
}  // namespace DIG