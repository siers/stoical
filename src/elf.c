#include "elf.h"

struct file elf;

static void
find_text()
{
    Elf64_Shdr* str = &exec.secs[exec.ehdr->e_shstrndx];

    int i;
    char* sh_name;
    Elf64_Shdr* sec;

    for (i = 0; i < exec.ehdr->e_shnum; i++)
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
sanity_check()
{
    assert_fatal(exec.ehdr->e_type == ET_EXEC,
            "input file must be an executable");
}

static void
print_info()
{
    log(".text        = 0x%.8x.",  exec.text);
    log(".text.size   = %.2f KiB", exec.text->sh_size / 1024.0);
    log(".text.shaddr = 0x%.8x.",  exec.text->sh_addr);
    log(".e_entry     = 0x%.8x.",  exec.ehdr->e_entry);
}

void
elf_parse()
{
    exec.ehdr = exec.mem = file_mmap(&elf);
    exec.secs = exec.mem + exec.ehdr->e_shoff;
    sanity_check();

    find_text();
    print_info();
}

static void
set_replaces()
{
    exec.stub_offset   = exec.text->sh_size - stub.st.st_size - 1;
    replaces[TEXT_ADDR][VAL_NEW] = (void*) exec.text->sh_addr;
    replaces[ENTRY_ADR][VAL_NEW] = (void*) exec.ehdr->e_entry;
    replaces[CRYPT_LEN][VAL_NEW] = (void*) exec.stub_offset;
    exec.ehdr->e_entry = exec.text->sh_addr + exec.stub_offset;
}

static void
set_writable()
{
    size_t i;
    Elf64_Phdr *phdrs = exec.mem + exec.ehdr->e_phoff;

    exec.text->sh_flags |= SHF_WRITE;

    for (i = 0; i < exec.ehdr->e_phnum; ++i) {
        phdrs[i].p_flags |= PF_W;
    }
}

void
elf_prepare()
{
    set_replaces();
    set_writable();
}

void
elf_crypt()
{
    uint8_t *text = exec.mem + exec.text->sh_offset;
    cipher     (text, exec.text->sh_size);
    stub_inject(text + exec.stub_offset);
}
