#include <libelf.h>
#include <unistd.h>
#include "log.h"
#include "crypt.h"

int
crypt()
{
    int fd;
    Elf *e;
    Elf_Kind ek;
    char b[255];

    assert_fatal((e = elf_begin(input, ELF_C_READ, NULL)) != NULL,
            "elf_begin failed: %s", elf_errmsg(-1));

    ek = elf_kind(e);
    assert_fatal(ek == ELF_K_ELF, "input file is not ELF");

    elf_end(e);

    return 0;
}
