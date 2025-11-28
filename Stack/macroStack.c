#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_STACK(TYPE, NAME) \
typedef struct { \
    TYPE* data; \
    size_t num_elements; \
    size_t capacity; \
} NAME##Stack; \
\
NAME##Stack* NAME##_stack_init(size_t initial_capacity) { \
    NAME##Stack* s = calloc(1, sizeof(NAME##Stack)); \
    if (!s) { fprintf(stderr, "Allocation failed\n"); exit(EXIT_FAILURE); } \
    s->num_elements = 0; \
    s->capacity = initial_capacity > 0 ? initial_capacity : 4; \
    s->data = calloc(s->capacity, sizeof(TYPE)); \
    if (!s->data) { free(s); fprintf(stderr, "Allocation failed\n"); exit(EXIT_FAILURE); } \
    return s; \
} \
\
void NAME##_stack_free(NAME##Stack* s) { \
    if (!s) return; \
    free(s->data); \
    free(s); \
} \
\
bool NAME##_is_empty(NAME##Stack* s) { \
    return s->num_elements == 0; \
} \
\
size_t NAME##_size(NAME##Stack* s) { \
    return s->num_elements; \
} \
\
void NAME##_stack_resize(NAME##Stack* s) { \
    size_t new_capacity = s->capacity * 2; \
    TYPE* temp = realloc(s->data, new_capacity * sizeof(TYPE)); \
    if (!temp) { fprintf(stderr, "Resize failed\n"); exit(EXIT_FAILURE); } \
    s->data = temp; \
    s->capacity = new_capacity; \
} \
\
void NAME##_push(NAME##Stack* s, TYPE value) { \
    if (s->num_elements == s->capacity) NAME##_stack_resize(s); \
    s->data[s->num_elements++] = value; \
} \
\
TYPE NAME##_pop(NAME##Stack* s) { \
    if (s->num_elements == 0) { fprintf(stderr, "Stack underflow!\n"); exit(EXIT_FAILURE); } \
    return s->data[--s->num_elements]; \
} \
\
TYPE NAME##_peek(NAME##Stack* s) { \
    if (s->num_elements == 0) { fprintf(stderr, "Stack underflow!\n"); exit(EXIT_FAILURE); } \
    return s->data[s->num_elements - 1]; \
}
