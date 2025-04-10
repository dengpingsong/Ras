//
// Created by psg on 25-4-10.
//

#include "rsa.h"
#include <iostream>
#include <string>

int main() {
    RSA rsa(1024);

    std::string input;
    std::cout << "Enter a number to encrypt (as a string of digits): ";
    std::cin >> input;

    mpz_class message(input);
    mpz_class ciphertext = rsa.encrypt(message);
    mpz_class decrypted = rsa.decrypt(ciphertext);

    std::cout << "Encrypted: " << ciphertext << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}