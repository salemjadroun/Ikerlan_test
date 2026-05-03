/* the idea of this attack we know that the nonce 0 is fixed for all the messages
 so we have all ciphertexts encrypted with the same nonce and key
 we can test all the possible key values from 0 to 255 and look for the one that produces the most readable text (most likely the correct key)
*/
#include "EX_19.h"


static const char *text[40] = {
    "SSBoYXZlIG1ldCB0aGVtIGF0IGNsb3NlIG9mIGRheQ==",
    "Q29taW5nIHdpdGggdml2aWQgZmFjZXM=",
    "RnJvbSBjb3VudGVyIG9yIGRlc2sgYW1vbmcgZ3JleQ==",
    "RWlnaHRlZW50aC1jZW50dXJ5IGhvdXNlcy4=",
    "SSBoYXZlIHBhc3NlZCB3aXRoIGEgbm9kIG9mIHRoZSBoZWFk",
    "T3IgcG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
    "T3IgaGF2ZSBsaW5nZXJlZCBhd2hpbGUgYW5kIHNhaWQ=",
    "UG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
    "QW5kIHRob3VnaHQgYmVmb3JlIEkgaGFkIGRvbmU=",
    "T2YgYSBtb2NraW5nIHRhbGUgb3IgYSBnaWJl",
    "VG8gcGxlYXNlIGEgY29tcGFuaW9u",
    "QXJvdW5kIHRoZSBmaXJlIGF0IHRoZSBjbHViLA==",
    "QmVpbmcgY2VydGFpbiB0aGF0IHRoZXkgYW5kIEk=",
    "QnV0IGxpdmVkIHdoZXJlIG1vdGxleSBpcyB3b3JuOg==",
    "QWxsIGNoYW5nZWQsIGNoYW5nZWQgdXR0ZXJseTo=",
    "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4=",
    "VGhhdCB3b21hbidzIGRheXMgd2VyZSBzcGVudA==",
    "SW4gaWdub3JhbnQgZ29vZCB3aWxsLA==",
    "SGVyIG5pZ2h0cyBpbiBhcmd1bWVudA==",
    "VW50aWwgaGVyIHZvaWNlIGdyZXcgc2hyaWxsLg==",
    "V2hhdCB2b2ljZSBtb3JlIHN3ZWV0IHRoYW4gaGVycw==",
    "V2hlbiB5b3VuZyBhbmQgYmVhdXRpZnVsLA==",
    "U2hlIHJvZGUgdG8gaGFycmllcnM/",
    "VGhpcyBtYW4gaGFkIGtlcHQgYSBzY2hvb2w=",
    "QW5kIHJvZGUgb3VyIHdpbmdlZCBob3JzZS4=",
    "VGhpcyBvdGhlciBoaXMgaGVscGVyIGFuZCBmcmllbmQ=",
    "V2FzIGNvbWluZyBpbnRvIGhpcyBmb3JjZTs=",
    "SGUgbWlnaHQgaGF2ZSB3b24gZmFtZSBpbiB0aGUgZW5kLA==",
    "U28gc2Vuc2l0aXZlIGhpcyBuYXR1cmUgc2VlbWVkLA==",
    "U28gZGFyaW5nIGFuZCBzd2VldCBoaXMgdGhvdWdodC4=",
    "VGhpcyBvdGhlciBtYW4gSSBoYWQgZHJlYW1lZA==",
    "QSBkcnVua2VuLCB2YWluLWdsb3Jpb3VzIGxvdXQu",
    "SGUgaGFkIGRvbmUgbW9zdCBiaXR0ZXIgd3Jvbmc=",
    "VG8gc29tZSB3aG8gYXJlIG5lYXIgbXkgaGVhcnQs",
    "WWV0IEkgbnVtYmVyIGhpbSBpbiB0aGUgc29uZzs=",
    "SGUsIHRvbywgaGFzIHJlc2lnbmVkIGhpcyBwYXJ0",
    "SW4gdGhlIGNhc3VhbCBjb21lZHk7",
    "SGUsIHRvbywgaGFzIGJlZW4gY2hhbmdlZCBpbiBoaXMgdHVybiw=",
    "VHJhbnNmb3JtZWQgdXR0ZXJseTo=",
    "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4="
};


int challenge_19()
{
    // generate a random key
    uint8_t key[16];
    random_bytes(key, 16);

    //encrypt every line with the same (key, nonce=0).
    // same key + same nonce = same keystream
       
    uint8_t *ciphertexts[40];
    size_t   lengths[40];

    //loop all the lines and encrypt them with the same key and nonce 0, store the ciphertexts and their lengths in arrays
    for (int i = 0; i < 40; i++) {
        size_t pt_len;
        uint8_t *plaintext = base64_to_bytes(text[i], &pt_len);

        ciphertexts[i] = aes_128_ctr(plaintext, pt_len, key, 0, &lengths[i]);

        free(plaintext);
    }

    // find the length of the shortest line. we need to stop at the shortest one.
    size_t shortest = lengths[0];
    for (int i = 1; i < 40; i++) {
        if (lengths[i] < shortest)
            shortest = lengths[i];
    }

    // recover the keystream, one byte at a time
    uint8_t keystream[256];   // lines are short, 256 is plenty 

    for (size_t j = 0; j < shortest; j++) {

        // Build the column : the j-th byte of every ciphertext
        uint8_t column[40];
        for (int i = 0; i < 40; i++) {
            column[i] = ciphertexts[i][j];
        }

        // Find the byte that, XORed against the column,
        // produces the most english alphabet output.
        uint8_t recovered_byte;
        best_single_xor(column, 40, &recovered_byte);

        keystream[j] = recovered_byte;
    }

    // decrypt every line with the recovered keystream
    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < shortest; j++) {
            uint8_t plaintext_byte = ciphertexts[i][j] ^ keystream[j];
            printf("%c", plaintext_byte);
        }
        printf("\n");
    }

    for (int i = 0; i < 40; i++) {
        free(ciphertexts[i]);
    }

    return 0;
}