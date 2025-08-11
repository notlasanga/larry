#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "token.h"
#include "lexer.h"
#include "token_list.h"
#include "trie.h"
#include "input_stream.h"

#include "safe.h"

token_t *create_token(token_type_t type) {
    token_t *token = safe_malloc(sizeof(token_t));
    token->type = type;

    return token;
}

token_t *create_operator_token(operator_type_t op) {
    token_t *token = safe_malloc(sizeof(token_t));
    token->type = TOKEN_OPERATOR;
    token->operator = op;

    return token;
}

token_t *create_invalid_token(char c) {
    token_t *token = safe_malloc(sizeof(token_t));
    token->type = TOKEN_INVALID;
    token->invalid_char = c;

    return token;
}

token_t *next_token(input_stream_t *in, trie_node_t *root) {
    unsigned char c = peek_char(in);
    trie_node_t *node = root;
    trie_node_t *next = node->children[(int) c];

    while (next != NULL) {
        node = next;

        // skip whitespace
        if (node->payload_type == TRIE_WHITESPACE) {
            node = root;
        }

        // call dispatch
        if (node->payload_type == TRIE_DISPATCH) {
            return node->dispatch_handler(in);
        }
        
        // early exit for end tokens
        if (node->payload_type == TRIE_TOKEN && node->token_type == TOKEN_END) {
            next_char(in);
            return create_token(TOKEN_END);
        }

        // move to next char
        next_char(in);
        c = peek_char(in);
        next = node->children[(int) c];
    }

    if (node->payload_type == TRIE_TOKEN) {
        return create_token(node->token_type);
    } else if (node->payload_type == TRIE_OP) {
        return create_operator_token(node->operator_type);
    }

    next_char(in);
    return create_invalid_token(c);
}

token_list_t *tokenize(input_stream_t *input, trie_node_t *tree) {
    token_list_t *tokens = init_token_list();

    while (1) {
        token_t *token = next_token(input, tree);

        if (token == NULL) {
            fprintf(stderr, "error: lex error\n");
            exit(EXIT_FAILURE);
        }

        append_token(tokens, token);
        if (token->type == TOKEN_END) {
            break;
        }
    }

    return tokens;
}
