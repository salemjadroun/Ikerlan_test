#include "EX_7.h"


/*
    Decrypting consists of the following stages:

    Setting up a context
    Initialising the decryption operation
    Providing ciphertext bytes to be decrypted
    Finalising the decryption operation
    
    */


uint8_t *aes_128_ecb_decrypt(uint8_t *data, size_t len, uint8_t *key, int *out_len)
{
    uint8_t *out = malloc(len);
    int tmp_len = 0, final_len = 0;
    /* final_len = the number of plaintext bytes from that last block after the padding was stripped 
      and tmp_len = the number of plaintext bytes from all the blocks except the last one
     */
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, out, &tmp_len, data, len); // tmp_len stores bytes processed till now , update treat the blocks len - 16 after removing padding
    EVP_DecryptFinal_ex(ctx, out + tmp_len, &final_len); // Decrypts the last block that Update was holding back 
    EVP_CIPHER_CTX_free(ctx);

    *out_len = tmp_len + final_len;
    return out;
}
