//
// Created by psg on 25-4-10.
//

#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <gmpxx.h>

// 字符串 <-> mpz_class
mpz_class stringToMpz(const std::string& str);
std::string mpzToString(const mpz_class& num);

// Base64 编解码
std::string base64Encode(const std::string& input);
std::string base64Decode(const std::string& input);

// SHA256 哈希（macOS 使用 CommonCrypto）
std::string sha256(const std::string& input);

#endif // CRYPTO_H
