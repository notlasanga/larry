#include <ctype.h>

#include "token.h"
#include "trie.h"

#include "safe.h"

token_t *read_identifier(input_stream_t *in) {
    token_t *token = safe_malloc(sizeof(token_t));

    token->type = TOKEN_IDENTIFIER;
    size_t capacity = 16;
    size_t length = 0;
    char *buffer = safe_malloc(capacity);

    while (isalnum(peek_char(in)) || peek_char(in) == '_') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = safe_realloc(buffer, capacity);
            buffer = new_buffer;
        }

        buffer[length++] = next_char(in);
    }

    buffer[length] = '\0';
    token->identifier = buffer;

    return token;
}

token_t *read_int(input_stream_t *in) {
    token_t *token = safe_malloc(sizeof(token_t));

    token->type = TOKEN_INT;
    token->int_value = 0;

    while (isdigit(peek_char(in))) {
        char c = next_char(in);
        token->int_value = token->int_value * 10 + (c - '0');
    }

    // check if is followed by fractional
    if (peek_char(in) == '.') {
        next_char(in);
        int int_value = token->int_value;

        int place = 1;
        while (isdigit(peek_char(in))) {
            char c = next_char(in);
            float curr_val = c - '0';
            for (int i = 0; i < place; i++) {
                curr_val /= 10;
            }
            token->float_value += curr_val;
            place++;
        }
        token->type = TOKEN_FLOAT;
        token->float_value += int_value;
    }

    return token;
}

// only reads part after decimal point
token_t *read_float(input_stream_t *in) {
    token_t *token = safe_malloc(sizeof(token_t));

    token->type = TOKEN_FLOAT;
    token->float_value = 0;

    int place = 1;
    while (isdigit(peek_char(in))) {
        char c = next_char(in);
        float curr_val = c - '0';
        for (int i = 0; i < place; i++) {
            curr_val /= 10;
        }
        token->float_value += curr_val;
        place++;
    }

    return token;
}
