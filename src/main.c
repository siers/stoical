#include <getopt.h>
#include <fcntl.h>
#include "main.h"
#include "log.h"
#include "crypt.h"

int loglvl = (uint16_t) -1;

static void
initialize(char* path)
{
    assert_fatal((input.fd = open(path, O_RDWR, 0)) != -1,
            "error opening %s: %s", optarg, strerror(errno));

    assert_fatal(!fstat(input.fd, &input.st),
            "stat failed: %s", strerror(errno));

    log("Initialization went fine.");
}

static void
fin()
{
    assert_fatal(!close(input.fd), "close failed: %s", strerror(errno));
}

int
main(int argc, char** argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "i:")) != -1) {
        switch (opt) {
            case 'i':
                initialize(optarg);
                break;
        }
    }

    crypt();
    fin();
    return 0;
}
