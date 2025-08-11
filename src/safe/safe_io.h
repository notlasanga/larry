#ifndef SAFE_IO_H
#define SAFE_IO_H

#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define safe_open(pathname, flags, mode) _safe_open(pathname, flags, mode, __FILE__, __LINE__)
int _safe_open(const char *pathname, int flags, mode_t mode, const char *file, int line);

#define safe_close(fd) _safe_close(fd, __FILE__, __LINE__)
void _safe_close(int fd, const char *file, int line);

#endif // SAFE_IO_H
