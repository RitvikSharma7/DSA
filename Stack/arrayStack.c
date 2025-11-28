#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define DEFAULT_SIZE 5

typedef struct stack {
    int* data;
    size_t num_elements;
    size_t capacity;
} stack;

stack* stack_init() {
    stack* s = calloc(1, sizeof(stack));
    if (!s) exit(EXIT_FAILURE);

    s->num_elements = 0;
    s->capacity = DEFAULT_SIZE;
    s->data = calloc(s->capacity, sizeof(int));
    if (!s->data) {
        free(s);
        exit(EXIT_FAILURE);
    }
    return s;
}

void free_stack(stack* s) {
    if (!s) return;
    free(s->data);
    free(s);
}

void stack_resize(stack* s) {
    if (!s) {
        fprintf(stderr, "Stack does not exist.\n");
        exit(EXIT_FAILURE);
    }

    size_t new_capacity = s->capacity * 2;
    int* temp = realloc(s->data, new_capacity * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Failed to resize stack.\n");
        exit(EXIT_FAILURE);
    }

    s->data = temp;
    s->capacity = new_capacity;
}

void push(stack* s, int value) {
    if (!s) {
        fprintf(stderr, "Stack does not exist.\n");
        exit(EXIT_FAILURE);
    }

    if (s->num_elements == s->capacity) {
        stack_resize(s);
    }

    s->data[s->num_elements++] = value;
}

int pop(stack* s) {
    if (!s || s->num_elements == 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }

    s->num_elements--;
    return s->data[s->num_elements];
}

int peek(stack* s) {
    if (!s || s->num_elements == 0) {
        fprintf(stderr, "Stack underflow or does not exist!\n");
        exit(EXIT_FAILURE);
    }

    return s->data[s->num_elements - 1];
}
