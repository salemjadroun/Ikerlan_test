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

int challenge_7()
{
    FILE *fp = fopen("../docs/7.txt", "r");
    char b64[20000] = {0};
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        strcat(b64, line);
    }
    fclose(fp);

    size_t len;
    uint8_t *data = base64_to_bytes(b64, &len);
    int out_len;
    uint8_t *decrypted = aes_128_ecb_decrypt(data, len, (uint8_t *)"YELLOW SUBMARINE", &out_len);

    printf("%.*s\n", out_len, decrypted);

    free(decrypted);
    free(data);
    return 0;
}
