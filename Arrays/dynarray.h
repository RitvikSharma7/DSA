#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>

typedef struct dynarray {
void** data;
size_t elements;
size_t size;
} dynarray;

typedef void (*free_fn)(void*);

// Create a new dynamic array
dynarray* dynarray_create(void);

// Destroy the dynamic array and free all elements using fn (if it exits)
void dynarray_destroy(dynarray* a, free_fn fn);

// Append an element to the array
void dynarray_append(dynarray* a, void* item);

// Get element at index
void* dynarray_get(dynarray* a, size_t index);

// Set element at index
void dynarray_set(dynarray* a, size_t index, void* item);

// Return number of elements in array
size_t dynarray_size(dynarray* a);

#endif // DYNARRAY_H
