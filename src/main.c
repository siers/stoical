#include <libelf.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include "main.h"
#include "log.h"
#include "crypt.h"

/* I/O executable paths. */
int output, input;

int loglvl = (uint16_t) -1;

static int
initialize()
{
    input = STDIN_FILENO;
    input = STDOUT_FILENO;
    assert_fatal(elf_version(EV_CURRENT) != EV_NONE, "unable to initialize libelf");
}

static int
fin()
{
    close(input);
    close(output);
}

int
main(int argc, char** argv)
{
    int opt;
    int *target;

    while ((opt = getopt(argc, argv, "o::i::")) != -1) {
        switch (opt) {
            case 'o':
            case 'i':
                target = (opt == 'o') ? &output : &input;
                opt    = (opt == 'o') ? O_WRONLY : O_RDONLY;
                assert_fatal((*target = open(optarg, opt, 0) != 1),
                        "error opening %s", optarg);
                break;
        }
    }

    return crypt();
}
