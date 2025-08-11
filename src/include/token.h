#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    OP_ADDITION,
    OP_SUBTRACTION,
    OP_MULTIPLICATION,
    OP_DIVISION,
    OP_POWER,
} operator_type_t;

typedef enum {
    LEFT_ASSOCIATIVE,
    RIGHT_ASSOCIATIVE,
} associativity_t;

typedef struct {
    char *op;
    int precedence;
    associativity_t associativity;
} operator_info_t;

static const operator_info_t operators[] = {
    { "+", 2, LEFT_ASSOCIATIVE },
    { "-", 2, LEFT_ASSOCIATIVE },
    { "*", 3, LEFT_ASSOCIATIVE },
    { "/", 3, LEFT_ASSOCIATIVE },
    { "^", 4, RIGHT_ASSOCIATIVE },
    { 0,   0, LEFT_ASSOCIATIVE }, // sentinel
};

typedef enum {
    TOKEN_INVALID,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_OPERATOR,
    TOKEN_IDENTIFIER,
    TOKEN_DOT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
} token_type_t;

typedef struct {
    token_type_t type;
    union {
        int int_value;       // number tokens
        double float_value;  // number tokens
        operator_type_t operator;  // operator token
        char *identifier;    // variable tokens
        char invalid_char;   // invalid token
    };
} token_t;

char *token_to_string(token_t *token);
char *token_to_value(token_t *token);
void free_token(token_t *token);

#endif // TOKEN_H
