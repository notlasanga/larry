#ifndef DISPATCH_H
#define DISPATCH_H

#include "token.h"
#include "input_stream.h"

token_t *read_identifier(input_stream_t *in);

token_t *read_int(input_stream_t *in);

token_t *read_float(input_stream_t *in);

#endif // DISPATCH_H
