#ifndef EX_11_H
#define EX_11_H
 
#include "EX_10.h"
 
#define MODE_ECB 0
#define MODE_CBC 1
 
void random_bytes(uint8_t *buf, size_t len);
uint8_t *encryption_oracle(uint8_t *input, size_t len, int *mode_used, size_t *out_len);
int detect_mode(uint8_t *ciphertext, size_t len);
int challenge_11();
 
#endif
