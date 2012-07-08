#include <libelf.h>
#include <getopt.h>
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

static void
initialize()
{
    input  = STDIN_FILENO;
    output = STDOUT_FILENO;
    assert_fatal(elf_version(EV_CURRENT) != EV_NONE, "unable to initialize libelf");
}

static int
fin()
{
    return close(input) && close(output);
}

int
main(int argc, char** argv)
{
    int opt;
    int *target;

    initialize();

    while ((opt = getopt(argc, argv, "o::i::")) != -1) {
        switch (opt) {
            case 'o':
            case 'i':
                target = (opt == 'o') ? &output  : &input;
                opt    = (opt == 'o') ? O_WRONLY : (O_RDONLY | !O_CREAT);
                assert_fatal((*target = open(optarg, opt, 0)) != -1,
                        "error opening %s: %s", optarg, strerror(errno));
                break;
        }
    }

    crypt();
    return fin();
}
