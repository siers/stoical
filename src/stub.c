#include "stub.h"

void* replaces[][2] = {
    {"c0febabe", (void*) 0},
    {"cccccccc", (void*) 0},
    {"eeeeeeee", (void*) 0},
    /* Add enums for every entry in main.h */
};

struct file stub;

static void
load()
{
    file_open(&stub, STUB_PATH);
    file_mmap(&stub);
}

void
stub_prepare()
{
    int i, new;
    char cmd[512] = STUB_PREPARE_SCRIPT,
         appendable[256], *old;

    for (i = 0; i < REPLACE_COUNT; i++) {
        old = (char*)    replaces[i][VAL_OLD];
        new = (uint32_t) replaces[i][VAL_NEW];
        snprintf(appendable, 512, " %s %0*x", old, strlen(old), new);
        strncat(cmd, appendable, 512);
    }

    log_d("Calling $ %s", cmd);
    assert_fatal(system(cmd) == 0, "Couldn't prepare stub.");
    load();
}

void
stub_inject(uint8_t mem[])
{
    size_t i, stub_size = stub.st.st_size;

    for (i = 0; i < stub_size; i++) {
        mem[i] = *((char*) stub.mem + i);
    }

    log("Stub injected.");
}
