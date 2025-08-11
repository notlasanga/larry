#include <string.h>
#include <errno.h>

#include "safe_threads.h"
#include "fail.h"

void _safe_pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg, const char *file, int line) {
    int err = pthread_create(thread, attr, start_routine, arg);
    if (err != 0) fail("pthread_create", strerror(err), file, line);
}

void _safe_pthread_join(pthread_t thread, void **retval, const char *file, int line) {
    int err = pthread_join(thread, retval);
    if (err != 0) fail("pthread_join", strerror(err), file, line);
}
