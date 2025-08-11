#include "safe_io.h"
#include "fail.h"

int _safe_open(const char *pathname, int flags, mode_t mode, const char *file, int line) {
    int fd = open(pathname, flags, mode);
    if (fd == -1) {
        fail("open()", strerror(errno), file, line);
    }
    return fd;
}

void _safe_close(int fd, const char *file, int line) {
    if (close(fd) == -1) {
        fail("close", strerror(errno), file, line);
    }
}
