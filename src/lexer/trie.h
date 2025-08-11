#ifndef TRIE_H
#define TRIE_H

#include "token.h"
#include "input_stream.h"

#define TRIE_CHILDREN_COUNT 256

typedef token_t *(*token_dispatch_fn)(input_stream_t *in);

typedef enum {
    TRIE_NONE,
    TRIE_TOKEN,
    TRIE_OP,
    TRIE_DISPATCH,
    TRIE_WHITESPACE,
} trie_payload_type_t;

typedef struct trie_node {
    struct trie_node *children[TRIE_CHILDREN_COUNT];
    trie_payload_type_t payload_type;
    union {
        token_type_t token_type;
        token_dispatch_fn dispatch_handler;
        operator_type_t operator_type;    // for TOKEN_CLASS_OPERATOR
    };
} trie_node_t;

trie_node_t *init_trie(void);
void free_trie(trie_node_t *root);

#endif // TRIE_H
