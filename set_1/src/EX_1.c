#include "EX_1.h"
 
//Global view of the implementation : hex --> bytes --> bin64


// add base64_to_bytes function to be used in challenge 6 and 7
uint8_t base64_char_to_val(char c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0;
}

uint8_t *base64_to_bytes(const char *b64, size_t *out_len)
{
    size_t len = strlen(b64);
    *out_len = len * 3 / 4; //4 chars = 3 bytes

    //check for padding '=' characters
    if (b64[len - 1] == '=') (*out_len)--;
    if (b64[len - 2] == '=') (*out_len)--;

    uint8_t *bytes = malloc(*out_len);

    size_t j = 0; // index for the output byte array

    for (size_t i = 0; i < len; i += 4) {
        // Combine each four 6 bit into one 24 bit block
        uint32_t combined = (base64_char_to_val(b64[i]) << 18) |
                            (base64_char_to_val(b64[i + 1]) << 12) |
                            (base64_char_to_val(b64[i + 2]) << 6) |
                             base64_char_to_val(b64[i + 3]);

        // Extract the 3 bytes from the 24 bit block and store them
        if (j < *out_len) bytes[j++] = (combined >> 16) & 0xFF;
        if (j < *out_len) bytes[j++] = (combined >> 8) & 0xFF;
        if (j < *out_len) bytes[j++] = combined & 0xFF;
    }
    return bytes;
}

//Challenge 1 functions
//a function help us to convert a hex char to his value
uint8_t hex_char_to_val(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
}
 
//take the hex string and return an array of uint8
uint8_t *hex_to_bytes(char *hex, size_t *out_len)
{
    size_t hex_len = strlen(hex);
    *out_len = hex_len / 2;
    uint8_t *bytes = malloc(*out_len);
 
   //take each two hexa char (4+4=8) and store them in one byte, the 1st takes the upper nibble and the 2nd takes the lower
    for (size_t i = 0; i < *out_len; i++) {
        uint8_t hi = hex_char_to_val(hex[2 * i]);
        uint8_t lo = hex_char_to_val(hex[2 * i + 1]);
        bytes[i] = (hi << 4) | lo;
    }
    return bytes;
}

//take raw bytes and return a base64 string
char *bytes_to_base64(uint8_t *bytes, size_t len)
{
    const char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    //Every 3 bytes produce 4 base64 chars (8*3=6*4)
    size_t out_len = 4 * ((len + 2) / 3); //+2 just for ceiling
    char *out = malloc(out_len + 1);
    size_t j = 0;
 
    for (size_t i = 0; i < len; i += 3) {
    
        uint32_t b0 = bytes[i];
        uint32_t b1 = (i + 1 < len) ? bytes[i + 1] : 0;
        uint32_t b2 = (i + 2 < len) ? bytes[i + 2] : 0;
        //combine all the three bytes in one variable of 32 so we can devide the 24 bits into 6*4
        uint32_t combined = (b0 << 16) | (b1 << 8) | b2;
 
        //extract the char aligned to each 6 bits from the table 
        out[j++] = table[(combined >> 18) & 0x3F]; //(3F)16 = (00111111)2
        out[j++] = table[(combined >> 12) & 0x3F];
        out[j++] = (i + 1 < len) ? table[(combined >> 6) & 0x3F] : '=';
        out[j++] = (i + 2 < len) ? table[(combined >> 0) & 0x3F] : '=';
    }
 
    out[j] = '\0';
    return out;
}


int challenge_1(){


  size_t out_len;
  char *hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  uint8_t * arr = hex_to_bytes(hex, &out_len);
  char *b64 = bytes_to_base64(arr, out_len);
  printf("Base64 : %s\n", b64);
  
  
  free(arr);
  free(b64);
  return 0 ;
}