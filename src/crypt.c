#include "crypt.h"
#include "main.h"

int
crypt()
{
    Elf *e;
    Elf_Kind ek;

    assert_fatal((e = elf_begin(input, ELF_C_READ, NULL)) != NULL,
            "elf_begin failed: %s", elf_errmsg(-1));

    ek = elf_kind(e);
    assert_fatal(ek == ELF_K_ELF, "input file is not ELF");

    elf_end(e);

    return 0;
}
