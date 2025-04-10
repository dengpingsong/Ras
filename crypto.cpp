#include "crypto.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <CommonCrypto/CommonDigest.h>  // macOS SHA256

mpz_class stringToMpz(const std::string& str) {
    mpz_class result;
    mpz_import(result.get_mpz_t(), str.size(), 1, 1, 0, 0, str.data());
    return result;
}

std::string mpzToString(const mpz_class& num) {
    size_t count = (mpz_sizeinbase(num.get_mpz_t(), 2) + 7) / 8;
    std::string str(count, '\0');
    mpz_export(&str[0], &count, 1, 1, 0, 0, num.get_mpz_t());
    str.resize(count);
    return str;
}

std::string base64Encode(const std::string& input) {
    static const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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
    if (valb > -6)
        output.push_back(table[((val << 8) >> (valb + 8)) & 0x3F]);
    while (output.size() % 4)
        output.push_back('=');
    return output;
}

std::string base64Decode(const std::string& input) {
    static std::vector<int> T(256, -1);
    for (int i = 0; i < 64; ++i)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

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

std::string sha256(const std::string& input) {
    unsigned char hash[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(input.data(), (CC_LONG)input.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return oss.str();
}