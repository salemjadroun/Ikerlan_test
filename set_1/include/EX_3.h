#ifndef CH3_H
#define CH3_H

#include "EX_2.h"

uint8_t *single_byte_xor(uint8_t *bytes, size_t len, uint8_t key);
float english_score(uint8_t *bytes, size_t len);
float best_single_xor(uint8_t *bytes, size_t len, uint8_t *best_key);
int challenge_3();




#endif