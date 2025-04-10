//
// Created by psg on 25-4-10.
//
#include "utils.h"
#include <gmp.h>
#include <ctime>

extern gmp_randstate_t randState;

mpz_class generatePrime(unsigned int bitLength) {
    mpz_class prime;
    mpz_urandomb(prime.get_mpz_t(), randState, bitLength);
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
    return prime;
}