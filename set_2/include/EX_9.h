#ifndef EX_9_H
#define EX_9_H

#include "EX_8.h"

uint8_t *pkcs7_pad(uint8_t *data, size_t len, int block_size, size_t *out_len);
int challenge_9();

#endif