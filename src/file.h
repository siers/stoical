#pragma once

#include "main.h"

struct file {
    int fd;
    struct stat st;
    void* mem;
};

extern struct file elf;
extern struct file stub;

void file_open(struct file *file, char path[]);
void* file_mmap(struct file *file);
void file_write(const struct file *file);
void file_close(struct file *file);
