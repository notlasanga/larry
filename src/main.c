#include <stdlib.h>
#include <stdio.h>

#include "run.h"

int main(int argc, char **argv) {
    if (argc > 2) {
        printf("Usage: %s [script]", argv[0]);
        return EXIT_FAILURE;
    } else if (argc == 2) {
        run_file(argv[1]);
    } else {
        run_repl();
    }

    return EXIT_SUCCESS;
}
