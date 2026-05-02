#ifndef EX_15_H
#define EX_15_H

#include "EX_11.h"

int pkcs7_unpad(uint8_t *data, size_t len, size_t *out_len);
int challenge_15();

#endif