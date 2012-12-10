#pragma once

#include <libelf.h>
#include <gelf.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdint.h>

#include "log.h"

#define unless(a) if (!(a))

struct input {
    int fd;
    struct stat st;
} input;
