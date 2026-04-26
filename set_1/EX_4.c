#include "EX_4.h"


/* 

    the Global View : 

        1. Open the file
        2. Read each line (exactly 60 hex chars = 30 bytes)
        3. Try all 256 keys using best_single_xor and score the result
        4. Keep track of the best score across all lines
        5. Decrypt and print the winner

*/


int challenge_4()
{
    FILE *fp = fopen("4.txt", "r");
    char line[64];
    float best_score = 0.0;
    uint8_t best_key = 0;
    char winner[64];
    while (fscanf(fp, "%60s", line) == 1) { 
        size_t len;
        uint8_t *bytes = hex_to_bytes(line, &len);
        
        uint8_t key;
        float score = best_single_xor(bytes, len, &key);
        if (score > best_score) {
            best_score = score;
            best_key = key;
            strncpy(winner, line, sizeof(winner));
        }
        free(bytes);
    }
    fclose(fp);


    size_t len;
    uint8_t *bytes = hex_to_bytes(winner, &len);
    uint8_t *decrypted = single_byte_xor(bytes, len, best_key);

    printf("Best key: %d\n", best_key);
    printf("Decrypted: %.*s\n", (int)len, decrypted); //fix length to avoid reading extra memory
    free(bytes);
    free(decrypted);
    
    return 0;
}