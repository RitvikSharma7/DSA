#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

static const float LOAD_FACTOR = 0.75f;
static const int INITIAL_SIZE = 8;

typedef struct bucket {
    char* key;
    void* value;
} bucket;

#define TOMBSTONE ((bucket*) -1)

typedef struct dict {
    int size;
    int count;
    bucket** table;
} dict;

/* ==================== Hash Functions ==================== */

// FNV-1a 64-bit hash
uint64_t fnv_1a(const char* key) {
    uint64_t hash = 1469598103934665603ULL;
    while (*key) {
        hash ^= (unsigned char)(*key);
        hash *= 1099511628211ULL;
        key++;
    }
    return hash;
}

// Compression function: maps hash to table index (size must be power of 2)
int compression_fn(uint64_t hash, int size) {
    return (int)(hash & (size - 1));
}

/* ==================== Bucket Helpers ==================== */

bucket* create_bucket(const char* key, void* value) {
    bucket* b = malloc(sizeof(bucket));
    if (!b) {
        perror("malloc");
        return NULL;
    }
    b->key = strdup(key);
    b->value = value;
    return b;
}

/* ==================== Dictionary API ==================== */

dict* dict_create(void) {
    dict* d = malloc(sizeof(dict));
    if (!d) { perror("malloc"); return NULL; }
    d->size = INITIAL_SIZE;
    d->count = 0;
    d->table = calloc(d->size, sizeof(bucket*));
    if (!d->table) { perror("calloc"); free(d); return NULL; }
    return d;
}

void dict_free(dict* d) {
    for (int i = 0; i < d->size; i++) {
        bucket* b = d->table[i];
        if (b && b != TOMBSTONE) {
            free(b->key);
            free(b);
        }
    }
    free(d->table);
    free(d);
}

int dict_len(dict* d) {
    return d->count;
}

/* ==================== Internal Set Without Resize ==================== */

void dict_set_no_resize(dict* d, const char* key, void* value) {
    int index = compression_fn(fnv_1a(key), d->size);
    int first_tombstone = -1;

    while (d->table[index] != NULL) {
        if (d->table[index] == TOMBSTONE && first_tombstone == -1) {
            first_tombstone = index;
        } else if (d->table[index] != TOMBSTONE &&
                   strcmp(d->table[index]->key, key) == 0) {
            d->table[index]->value = value;
            return;
        }
        index = (index + 1) & (d->size - 1);
    }

    int insert_pos = (first_tombstone != -1) ? first_tombstone : index;
    d->table[insert_pos] = create_bucket(key, value);
    d->count++;
}

/* ==================== Resize ==================== */

void dict_resize(dict* d) {
    int old_size = d->size;
    bucket** old_table = d->table;

    int new_size = old_size * 2;
    bucket** new_table = calloc(new_size, sizeof(bucket*));
    if (!new_table) { perror("calloc"); return; }

    d->table = new_table;
    d->size = new_size;
    d->count = 0;

    for (int i = 0; i < old_size; i++) {
        bucket* b = old_table[i];
        if (b && b != TOMBSTONE) {
            dict_set_no_resize(d, b->key, b->value);
            free(b->key);
            free(b);
        }
    }
    free(old_table);
}

/* ==================== Set / Get / Contains / Delete ==================== */

void dict_set(dict* d, const char* key, void* value) {
    if ((float)d->count / d->size > LOAD_FACTOR) {
        dict_resize(d);
    }
    dict_set_no_resize(d, key, value);
}

void* dict_get(dict* d, const char* key) {
    int index = compression_fn(fnv_1a(key), d->size);
    int start = index;

    while (1) {
        bucket* b = d->table[index];
        if (!b) return NULL;
        if (b != TOMBSTONE && strcmp(b->key, key) == 0) return b->value;
        index = (index + 1) & (d->size - 1);
        if (index == start) return NULL;
    }
}

bool dict_contains(dict* d, const char* key) {
    return dict_get(d, key) != NULL;
}

void dict_delete(dict* d, const char* key) {
    int index = compression_fn(fnv_1a(key), d->size);
    int start = index;

    while (1) {
        bucket* b = d->table[index];
        if (!b) return;
        if (b != TOMBSTONE && strcmp(b->key, key) == 0) {
            free(b->key);
            free(b);
            d->table[index] = TOMBSTONE;
            d->count--;
            return;
        }
        index = (index + 1) & (d->size - 1);
        if (index == start) return;
    }
}


