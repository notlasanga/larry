#ifndef INPUT_STREAM_H
#define INPUT_STREAM_H

#include <stddef.h>

typedef struct {
    int fd;
    char *buffer;
    size_t bufsize;
    size_t pos;
    size_t len;
} input_stream_t;

input_stream_t *init_stream(int fd, size_t bufsize);
void free_stream(input_stream_t *in);

int peek_char(input_stream_t *in);
int next_char(input_stream_t *in);

#endif // INPUT_STREAM_H
