#include <sys/mman.h>
#include "crypt.h"
#include "main.h"

static struct executable {
    void*           mem;
    Elf32_Ehdr      ehdr;

    Elf32_Shdr*     text;
} exec;

static void
parse()
{
    exec.mem = mmap(0, input.st.st_size, PROT_READ | PROT_WRITE,
            MAP_PRIVATE, input.fd, 0);
    memcpy(&exec.ehdr, exec.mem, sizeof(exec.ehdr));

    assert_fatal(exec.ehdr.e_type == ET_EXEC,
            "input file must be an executable");
}

static void
find_text()
{
    int sec_size          = exec.ehdr.e_shentsize;
    Elf32_Shdr* secs_base = exec.mem + exec.ehdr.e_shoff;
    Elf32_Shdr* str       = &secs_base[exec.ehdr.e_shstrndx];

    int i;
    char* sh_name;
    Elf32_Shdr* sec;

    for (i = 0; i < exec.ehdr.e_shnum; i++)
    {
        sec = &secs_base[i];
        sh_name = (exec.mem + str->sh_offset) + sec->sh_name;

        if (strcmp(sh_name, ".text") == 0) {
            exec.text = sec;
            return log(".text found");
        }
    }

    assert_fatal(0, "Couldn't find .text section.");
}

static void
print_info()
{
    log(".text = 0x%.8x.", exec.text);
    log(".text.size = %.2f KiB", exec.text->sh_size / 1024.0);
}

static void
alter_text()
{
}

void
crypt()
{
    parse();
    find_text();
    print_info();
    alter_text();
}
