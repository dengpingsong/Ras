//
// Created by psg on 25-4-10.
//

#ifndef RSA_H
#define RSA_H

#include <gmpxx.h>

class RSA {
public:
    RSA(unsigned int bitLength = 1024);
    void generateKeys();
    mpz_class encrypt(const mpz_class& message);
    mpz_class decrypt(const mpz_class& ciphertext);

    mpz_class getPublicKeyE() const;
    mpz_class getPublicKeyN() const;

private:
    mpz_class p, q, n, phi;
    mpz_class e, d;
    unsigned int keyLength;

    void generatePrimes();
    void calculateKeys();
};

#endif // RSA_H
