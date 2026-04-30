#ifndef EX_10_H
#define EX_10_H
 
#include "EX_9.h"
 
uint8_t *aes_128_ecb_encrypt(uint8_t *data, size_t len, uint8_t *key, int *out_len);
uint8_t *aes_128_cbc_encrypt(uint8_t *plaintext, size_t len, uint8_t *key, uint8_t *iv, size_t *out_len);
int challenge_10();
 
#endif
 
