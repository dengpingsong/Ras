//
// Created by psg on 25-4-10.
//
#ifndef RSA_H
#define RSA_H

#include <gmpxx.h>

class RSA {
public:
    RSA(unsigned int keySize = 1024);

    mpz_class encrypt(const mpz_class& message) const;
    mpz_class decrypt(const mpz_class& cipher) const;

    mpz_class getPublicKeyE() const { return e; }
    mpz_class getPublicKeyN() const { return n; }

private:
    mpz_class p, q, n, phi, e, d;

    void generateKeys(unsigned int keySize);
};

#endif // RSA_H