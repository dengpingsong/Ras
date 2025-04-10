//
// Created by psg on 25-4-10.
//
#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <string>
#include <sstream>
#include "rsa.h"

// 文件加解密
void encryptFile(const std::string& inFile, const std::string& outFile, RSA& rsa);
void decryptFile(const std::string& inFile, const std::string& outFile, RSA& rsa);

// 签名与验证
void signFile(const std::string& inFile, const std::string& sigFile, RSA& rsa);
bool verifyFile(const std::string& inFile, const std::string& sigFile, RSA& rsa);

#endif // FILE_OPS_H
