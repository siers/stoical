#pragma once

#include <errno.h>
#include <fcntl.h>
#include <libelf.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "log.h"
#include "cipher.h"
#include "file.h"
#include "elf.h"
#include "stub.h"

#define STUB_PATH "stub"
#define DUMMY_STUB_PATH "bin/stub.bin.tmpl"
#define STUB_PREPARE_SCRIPT "src/prepare_stub.rb"
