#include "EX_11.h"


/* 
  Detection Logic: Use a 48-byte identical plaintext to force block alignment.
  This ensures at least two identical 16-byte blocks even with a 5-10 byte prefix.
  We then compare adjacent ciphertext blocks; identical blocks = ECB mode.

 */


void random_bytes(uint8_t *buf, size_t len)
{
    for (size_t i = 0; i < len; i++)
        buf[i] = rand();
}

// The method followed : generate the key randomly, modify the plaintext by adding random bytes before and after, 
// then encrypt using either ECB or CBC mode randomly. if the mode is ecb we pad the plaintext and encrypt it.
// if the mode is cbc we generate a random iv and encrypt the plaintext using cbc mode.

uint8_t *encryption_oracle(uint8_t *input, size_t len, int *mode_used, size_t *out_len)
{
    uint8_t key[16];
    random_bytes(key, 16);
 
    // 5-10 random bytes before and after the plaintext
    size_t prefix_len = 5 + rand() % 6;
    size_t suffix_len = 5 + rand() % 6;
    size_t total_len = prefix_len + len + suffix_len;
    uint8_t *buffer = malloc(total_len);
    random_bytes(buffer, prefix_len);
    memcpy(buffer + prefix_len, input, len);
    random_bytes(buffer + prefix_len + len, suffix_len);
 
    uint8_t *ct;
    if (rand() % 2 == 0) {
        *mode_used = MODE_ECB;
        size_t padded_len;
        uint8_t *padded = pkcs7_pad(buffer, total_len, 16, &padded_len);
        int tmp;
        ct = aes_128_ecb_encrypt(padded, padded_len, key, &tmp);
        *out_len = padded_len;
        free(padded);
    } else {
        *mode_used = MODE_CBC;
        uint8_t iv[16];
        random_bytes(iv, 16);
        ct = aes_128_cbc_encrypt(buffer, total_len, key, iv, out_len);
    }
    free(buffer);
    return ct;
}

int detect_mode(uint8_t *ciphertext, size_t len)
{
    for (size_t i = 0; i + 32 <= len; i += 16) {
        if (memcmp(ciphertext + i, ciphertext + i + 16, 16) == 0)
            return MODE_ECB;
    }
    return MODE_CBC;
}

int challenge_11()
{
    uint8_t input[48];
    memset(input, 'A', 48);
 
    int mode;
    size_t ct_len;
    uint8_t *ct = encryption_oracle(input, 48, &mode, &ct_len);
    int guessed = detect_mode(ct, ct_len);
    printf("guessed %s, actual %s\n",
           guessed == MODE_ECB ? "ECB" : "CBC",
           mode    == MODE_ECB ? "ECB" : "CBC");
    free(ct);
    return 0;
}

