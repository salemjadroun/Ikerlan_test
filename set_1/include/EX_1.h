#ifndef EX_1_H
#define EX_1_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Functions needed in the first challenge

uint8_t hex_char_to_val(char c);
uint8_t *hex_to_bytes(char *hex, size_t *out_len);
char *bytes_to_base64(uint8_t *bytes, size_t len);
uint8_t base64_char_to_val(char c);
uint8_t *base64_to_bytes(const char *b64, size_t *out_len);

int challenge_1();


#endif