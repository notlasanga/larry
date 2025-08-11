#ifndef LEXER_H
#define LEXER_H

#include "token_list.h"
#include "input_stream.h"
#include "trie.h"

token_list_t *tokenize(input_stream_t *input, trie_node_t *tree);

void free_token_list(token_list_t *list);

void print_token_list(token_list_t *list);

#endif // LEXER_H
