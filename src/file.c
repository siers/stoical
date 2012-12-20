#include <sys/mman.h>
#include "file.h"

void
file_open(struct file *file, char path[])
{
    assert_fatal((file->fd = open(path, O_RDWR, 0)) != -1,
            "error opening '%s': %s", path, strerror(errno));

    assert_fatal(!fstat(file->fd, &file->st), "stat failed: %s",
            strerror(errno));

    file->mem = 0;
}

void*
file_mmap(struct file *file)
{
    file->mem = mmap(0, file->st.st_size, PROT_READ | PROT_WRITE,
            MAP_SHARED, file->fd, 0);
    assert_fatal(file->mem != MAP_FAILED, "mmap failed: %s", strerror(errno));

    return file->mem;
}

void
file_write(const struct file *file)
{
    assert_fatal(write(file->fd, file->mem, file->st.st_size) != -1,
            "write failed: %s", strerror(errno));
}

void
file_close(struct file *file)
{
    close(file->fd);
    file->fd = 0;

    if (file->mem) {
        munmap(file->mem, file->st.st_size);
    }
}
