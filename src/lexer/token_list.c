#include <stdlib.h>

#include "token.h"
#include "token_list.h"

#include "safe.h"

token_list_t *init_token_list(void) {
    token_list_t *list = safe_malloc(sizeof(token_list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append_token(token_list_t *list, token_t *t) {
    token_node_t *node = safe_malloc(sizeof(token_node_t));

    node->token = t;
    node->next = NULL;

    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
}

void push_token(token_list_t *list, token_t *t) {
    token_node_t *node = safe_malloc(sizeof(token_node_t));

    node->token = t;

    if (list->head) {
        node->next = list->head;
    } else {
        node->next = NULL;
        list->tail = node;
    }

    list->head = node;
}

token_t *peek_token(token_list_t *list) {
    if (list->head == NULL) {
        return NULL;
    }
    return list->head->token;
}


token_t *pop_token(token_list_t *list) {
    if (list->head == NULL) {
        return NULL;
    }

    token_node_t *node = list->head;
    
    list->head = list->head->next;

    token_t *token = node->token;
    free(node);

    return token;
}

void free_token_list(token_list_t *list) {
    while (list->head) {
        token_node_t *temp = list->head->next;
        free_token(list->head->token);
        free(list->head);
        list->head = temp;
    }
    free(list);
}


void print_token_list(token_list_t *list) {
    token_node_t *current = list->head;
    int first = 1;
    printf("[");
    while (current) {
        if (first) {
            first = 0;
        } else {
            printf(", ");
        }

        char *str = token_to_string(current->token);
        printf("%s", str);
        free(str);

        current = current->next;
    }
    printf("]\n");
}
