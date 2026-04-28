#ifndef EX_7_H
#define EX_7_H

#include "EX_6.h"
#include <openssl/evp.h>

uint8_t *aes_128_ecb_decrypt(uint8_t *data, size_t len, uint8_t *key, int *out_len);
int challenge_7();

#endif