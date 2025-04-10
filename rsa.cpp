//
// Created by psg on 25-4-10.
//

#include "rsa.h"
#include <gmp.h>
#include <gmpxx.h>
#include <random>
#include <ctime>

RSA::RSA(unsigned int keySize) {
    generateKeys(keySize);
}

void RSA::generateKeys(unsigned int keySize) {
    gmp_randclass randGen(gmp_randinit_mt);
    randGen.seed(static_cast<unsigned long>(time(nullptr)));

    // 生成大素数 p 和 q
    p = randGen.get_z_bits(keySize / 2);
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());

    q = randGen.get_z_bits(keySize / 2);
    mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());

    // 计算 n 和 phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // 通常选择 65537 作为 e
    e = 65537;
    while (gcd(e, phi) != 1) {
        e += 2;
    }

    // 计算私钥 d
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
}

mpz_class RSA::encrypt(const mpz_class& message) const {
    mpz_class result;
    mpz_powm(result.get_mpz_t(), message.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    return result;
}

mpz_class RSA::decrypt(const mpz_class& cipher) const {
    mpz_class result;
    mpz_powm(result.get_mpz_t(), cipher.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    return result;
}