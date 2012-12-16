#pragma once

struct executable {
    void*           mem;
    void*           smem; // Stub's memory.
    Elf32_Ehdr*     ehdr;

    Elf32_Shdr*     text;
    Elf32_Shdr*     secs;

    size_t code_size;
} exec;

void encrypt_input();
