#include "EX_5.h"

uint8_t *repeating_key_xor(uint8_t *text, size_t len, char *key, size_t key_len)
{
    uint8_t *out = malloc(len);
    size_t j = 0; // Key index

    for (size_t i = 0; i < len; i++){
        out[i] = text[i] ^ key[j++];
        
        if (j == key_len) j = 0;
    }
    return out;
}

int challenge_5()
{
    char *plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char *key = "ICE";
    size_t len = strlen(plaintext);
    size_t key_len = strlen(key);
    uint8_t *ciphertext = repeating_key_xor((uint8_t *)plaintext, len, key, key_len);

    
    print_hex(ciphertext, len);
    
    free(ciphertext);
    return 0;
}
