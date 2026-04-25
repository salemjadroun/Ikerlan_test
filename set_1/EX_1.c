#include "EX_1.h"
 
//Global view of the implementation : hex --> bytes --> bin64

//a function help us to convert a hex char to his value
uint8_t hex_char_to_val(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
}
 
//take the hex string and return an array of uint8
uint8_t *hex_to_bytes(char *hex, size_t *out_len)
{
    size_t hex_len = strlen(hex);
    *out_len = hex_len / 2;
    uint8_t *bytes = malloc(*out_len);
 
   //take each two hexa char (4+4=8) and store them in one byte, the 1st takes the upper nibble and the 2nd takes the lower
    for (size_t i = 0; i < *out_len; i++) {
        uint8_t hi = hex_char_to_val(hex[2 * i]);
        uint8_t lo = hex_char_to_val(hex[2 * i + 1]);
        bytes[i] = (hi << 4) | lo;
    }
    return bytes;
}