#include <getopt.h>
#include <fcntl.h>
#include "main.h"
#include "crypt.h"

int loglvl = (uint16_t) -1;

void* replaces[][2] = {
    {"c0febabe", (void*) 0},
    {"cccc",     (void*) 0},
    /* Add enums for every entry in main.h */
};

static void
initialize(char* path)
{
    assert_fatal((input.fd = open(path, O_RDWR, 0)) != -1,
            "error opening '%s': %s", path, strerror(errno));

    assert_fatal((input.sfd = open(DUMMY_STUB_PATH, O_RDWR, 0)) != -1,
            "error opening '%s': %s", DUMMY_STUB_PATH, strerror(errno));

    assert_fatal(!fstat(input.fd, &input.st) &&
            !fstat(input.sfd, &input.sst),
            "stat failed: %s", strerror(errno));

    close(input.sfd); // We don't need the dummy for size anymore.

    log("Initialization went fine.");
}

static void
parse()
{
    exec.mem = mmap(0, input.st.st_size, PROT_READ | PROT_WRITE,
            MAP_SHARED, input.fd, 0);
    assert_fatal(exec.mem != MAP_FAILED, "mmap failed: %s", strerror(errno));

    exec.ehdr = exec.mem;
    assert_fatal(exec.ehdr->e_type == ET_EXEC,
            "input file must be an executable");

    exec.secs = exec.mem + exec.ehdr->e_shoff;
}

void
prepare_stub()
{
    int i, new;
    char cmd[512] = "src/prepare_stub.rb",
         appendable[256], *old;

    for (i = 0; i < REPLACE_COUNT; i++) {
        old = (char*)    replaces[i][VAL_OLD];
        new = (uint32_t) replaces[i][VAL_NEW];
        snprintf(appendable, 512, " %s %0*x", old, strlen(old), new);
        strncat(cmd, appendable, 512);
    }

    log_d("Calling $ %s", cmd);
    assert_fatal(system(cmd) == 0, "Couldn't prepare stub.");

    assert_fatal((input.sfd = open(STUB_PATH, O_RDWR, 0)) != -1,
            "error opening '%s': %s", STUB_PATH, strerror(errno));

    exec.smem = mmap(0, input.sst.st_size, PROT_READ, MAP_PRIVATE, input.sfd, 0);
    assert_fatal(exec.smem != MAP_FAILED,
            "mmap on stub failed: %s", strerror(errno));
}

static void
fin()
{
    assert_fatal(write(input.fd, exec.mem, input.st.st_size) != -1,
            "write failed: %s", strerror(errno));
    munmap(exec.mem, input.st.st_size);
    assert_fatal(!close(input.fd), "close failed: %s", strerror(errno));

    close(input.fd);
    close(input.sfd);

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

    parse();
    encrypt_input();
    fin();
    return 0;
}
