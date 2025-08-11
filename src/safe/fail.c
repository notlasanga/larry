#include "fail.h"

noreturn void fail(const char *func, const char *msg, const char *file,
                   int line) {
    fprintf(stderr,
            "\033[1;31merror\033[0m: \033[1;37m%s\033[0m failed (%s)\n --> "
            "\033[1;36m%s\033[0m:\033[1;33m%d\033[0m\n",
            func, msg, file, line);
    exit(EXIT_FAILURE);
}
