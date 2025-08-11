#include <stdio.h>
#include <math.h>

#include "token_list.h"

// only supports (+, -, *, /, ^)
token_t *evaluate_RPN(token_list_t *list) {
    token_list_t *stack = init_token_list();

    // for (token_t *token = pop_token(list); token; token = pop_token(list)) {
    token_t *token = pop_token(list);
    while (token) {
        
        switch (token->type) {
            case TOKEN_INT: {
                token->type = TOKEN_FLOAT; // store as float for uniformity
                token->float_value = (double)token->int_value;
                push_token(stack, token);
                break;
            }
            case TOKEN_FLOAT: {
                push_token(stack, token);
                break;
            }
            case TOKEN_OPERATOR: {
                token_t *b = pop_token(stack);
                token_t *a = pop_token(stack);

                if (!a || !b) {
                    fprintf(stderr, "Operator does not have two operands\n");
                    break;
                }

                double x = a->float_value;
                double y = b->float_value;

                double result;
                switch (token->operator) {
                    case OP_ADDITION: result = x + y; break;
                    case OP_SUBTRACTION: result = x - y; break;
                    case OP_MULTIPLICATION: result = x * y; break;
                    case OP_DIVISION: result = x / y; break;
                    case OP_POWER: result = pow(x, y); break;
                    default:
                        fprintf(stderr, "Unknown operator\n");
                        result = 0;
                }

                a->float_value = result;
                free_token(b);
                push_token(stack, a);
                break;
            }
            default:
                fprintf(stderr, "Unexpected token in evaluation\n");
        }
        token = pop_token(list);
    }

    token_t *result = pop_token(stack);
    free_token_list(stack);
    free_token_list(list);
    return result;
}
