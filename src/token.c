#include <stdio.h>
#include <stdlib.h>

#include "safe.h"
#include "token.h"

char *token_to_value(token_t *token) {
    char *buf = safe_malloc(64);

    switch (token->type) {
        case TOKEN_INT:
            snprintf(buf, 64, "%d", token->int_value);
            break;
        case TOKEN_FLOAT:
            snprintf(buf, 64, "%g", token->float_value);
            break;
        default:
            snprintf(buf, 64, "[Not a Value]");
            break;
    }
    return buf;
}

char *token_to_string(token_t *token) {
    char *buf = safe_malloc(64);

    switch (token->type) {
        case TOKEN_INT:
            snprintf(buf, 64, "INT(%d)", token->int_value);
            break;
        case TOKEN_FLOAT:
            snprintf(buf, 64, "FLOAT(%f)", token->float_value);
            break;
        case TOKEN_OPERATOR:
            if (token->operator >= 0 ||
                token->operator <= sizeof(operators) / sizeof(operators[0])) {
                snprintf(buf, 64, "OP(%s)", operators[token->operator].op);
            } else {
                snprintf(buf, 64, "UNKNOWN_OPERATOR");
            }
            break;
        case TOKEN_DOT:
            snprintf(buf, 64, "DOT");
            break;
        case TOKEN_LPAREN:
            snprintf(buf, 64, "LPAREN");
            break;
        case TOKEN_RPAREN:
            snprintf(buf, 64, "RPAREN");
            break;
        case TOKEN_END:
            snprintf(buf, 64, "END");
            break;
        case TOKEN_INVALID:
            snprintf(buf, 64, "INVALID(%c)", token->invalid_char);
            break;
        case TOKEN_IDENTIFIER:
            snprintf(buf, 64, "IDENT(%s)", token->identifier);
            break;
        default:
            snprintf(buf, 64, "UNKNOWN_TOKEN");
            break;
    }
    return buf;
}

void free_token(token_t *token) {
    if (token->type == TOKEN_IDENTIFIER) {
        free(token->identifier);
    }
    free(token);
}
