#include <stdio.h>

#include "input_stream.h"
#include "safe.h"

input_stream_t *init_stream(int fd, size_t bufsize) {
    input_stream_t *in = safe_malloc(sizeof(input_stream_t));

    in->buffer = safe_malloc(bufsize);

    in->fd = fd;
    in->bufsize = bufsize;
    in->pos = 0;
    in->len = 0;
    return in;
}

int refill_stream(input_stream_t *in) {
    in->len = read(in->fd, in->buffer, in->bufsize);
    in->pos = 0;
    return in->len > 0;
}

int peek_char(input_stream_t *in) {
    if (in->pos >= in->len) {
        if (!refill_stream(in)) {
            return EOF;
        }
    }
    return in->buffer[in->pos];
}

int next_char(input_stream_t *in) {
    int ch = peek_char(in);
    if (ch != EOF) {
        in->pos++;
    }
    return ch;
}

void free_stream(input_stream_t *in) {
    if (in) {
        free(in->buffer);
        free(in);
    }
}
