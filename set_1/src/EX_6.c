#include "EX_6.h"

int hamming_distance(uint8_t *a, uint8_t *b, size_t len) {
    int distance = 0;
    for (size_t i = 0; i < len; i++) {
        uint8_t diff = a[i] ^ b[i];
        uint8_t mask = 1;
        for (int bit = 0; bit < 8; bit++) {
            if (diff & mask)
                distance++;
            mask <<= 1;
        }
    }
    return distance;
}