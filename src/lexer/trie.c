#include "token.h"
#include "trie.h"

#include "lexer.h"
#include "dispatch.h"
#include "safe.h"

trie_node_t *insert_trie_node(trie_node_t *root, const char *str) {
    trie_node_t *node = root;
    unsigned char *p = (unsigned char *) str;

    while (*p != '\0') {
        if (!node->children[(int) *p]) {
            node->children[(int) *p] = safe_calloc(1, sizeof(trie_node_t));
        }
        node = node->children[(int) *p];

        p++;
    }

    return node;
}

void insert_token(trie_node_t *root, const char *str, token_type_t type) {
    trie_node_t *node = insert_trie_node(root, str);

    node->payload_type = TRIE_TOKEN;
    node->token_type = type;
}

void insert_operator(trie_node_t *root, const char *str, operator_type_t op_type) {
    trie_node_t *node = insert_trie_node(root, str);

    node->payload_type = TRIE_OP;
    node->operator_type = op_type;
}

void insert_dispatch(trie_node_t *root, const char *str, token_dispatch_fn func) {
    trie_node_t *node = insert_trie_node(root, str);

    node->payload_type = TRIE_DISPATCH;
    node->dispatch_handler = func;
}

void insert_whitespace(trie_node_t *root, const char *str) {
    trie_node_t *node = insert_trie_node(root, str);

    node->payload_type = TRIE_WHITESPACE;
}

trie_node_t *init_trie() {
    trie_node_t *root = safe_calloc(1, sizeof(trie_node_t));

    // Insert all operators
    insert_operator(root, "+", OP_ADDITION);
    insert_operator(root, "-", OP_SUBTRACTION);
    insert_operator(root, "*", OP_MULTIPLICATION);
    insert_operator(root, "/", OP_DIVISION);
    insert_operator(root, "^", OP_POWER);
    // etc.

    // Mark identifier starting chars
    for (int c = 'a'; c <= 'z'; c++) {
        char buf[2] = { c, '\0' };
        insert_dispatch(root, buf, read_identifier);
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        char buf[2] = { c, '\0' };
        insert_dispatch(root, buf, read_identifier);
    }
    insert_dispatch(root, "_", read_identifier);

    // Mark starting digits for ints
    for (int c = '0'; c <= '9'; c++) {
        char buf[2] = { c, '\0' };
        insert_dispatch(root, buf, read_int);
    }

    // Mark starting digits for floats
    for (int c = '0'; c <= '9'; c++) {
        char buf[3] = { '.', c, '\0' };
        insert_dispatch(root, buf, read_float);
    }

    // tokens
    insert_token(root, "(", TOKEN_LPAREN);
    insert_token(root, ")", TOKEN_RPAREN);
    insert_token(root, ".", TOKEN_DOT);
    
    // end tokens
    char buf[2] = { EOF, '\0' };
    insert_token(root, buf, TOKEN_END);
    buf[0] = '\n';
    insert_token(root, buf, TOKEN_END);
    insert_token(root, ";", TOKEN_END);

    // whitespace tokens
    buf[0] = ' ';
    insert_whitespace(root, buf);
    buf[0] = '\t';
    insert_whitespace(root, buf);

    return root;
}

void free_trie(trie_node_t *root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < TRIE_CHILDREN_COUNT; i++) {
        free_trie(root->children[i]);
    }

    free(root);
}
