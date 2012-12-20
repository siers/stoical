#include <getopt.h>
#include "main.h"

int loglvl = (uint16_t) -1;

static void
initialize(char path[])
{
    file_open(&elf,  path);
    file_open(&stub, DUMMY_STUB_PATH);
    file_close(&stub); // We don't need the dummy for size anymore.

    log("Initialization went fine.");
}

static void
fin()
{
    file_write(&elf);
    file_close(&elf);
    file_close(&stub);

    log("Success.");
}

char*
usage()
{
    return "usage: ./stoical [options] <filename>";
}

int
main(int argc, char** argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1) {
        switch (opt) {
        }
    }

    assert_fatal(optind < argc, usage());
    // do { } while (++optind < argc);

    initialize(argv[optind]);
    elf_parse();
    elf_prepare();
    stub_prepare();
    elf_crypt();
    fin();
    return 0;
}
