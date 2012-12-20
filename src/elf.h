#pragma once

#include "main.h"

struct executable {
    union {
        void*           mem;
        Elf32_Ehdr*     ehdr;
    };

    Elf32_Shdr*     text;
    Elf32_Shdr*     secs;
    size_t stub_offset;
} exec;

void elf_parse();
void elf_prepare();
void elf_crypt();
