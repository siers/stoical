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
int input;

int loglvl = (uint16_t) -1;

static void
initialize()
{
    assert_fatal(elf_version(EV_CURRENT) != EV_NONE, "unable to initialize libelf");
}

static int
fin()
{
    return close(input);
}

int
main(int argc, char** argv)
{
    int opt;

    initialize();

    while ((opt = getopt(argc, argv, "i:")) != -1) {
        switch (opt) {
            case 'i':
                assert_fatal((input = open(optarg, O_RDWR | O_APPEND, 0)) != -1,
                        "error opening %s: %s", optarg, strerror(errno));
                break;
        }
    }

    crypt();
    return fin();
}
