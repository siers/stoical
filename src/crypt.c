#include <sys/mman.h>
#include "crypt.h"
#include "main.h"

static struct executable {
    void*           mem;
    Elf32_Ehdr      ehdr;

    Elf32_Shdr*     text;
    Elf32_Shdr*     secs;
} exec;

static void
parse()
{
    exec.mem = mmap(0, input.st.st_size, PROT_READ | PROT_WRITE,
            MAP_PRIVATE, input.fd, 0);
    memcpy(&exec.ehdr, exec.mem, sizeof(exec.ehdr));
    assert_fatal(exec.ehdr.e_type == ET_EXEC,
            "input file must be an executable");

    exec.secs = exec.mem + exec.ehdr.e_shoff;
}

static void
find_text()
{
    Elf32_Shdr* str = &exec.secs[exec.ehdr.e_shstrndx];

    int i;
    char* sh_name;
    Elf32_Shdr* sec;

    for (i = 0; i < exec.ehdr.e_shnum; i++)
    {
        sec     = &exec.secs[i];
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
    unsigned char *text = exec.mem + exec.text->sh_offset;
    unsigned int i;

    for (i = 0; i < exec.text->sh_size; i++) {
        fprintf(stderr, "%c", text[i]);
    }
}

void
encrypt_input()
{
    parse();
    find_text();
    print_info();
    alter_text();
}
