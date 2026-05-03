#include "EX_18.h"



uint8_t *aes_128_ctr(uint8_t *data, size_t len, uint8_t *key, uint64_t nonce, size_t *out_len)
{
    
    //nonce must be unique per message
    //nonce could be from 0 to 2^64 - 1 (2^8 repeated in 8 bytes)
    uint8_t *out = malloc(len);
    uint8_t counter_block[16];
    // Nonce in the first 8 bytes, little-endian, fixed for the whole message
    for (int j = 0; j < 8; j++)
        counter_block[j] = (uint8_t)(nonce >> (8 * j));

    // The counter is it always starting on 0 and increment till finishing the encryption of all bytes 
    // needed to xor with the plaintext
    for (size_t i = 0; i < len; i += 16) {
        uint64_t block_count = i / 16;
        // Block count in the last 8 bytes, little-endian, increments per block
        for (int j = 0; j < 8; j++)
            counter_block[8 + j] = (uint8_t)(block_count >> (8 * j));

        int tmp;
        uint8_t *keystream = aes_128_ecb_encrypt(counter_block, 16, key, &tmp);

        size_t BlockSize = (len - i < 16) ? len - i : 16; // last block may be shorter
        for (size_t j = 0; j < BlockSize; j++)
            out[i + j] = data[i + j] ^ keystream[j];
        free(keystream);
    }
    *out_len = len;
    return out;
}


int challenge_18()
{
    uint8_t *key = (uint8_t *)"YELLOW SUBMARINE";
    char *b64 = "L77na/nrFsKvynd6HzOoG7GHTLXsTVu9qvY/2syLXzhPweyyMTJULu/6/kXX0KSvoOLSFQ==";

    // Decrypt the given ciphertext
    size_t ct_len, pt_len;
    uint8_t *ct = base64_to_bytes(b64, &ct_len);
    uint8_t *pt = aes_128_ctr(ct, ct_len, key, 0, &pt_len);
    printf("decrypted : %.*s\n", (int)pt_len, pt);
    free(ct);
    free(pt);

    return 0;
}