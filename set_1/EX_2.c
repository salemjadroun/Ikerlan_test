#include "EX_2.h"


uint8_t *xor_bytes(uint8_t *a, uint8_t *b, size_t len)
{
    uint8_t *out = malloc(len);
    for (size_t i = 0; i < len; i++)
        out[i] = a[i] ^ b[i];
    return out;
}

void print_hex(uint8_t *bytes, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%02x", bytes[i]);
    printf("\n");
}


int challenge_2(){
  char *hexa = "1c0111001f010100061a024b53535009181c";
  char *hexb = "686974207468652062756c6c277320657965";
  
  size_t len_a, len_b;
  
  uint8_t *a = hex_to_bytes(hexa, &len_a);
  uint8_t *b = hex_to_bytes(hexb, &len_b);

  uint8_t *xored = xor_bytes(a,b,len_a);
  
  print_hex(xored,len_a);
  free(a);
  free(b);
  free(xored);

  return 0;

}