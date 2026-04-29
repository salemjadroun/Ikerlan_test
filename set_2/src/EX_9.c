#include "EX_9.h"

uint8_t *pkcs7_pad(uint8_t *data, size_t len, int block_size, size_t *out_len)
{
    uint8_t rem = len % block_size;
    uint8_t pad = block_size - rem;
    *out_len = len + pad;
    uint8_t *out = malloc(*out_len);
    memcpy(out, data, len);
    memset(out + len, pad, pad); //Fill the remaining 'pad' bytes with the value of 'pad' itself
    return out;
}


int challenge_9()
{
    char *text = "YELLOW SUBMARINE";
    size_t out_len;
    uint8_t *padded = pkcs7_pad((uint8_t *)text, strlen(text), 20, &out_len);

    print_hex(padded, out_len);

    free(padded);
    return 0;
}