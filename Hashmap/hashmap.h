#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct dict dict;

/**
 * @brief Creates a new dictionary.
 *
 * @return Pointer to an empty dictionary.
 */
dict* dict_create(void);

/**
 * @brief Frees all memory associated with a dictionary.
 *
 * @param d Pointer to the dictionary to free.
 */
void dict_free(dict* d);

/**
 * @brief Inserts or updates a key-value pair in the dictionary.
 *
 * @param d     Dictionary pointer.
 * @param key   Null-terminated string key.
 * @param value Pointer to the value associated with the key.
 */
void dict_set(dict* d, const char* key, void* value);

/**
 * @brief Retrieves the value for a given key.
 *
 * @param d   Dictionary pointer.
 * @param key Key to look up.
 * @return Pointer to the value, or NULL if key does not exist.
 */
void* dict_get(dict* d, const char* key);

/**
 * @brief Checks if a key exists in the dictionary.
 *
 * @param d   Dictionary pointer.
 * @param key Key to check.
 * @return true if key exists, false otherwise.
 */
bool dict_contains(dict* d, const char* key);

/**
 * @brief Deletes a key-value pair from the dictionary.
 *
 * @param d   Dictionary pointer.
 * @param key Key to delete.
 */
void dict_delete(dict* d, const char* key);

/**
 * @brief Returns the number of items currently stored in the dictionary.
 *
 * @param d Dictionary pointer.
 * @return Number of items.
 */
int dict_len(dict* d);

#endif // HASHMAP_H

