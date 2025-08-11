#ifndef FAIL_H
#define FAIL_H

#include <stdnoreturn.h>
#include <stdio.h>
#include <stdlib.h>

noreturn void fail(const char *func, const char *msg, const char *file, int line);

#endif // FAIL_H
