//
// Created by psg on 25-4-10.
//
#include "file_ops.h"
#include "crypto.h"
#include <fstream>
#include <sstream>
#include <iostream>

constexpr size_t CHUNK_SIZE = 100;

void encryptFile(const std::string& inFile, const std::string& outFile, RSA& rsa) {
    std::ifstream in(inFile, std::ios::binary);
    std::ofstream out(outFile);

    if (!in || !out) {
        std::cerr << "File error: can't open " << inFile << " or " << outFile << std::endl;
        return;
    }

    char buffer[CHUNK_SIZE];
    while (in.read(buffer, CHUNK_SIZE) || in.gcount() > 0) {
        std::string chunk(buffer, in.gcount());
        mpz_class m = stringToMpz(chunk);
        mpz_class c = rsa.encrypt(m);
        out << c.get_str(16) << std::endl;  // 十六进制写入
    }
}

void decryptFile(const std::string& inFile, const std::string& outFile, RSA& rsa) {
    std::ifstream in(inFile);
    std::ofstream out(outFile, std::ios::binary);

    if (!in || !out) {
        std::cerr << "File error: can't open " << inFile << " or " << outFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        mpz_class c(line, 16);
        mpz_class m = rsa.decrypt(c);
        std::string chunk = mpzToString(m);
        out.write(chunk.data(), chunk.size());
    }
}

void signFile(const std::string& inFile, const std::string& sigFile, RSA& rsa) {
    std::ifstream in(inFile, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open file for signing: " << inFile << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();

    std::string hash = sha256(content);
    mpz_class hashMpz(hash, 16);
    mpz_class signature = rsa.decrypt(hashMpz);  // 私钥加密

    std::ofstream out(sigFile);
    out << signature.get_str(16) << std::endl;
}

bool verifyFile(const std::string& inFile, const std::string& sigFile, RSA& rsa) {
    std::ifstream in(inFile, std::ios::binary);
    std::ifstream sig(sigFile);
    if (!in || !sig) {
        std::cerr << "Cannot open file or signature for verification.\n";
        return false;
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();

    std::string hash = sha256(content);
    mpz_class hashMpz(hash, 16);

    std::string sigHex;
    std::getline(sig, sigHex);
    mpz_class signature(sigHex, 16);

    mpz_class decrypted = rsa.encrypt(signature);  // 公钥解密

    return decrypted == hashMpz;
}