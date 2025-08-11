#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "token.h"

typedef struct token_node {
    token_t *token;
    struct token_node *next;
} token_node_t;

typedef struct {
    token_node_t *head;
    token_node_t *tail;
} token_list_t;

token_list_t *init_token_list(void);

void append_token(token_list_t *list, token_t *t);
void push_token(token_list_t *list, token_t *t);
token_t *peek_token(token_list_t *list);
token_t *pop_token(token_list_t *list);

void print_token_list(token_list_t *list);
void free_token_list(token_list_t *list);

#endif // TOKEN_LIST_H
