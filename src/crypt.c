#include "crypt.h"
#include "main.h"

static struct executable {
    Elf *elf;
    Elf_Kind kind;
    GElf_Ehdr ehdr;
} exec;

static void
do_checks()
{
    assert_fatal((exec.kind = elf_kind(exec.elf)) == ELF_K_ELF,
            "input file is not ELF");
    assert_fatal((gelf_getehdr(exec.elf, &exec.ehdr)) != NULL,
            "%s", elf_errmsg(-1));
    assert_fatal(exec.ehdr.e_type == ET_EXEC,
            "input file must be an executable");
}

/* Doesn't really crypt, just a name for the entry point.  */
int
crypt()
{
    assert_fatal((exec.elf = elf_begin(input, ELF_C_READ, NULL)) != NULL,
            "elf_begin failed: %s", elf_errmsg(-1));
    do_checks();
    elf_end(exec.elf);

    return 0;
}
