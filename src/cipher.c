#include "cipher.h"

void
cipher(uint8_t buf[], size_t size)
{
    size_t i;

    uint8_t key = 216;

    for (i = 0; i < size; i++) {
        buf[i] ^= key;
    }

    log("Crypted code.");
}
