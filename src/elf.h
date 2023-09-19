#pragma once

#include "main.h"

struct executable {
    union {
        void*           mem;
        Elf64_Ehdr*     ehdr;
    };

    Elf64_Shdr*     text;
    Elf64_Shdr*     secs;
    size_t stub_offset;
} exec;

void elf_parse();
void elf_prepare();
void elf_crypt();
