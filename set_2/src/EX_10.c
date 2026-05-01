
#include "EX_10.h"

// ECB encrypt counterpart of EX_7's decrypt, with PKCS#7 padding disabled (raw block transform)
uint8_t *aes_128_ecb_encrypt(uint8_t *data, size_t len, uint8_t *key, int *out_len)
{
    uint8_t *out = malloc(len);
    int tmp_len = 0, final_len = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    // we don t want openssl to pad here, this is just a raw 16 to 16 block transform,
    // padding is done once on the whole message in aes_128_cbc_encrypt
    EVP_CIPHER_CTX_set_padding(ctx, 0); 
    EVP_EncryptUpdate(ctx, out, &tmp_len, data, len);
    EVP_EncryptFinal_ex(ctx, out + tmp_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);
    *out_len = tmp_len + final_len;
    return out;
}


uint8_t *aes_128_cbc_encrypt(uint8_t *plaintext, size_t len, uint8_t *key, uint8_t *iv, size_t *out_len)
{
    // the idea is we don t want to pad every block , so we pad directly
    //  the whole plaintext (so at max we have 16 byte of padding)
    size_t padded_len;
    uint8_t *padded = pkcs7_pad(plaintext, len, 16, &padded_len);
    uint8_t *out = malloc(padded_len);
    uint8_t block[16]; // tmp xoring calc
 
    // looping on blocks of 16 bytes of the padded plaintext
    for (size_t i = 0; i < padded_len; i += 16) { 
        uint8_t *prev = (i == 0) ? iv : out + i - 16;
        // XOR plaintext block with previous ciphertext
        for (int j = 0; j < 16; j++){
            block[j] = padded[i + j] ^ prev[j];
        }
        // ECB-encrypt the XORed block, write into out + i
        int tmp;
        uint8_t *enc = aes_128_ecb_encrypt(block, 16, key, &tmp);
        memcpy(out + i, enc, 16);
        free(enc);
    }
    free(padded);
    *out_len = padded_len;
    return out;
}


uint8_t *aes_128_cbc_decrypt(uint8_t *ciphertext, size_t len, uint8_t *key, uint8_t *iv, size_t *out_len)
{
    // ECB-decrypt the whole buffer, no padding
    uint8_t *raw = malloc(len);
    int tmp;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_DecryptUpdate(ctx, raw, &tmp, ciphertext, len);
    EVP_CIPHER_CTX_free(ctx);

    // XOR each block with previous ciphertext block
    uint8_t *out = malloc(len);
    for (size_t i = 0; i < len; i += 16) {
        uint8_t *prev = (i == 0) ? iv : ciphertext + i - 16;
        for (int j = 0; j < 16; j++)
            out[i + j] = raw[i + j] ^ prev[j];
    }
    free(raw);

    uint8_t pad = out[len - 1]; // read pad length from the last byte
    *out_len = len - pad;
    return out;
}


int challenge_10()
{
    uint8_t *key = (uint8_t *)"YELLOW SUBMARINE";
    uint8_t iv[16] = {0};
 
    
    // Decrypt 10.txt
    FILE *fp = fopen(DOCS_DIR "/10.txt", "r");
    char b64[20000] = {0};
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        strcat(b64, line);
    }
    fclose(fp);
 
    size_t data_len, plain_len;
    uint8_t *data = base64_to_bytes(b64, &data_len);
    uint8_t *plain = aes_128_cbc_decrypt(data, data_len, key, iv, &plain_len);
    printf("%.*s\n", (int)plain_len, plain);
 
    free(data);
    free(plain);
    return 0;
 
}



