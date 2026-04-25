#include "EX_2.h"


uint8_t *xor_bytes(uint8_t *a, uint8_t *b, size_t len)
{
    uint8_t *out = malloc(len);
    for (size_t i = 0; i < len; i++)
        out[i] = a[i] ^ b[i];
    return out;
}

