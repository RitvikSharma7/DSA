#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

static Node* hashTable[TABLE_SIZE] = {NULL};

int hashFunction(char* s) {
    int index = 0;
    while (*s != '\0') {
        index += *s;
        s++;
    }
    return index % TABLE_SIZE;
}

// Add Key,Value pair to hash table with collision handling.
void add(Node* hashTable[], char *k, int v) {
    int index = hashFunction(k);

    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->key = strdup(k);
    newNode->value = v;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        Node* bucket = hashTable[index];
        while (bucket->next != NULL) {
            bucket = bucket->next;
        }
        bucket->next = newNode;
        newNode->prev = bucket;
    }
}

// Remove specified key,value pair and return value if found, else -1.
int removeKey(Node* hashTable[], char *k, int v) {
    int index = hashFunction(k);
    Node* bucket = hashTable[index];

    while (bucket != NULL) {
        if (strcmp(bucket->key, k) == 0 && bucket->value == v) {
            int found = bucket->value;

            if (bucket->prev != NULL)
                bucket->prev->next = bucket->next;
            else
                hashTable[index] = bucket->next; 

            if (bucket->next != NULL)
                bucket->next->prev = bucket->prev;

            free(bucket->key);
            free(bucket);
            return found;
        }
        bucket = bucket->next;
    }
    return -1;
}

// Check if key is in hashTable
bool contains(Node* hashTable[], char *k) {
    int index = hashFunction(k);
    Node* bucket = hashTable[index];
    while (bucket != NULL) {
        if (strcmp(bucket->key, k) == 0) {
            return true;
        }
        bucket = bucket->next;
    }
    return false;
}

int main(void) {
    add(hashTable, "Red", 1);
    add(hashTable, "Red", 2);
    add(hashTable, "Green", 2);
    add(hashTable, "Blue", 3);

    printf("Contains Red? %d\n", contains(hashTable, "Red"));
    printf("Removing Green: %d\n", removeKey(hashTable, "Green", 2));
    printf("Removing Red: %d\n", removeKey(hashTable, "Red", 2));
    printf("Contains Red? %d\n", contains(hashTable, "Red"));
    printf("Contains Green? %d\n", contains(hashTable, "Green"));

    return 0;
}
