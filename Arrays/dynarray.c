#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static const size_t INIT_SIZE = 8;

typedef struct dynarray {
    void** data;
    size_t elements;
    size_t size;
} dynarray;

dynarray* dynarray_create() {
    dynarray* a = malloc(sizeof(dynarray));
    if (!a) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    a->elements = 0;
    a->size = INIT_SIZE;

    a->data = malloc(sizeof(void*) * a->size);
    if (!a->data) {
        free(a);
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    return a;
}

void dynarray_free(dynarray* a) {
    if (!a) return;

    /* does NOT free individual elements */
    free(a->data);
    free(a);
}

typedef void (*free_fn)(void*);

void dynarray_destroy(dynarray* a, free_fn fn) {
    if (!a) return;

    if (fn) {
        for (size_t i = 0; i < a->elements; i++) {
            fn(a->data[i]);     // free element
        }
    }

    free(a->data);
    free(a);
}

void resize_dynarr(dynarray* a) {
    size_t new_size = a->size * 2;

    void** new_data = realloc(a->data, sizeof(void*) * new_size);
    if (!new_data) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    a->data = new_data;
    a->size = new_size;
}

void dynarray_append(dynarray* a, void* item) {
    if (a->elements == a->size) {
        resize_dynarr(a);
    }

    a->data[a->elements] = item;
    a->elements++;
}

void* dynarray_get(dynarray* a, size_t index) {
    if (index >= a->elements) {
        return NULL;
    }

    return a->data[index];
}

void dynarray_set(dynarray* a, size_t index, void* item) {
    if (index >= a->elements) {
        return;
    }

    a->data[index] = item;
}

size_t dynarray_size(dynarray* a) {
    return a->elements;
}
                                             