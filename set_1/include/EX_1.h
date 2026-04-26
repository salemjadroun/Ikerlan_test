#ifndef EX_1_H
#define EX_1_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Functions needed in the first challenge

uint8_t hex_char_to_val(char c);
uint8_t *hex_to_bytes(char *hex, size_t *out_len);
char *bytes_to_base64(const uint8_t *bytes, size_t len);

int challenge_1();


#endif