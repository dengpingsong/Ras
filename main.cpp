//
// Created by psg on 25-4-10.
//
#include <iostream>
#include "rsa.h"
#include "crypto.h"
#include "file_ops.h"

int main() {
    RSA rsa(1024);

    std::string msg = "Hello from RSA!";
    mpz_class m = stringToMpz(msg);
    mpz_class c = rsa.encrypt(m);
    mpz_class d = rsa.decrypt(c);
    std::cout << "原文: " << msg<<"\n 加密后:"<<mpzToString(c) << "\n解密后: " << mpzToString(d) << std::endl;

    encryptFile("example.txt", "encrypted.txt", rsa);
    decryptFile("encrypted.txt", "decrypted.txt", rsa);

    signFile("example.txt", "example.sig", rsa);
    bool valid = verifyFile("example.txt", "example.sig", rsa);
    std::cout << "签名验证: " << (valid ? "成功" : "失败") << std::endl;

    return 0;
}