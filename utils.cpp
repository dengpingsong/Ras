//
// Created by psg on 25-4-10.
//
#include "utils.h"
#include <gmp.h>
#include <ctime>

gmp_randclass randState(gmp_randinit_mt);  // ✅ 这是变量定义
// 必须只有一处！

mpz_class generatePrime(unsigned int bits) {
    return randState.get_z_bits(bits);
}

void initRand() {
    randState.seed(static_cast<unsigned long>(time(nullptr)));
}