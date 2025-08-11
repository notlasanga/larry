#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "input_stream.h"
#include "lexer.h"
#include "token_list.h"
#include "trie.h"
#include "shunting_yard.h"
#include "evaluator.h"

void run(input_stream_t *input, trie_node_t *trie) {
    token_list_t *tokens = tokenize(input, trie);
    // print_token_list(tokens);

    token_list_t *postfix = shunting_yard(tokens);

    // print_token_list(postfix);

    token_t *result = evaluate_RPN(postfix);

    if (result == NULL) {
        return;
    }

    char *result_str = token_to_value(result);
    printf("%s\n", result_str);
    free(result_str);

    free_token(result);
}

int run_file(char *path) {
    printf("Running file: %s\n", path);
    int fp = open(path, O_RDONLY);

    input_stream_t *input = init_stream(fp, 1024);
    trie_node_t *tree = init_trie();

    run(input, tree);

    free_stream(input);
    free_trie(tree);

    return 0;
}

int run_repl() {
    input_stream_t *input = init_stream(STDIN_FILENO, 1024);
    trie_node_t *tree = init_trie();

    while (1) {
        printf("> ");
        fflush(stdout);

        run(input, tree);
    }

    free_stream(input);
    free_trie(tree);

    return 0;
}
