#pragma once

#include "main.h"

extern void* replaces[][2];

enum {
    TEXT_ADDR,
    CRYPT_LEN,
    ENTRY_ADR,
    REPLACE_COUNT
};

enum {
    VAL_OLD,
    VAL_NEW,
};

void stub_prepare();
void stub_inject(uint8_t mem[]);
