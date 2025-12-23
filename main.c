#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aes.h"

int main() {
    unsigned char input_data[] = "passphrase";
    unsigned char derived_key[SHA256_DIGEST_LENGTH]; // 32 bytes
    
    SHA256(input_data, strlen((char*)input_data), derived_key);
    
    printf("Derived key (hex): ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", derived_key[i]);
    }
    printf("\n");

    struct AES_ctx *schedule = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));

    AES_init_ctx(schedule, (uint8_t*)derived_key);

    printf("Full schedule (hex): ");
    for (int i = 0; i < AES_keyExpSize; i++) {
        printf("%02x", schedule->RoundKey[i]);
    }
    printf("\n");

    FILE *file_ptr;

    file_ptr = fopen("uncorrupted.bin", "wb");

    fwrite(schedule->RoundKey, AES_keyExpSize*sizeof(uint8_t), 1, file_ptr);

    fclose(file_ptr);

    memset(&derived_key, 0, sizeof(derived_key));

    // Start with upper-bound equals 8 for simple testing, can increase later after initial validation of method
    for (int i = 0; i < 8; i++) {
        int pos = arc4random_uniform(AES_keyExpSize*8);
        schedule->RoundKey[pos/8] ^= (1 << (pos % 8));
    }

    printf("Simulated corrupted schedule (hex): ");
    for (int i = 0; i < AES_keyExpSize; i++) {
        printf("%02x", schedule->RoundKey[i]);
    }
    printf("\n");

    file_ptr = fopen("corrupted.bin", "wb");

    fwrite(schedule->RoundKey, AES_keyExpSize*sizeof(uint8_t), 1, file_ptr);

    fclose(file_ptr);
    
    return 0;
}

