#ifndef AST_H
#define AST_H

#include "token.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY_OP,
} ast_node_type_t;

typedef struct ast_node {
    ast_node_type_t type;
    union {
        double number;
        struct {
            struct ast_node* left;
            struct ast_node* right;
            operator_type_t op;
        } binary;
    };
} ast_node_t;

#endif // AST_H
