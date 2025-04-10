//
// Created by psg on 25-4-10.
//
#include "rsa.h"
#include "utils.h"
#include <gmpxx.h>
#include <ctime>

RSA::RSA(unsigned int bitLength) : keyLength(bitLength) {
    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, static_cast<unsigned long>(time(nullptr)));
    generateKeys();
}

void RSA::generateKeys() {
    generatePrimes();
    calculateKeys();
}

void RSA::generatePrimes() {
    p = generatePrime(keyLength / 2);
    q = generatePrime(keyLength / 2);
    n = p * q;
    phi = (p - 1) * (q - 1);
}

void RSA::calculateKeys() {
    e = 65537; // commonly used public exponent
    mpz_gcd(gcd.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
    while (gcd != 1) {
        e += 2;
        mpz_gcd(gcd.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
    }

    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
}

mpz_class RSA::encrypt(const mpz_class& message) {
    mpz_class ciphertext;
    mpz_powm(ciphertext.get_mpz_t(), message.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    return ciphertext;
}

mpz_class RSA::decrypt(const mpz_class& ciphertext) {
    mpz_class plaintext;
    mpz_powm(plaintext.get_mpz_t(), ciphertext.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    return plaintext;
}

mpz_class RSA::getPublicKeyE() const { return e; }
mpz_class RSA::getPublicKeyN() const { return n; }

gmp_randstate_t RSA::randState;
mpz_class RSA::gcd;