#include <string.h>
#include <errno.h>

#include "safe_memory.h"
#include "fail.h"

void *_safe_malloc(size_t size, const char *file, int line) {
    void *p = malloc(size);
    if (!p) fail("malloc", strerror(errno), file, line);
    return p;
}

void *_safe_calloc(size_t nmemb, size_t size, const char *file, int line) {
    void *p = calloc(nmemb, size);
    if (!p) fail("calloc", strerror(errno), file, line);
    return p;
}

void *_safe_realloc(void *ptr, size_t size, const char *file, int line) {
    void *p = realloc(ptr, size);
    if (!p) fail("realloc", strerror(errno), file, line);
    return p;
}
