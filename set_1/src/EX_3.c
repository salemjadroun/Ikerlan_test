#include "EX_3.h"

uint8_t *single_byte_xor(uint8_t *bytes, size_t len, uint8_t key)
{
    uint8_t *out = malloc(len);
    for (size_t i = 0; i < len; i++)
        out[i] = bytes[i] ^ key;
    return out;
}

float english_score(uint8_t *bytes, size_t len)
{
    float score = 0.0;
    for (size_t i = 0; i < len; i++) {
        if ((bytes[i] >= 'a' && bytes[i] <= 'z') ||
            (bytes[i] >= 'A' && bytes[i] <= 'Z') ||
            bytes[i] == ' ')
            score += 1.0;
    }
    return score / len;
}

float best_single_xor(uint8_t *bytes, size_t len, uint8_t *best_key)
{
    float best_score = 0.0;
    for (uint8_t key = 0; key < 255; key++) {
        uint8_t *xored = single_byte_xor(bytes, len, key);
        float score = english_score(xored, len);
        if (score > best_score) {
            best_score = score;
            *best_key = key;
        }
        free(xored);
    }
    return best_score;
}

int challenge_3()
{
    char *hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t len;
    uint8_t *bytes = hex_to_bytes(hex, &len);
    
    uint8_t best_key;
    best_single_xor(bytes, len, &best_key);
    
    uint8_t *decrypted = single_byte_xor(bytes, len, best_key);
    printf("Best key: %d\n", best_key);
    printf("Decrypted: %s\n", decrypted);
    free(decrypted);
    free(bytes);
}
