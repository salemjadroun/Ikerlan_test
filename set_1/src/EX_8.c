#include "EX_8.h"

/*

  The global idea: in ECB, if we have two identical plaintext blocks, their ciphertext blocks 
  will be automatically identical. 
  So we are searching in each line if there is a compatibility between blocks of 16 bytes.

 */


int count_repeats(uint8_t *data, size_t len)
{
    int blocks = len / 16;
    int repeats = 0;
    for (int i = 0; i < blocks; i++)
        for (int j = i + 1; j < blocks; j++)
            if (memcmp(data + i * 16, data + j * 16, 16) == 0){ // Compare 16-byte blocks from a(i) and b(j=i+1 ...)
                repeats++;
            }
    return repeats;
}

int challenge_8()
{
    FILE *fp = fopen("../docs/8.txt", "r");
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        size_t len;
        uint8_t *data = hex_to_bytes(line, &len);
        if (count_repeats(data, len) > 0) {
            printf("ECB mode detected in line: %s\n", line);
        }
        free(data);
    }
    fclose(fp);
    return 0;
}
