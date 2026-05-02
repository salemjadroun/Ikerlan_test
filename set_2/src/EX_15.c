#include "EX_15.h"

/*
   Global view : the check that we are doing is verifying that length is multiple of 16 and the pad writed 
   in last byte is btween 1 and 16, then we check that the last "pad" bytes are all the same as the value of pad. 
*/


int pkcs7_unpad(uint8_t *data, size_t len, size_t *out_len)
{
    if (len == 0 || len % 16 != 0) return 0;
    uint8_t pad = data[len - 1];
    if (pad < 1 || pad > 16) return 0;
    for (size_t i = len - pad; i < len; i++)
        if (data[i] != pad) return 0;
    *out_len = len - pad;
    return 1;
}


static void check(uint8_t *data, size_t len)
{
    size_t out_len;
    if (pkcs7_unpad(data, len, &out_len))
        printf("valid : %.*s\n", (int)out_len, data);
    else
        printf("invalid\n");
}


int challenge_15()
{
    check((uint8_t *)"ICE ICE BABY\x04\x04\x04\x04", 16);
    check((uint8_t *)"ICE ICE BABY\x05\x05\x05\x05", 16);
    check((uint8_t *)"ICE ICE BABY\x01\x02\x03\x04", 16);
    return 0;
}