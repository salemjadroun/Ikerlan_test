#ifndef EX_18_H
#define EX_18_H
 
#include "EX_15.h"
 
uint8_t *aes_128_ctr(uint8_t *data, size_t len, uint8_t *key, uint64_t nonce, size_t *out_len);
int challenge_18();
 
#endif
 
