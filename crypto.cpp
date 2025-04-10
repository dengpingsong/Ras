//
// Created by psg on 25-4-10.
//
#include "crypto.h"
#include <sstream>
#include <iomanip>
#include <CommonCrypto/CommonDigest.h>  // macOS SHA256

// 将字符串转为 mpz（适合加密）
mpz_class stringToMpz(const std::string& str) {
    mpz_class result;
    mpz_import(result.get_mpz_t(), str.size(), 1, 1, 0, 0, str.data());
    return result;
}

// 将 mpz 转回字符串（适合解密）
std::string mpzToString(const mpz_class& num) {
    size_t count = (mpz_sizeinbase(num.get_mpz_t(), 2) + 7) / 8;
    std::string str(count, '\0');
    mpz_export(&str[0], &count, 1, 1, 0, 0, num.get_mpz_t());
    str.resize(count);
    return str;
}

// base64 编码（简单实现）
std::string base64Encode(const std::string& input) {
    static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string output;
    int val = 0, valb = -6;
    for (uint8_t c : input) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            output.push_back(table[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) output.push_back(table[((val << 8) >> (valb + 8)) & 0x3F]);
    while (output.size() % 4) output.push_back('=');
    return output;
}

std::string base64Decode(const std::string& input) {
    static const char table[] = {
        62, -1, -1, -1, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
        -1, -1, -1,  0, -1, -1, -1,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25,
        -1, -1, -1, -1, -1,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
        36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
        46, 47, 48, 49, 50, 51
    };
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; ++i) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    std::string output;
    int val = 0, valb = -8;
    for (unsigned char c : input) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            output.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return output;
}

// SHA256（macOS CommonCrypto）
std::string sha256(const std::string& input) {
    unsigned char hash[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(input.data(), (CC_LONG)input.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}