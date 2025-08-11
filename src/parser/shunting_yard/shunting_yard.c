#include <stdio.h>
#include <stdbool.h>

#include "token.h"
#include "token_list.h"
#include "ast.h"

int precedence(operator_type_t op) {
    return operators[op].precedence;
}

associativity_t get_associativity(operator_type_t op) {
    return operators[op].associativity;
}

token_list_t *shunting_yard(token_list_t *tokens) {
    token_list_t *output = init_token_list();
    token_list_t *stack = init_token_list();

    for (token_t *token = pop_token(tokens); token->type != TOKEN_END;
         token = pop_token(tokens)) {
        switch (token->type) {
            case TOKEN_INT:
            case TOKEN_FLOAT:
                append_token(output, token);
                break;
            case TOKEN_OPERATOR: {
                int prec = precedence(token->operator);
                associativity_t associativity = get_associativity(token->operator);

                // pop from stack until a lower precedence op
                while (peek_token(stack) &&
                       peek_token(stack)->type == TOKEN_OPERATOR) {
                    int stack_prec = precedence(peek_token(stack)->operator);
                    if ((associativity == RIGHT_ASSOCIATIVE && stack_prec > prec) ||
                        (associativity == LEFT_ASSOCIATIVE && stack_prec >= prec)) {
                        append_token(output, pop_token(stack));
                    } else {
                        break;
                    }
                }
                push_token(stack, token);
                break;
            }
            case TOKEN_LPAREN:
                push_token(stack, token);
                break;
            case TOKEN_RPAREN:
                // pop until matching lparen
                while (peek_token(stack) &&
                       peek_token(stack)->type != TOKEN_LPAREN) {
                    append_token(output, pop_token(stack));
                }
                if (peek_token(stack) &&
                    peek_token(stack)->type == TOKEN_LPAREN) {
                    pop_token(stack);
                }
                break;
            default:
                printf("unsupported token: %s\n", token_to_string(token));
                break;
        }
    }

    while (peek_token(stack)) {
        append_token(output, pop_token(stack));
    }

    free_token_list(tokens);
    free_token_list(stack);

    return output;
}
