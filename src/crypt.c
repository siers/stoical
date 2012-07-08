#include "crypt.h"
#include "main.h"

static struct executable {
    Elf *elf;
    Elf_Kind kind;
    GElf_Ehdr ehdr;

    GElf_Shdr text;
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

static void
print_info()
{
    log("The entry point is at 0x%.8x.", exec.ehdr.e_entry);
    log(".text.size = 0x%xb", exec.text.sh_size);
}

static void
find_text()
{
    Elf_Scn *scn = 0;
    char* sh_name;

    while ((scn = elf_nextscn(exec.elf, scn)) != 0)
    {
        gelf_getshdr(scn, &exec.text);
        sh_name = elf_strptr(exec.elf, exec.ehdr.e_shstrndx, exec.text.sh_name);

        if (strcmp(sh_name, ".text") == 0) {
            return log(".text found");
        }
    }

    assert_fatal(0, "Couldn't find .text section.");
}

/* Doesn't really crypt, just a name for the entry point.  */
int
crypt()
{
    assert_fatal((exec.elf = elf_begin(input, ELF_C_READ, NULL)) != NULL,
            "elf_begin failed: %s", elf_errmsg(-1));
    do_checks();
    find_text();
    print_info();
    elf_end(exec.elf);

    return 0;
}
