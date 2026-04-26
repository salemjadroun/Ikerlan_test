#include "EX_3.h"

uint8_t *single_byte_xor(uint8_t *bytes, size_t len, uint8_t key)
{
    uint8_t *out = malloc(len);
    for (size_t i = 0; i < len; i++)
        out[i] = bytes[i] ^ key;
    return out;
}

float english_score(uint8_t *bytes, size_t len)
{
    float score = 0.0;
    for (size_t i = 0; i < len; i++) {
        if ((bytes[i] >= 'a' && bytes[i] <= 'z') ||
            (bytes[i] >= 'A' && bytes[i] <= 'Z') ||
            bytes[i] == ' ')
            score += 1.0;
    }
    return score / len;
}

