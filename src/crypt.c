#include "main.h"
#include "crypt.h"

static void
find_text()
{
    Elf32_Shdr* str = &exec.secs[exec.ehdr->e_shstrndx];

    int i;
    char* sh_name;
    Elf32_Shdr* sec;

    for (i = 0; i < exec.ehdr->e_shnum; i++)
    {
        sec     = &exec.secs[i];
        sh_name = (exec.mem + str->sh_offset) + sec->sh_name;

        if (strcmp(sh_name, ".text") == 0) {
            exec.text = sec;
            exec.code_size = exec.text->sh_size - input.sst.st_size - 1;
            return log(".text found");
        }
    }

    assert_fatal(0, "Couldn't find .text section.");
}

static void
print_info()
{
    log(".text        = 0x%.8x.", exec.text);
    log(".text.size   = %.2f KiB", exec.text->sh_size / 1024.0);
    log(".text.shaddr = 0x%.8x.", exec.text->sh_addr);
    log("ehdr.e_entry = 0x%.8x.", exec.ehdr->e_entry);
    log_d("crypted_size = %.2f KiB", exec.code_size / 1024.0);
}

static void
set_entry() /* From _text. */
{
    replaces[TEXT_ADDR][VAL_NEW] = (void*) exec.ehdr->e_entry;
    replaces[CRYPT_LEN][VAL_NEW] = (void*) exec.code_size;
    exec.ehdr->e_entry = exec.text->sh_addr + exec.code_size;
}

static void
set_writable()
{
    size_t i;
    Elf32_Phdr *phdrs = exec.mem + exec.ehdr->e_phoff;

    exec.text->sh_flags |= SHF_WRITE;


    for (i = 0; i < exec.ehdr->e_phnum; ++i) {
        phdrs[i].p_flags |= PF_W;
    }
}

static void
alter_text()
{
    unsigned char *text = exec.mem + exec.text->sh_offset;
    unsigned int i;

    uint8_t key = 216;

    for (i = 0; i < exec.code_size; i++) {
        text[i] ^= key;
    }

    for (i = 0; (int) i < input.sst.st_size; i++) {
        text[exec.code_size + i] = *((char*) exec.smem + i);
    }

    log("Injected code into .text.");
}

void
encrypt_input()
{
    find_text();
    set_writable();
    set_entry(); // Alters substitutions for stub preperal.
    prepare_stub();
    print_info();
    alter_text();
}
