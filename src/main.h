#pragma once

#include <libelf.h>
#include <gelf.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdint.h>
#include <sys/mman.h>

#include "log.h"

#define COUNT_OF(x) (sizeof(x) / sizeof(0[x])
#define unless(a) if (!(a))
#define STUB_PATH "stub"
#define DUMMY_STUB_PATH "bin/stub.bin.tmpl"

struct input {
    /* File's. */
    int fd;
    struct stat st;

    /* Stub's. */
    int sfd;
    struct stat sst;
} input;

extern void* replaces[][2];

enum {
    TEXT_ADDR,
    CRYPT_LEN,
    REPLACE_COUNT
};

enum {
    VAL_OLD,
    VAL_NEW,
};

void prepare_stub();
