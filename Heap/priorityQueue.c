#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define MIN_SIZE 5

typedef struct priorityQueue{
    node* queue;
    int elements;
    int capacity;
} priorityQueue;

priorityQueue* initQueue(int size) {
    if (size <= 0) size = MIN_SIZE;

    priorityQueue* q = malloc(sizeof(priorityQueue));
    if (!q) {
        fprintf(stderr, "Error initializing queue.\n");
        exit(EXIT_FAILURE);
    }

    q->queue = malloc(sizeof(node) * size);
    if (!q->queue) {
        fprintf(stderr, "Error allocating nodes.\n");
        free(q);
        exit(EXIT_FAILURE);
    }

    q->elements = 0;
    q->capacity = size;

    return q;
}

void destructQueue(priorityQueue* q) {
    if (!q) return;

    free(q->queue);
    free(q);
}

bool isEmpty(priorityQueue* q){
    if(!q){
        fprintf(stdout, "Queue does not exist.");
        return true;
    }
    return (q->elements == 0);
}

int size(priorityQueue* q){
    if(!q){
        fprintf(stdout, "Queue does not exist.");
        return -1;
    }
    return q->elements;
}

int capacity(priorityQueue* q){
    if(!q){
        fprintf(stdout, "Queue does not exist.");
        return -1;
    }
    return q->capacity;
}

void add(priorityQueue* q, int k, int v) {
    if (!q) return;

    if (q->elements == q->capacity) {
        resize(q);
    }

    node newNode = { k, v };
    q->queue[q->elements] = newNode;  
    q->elements++;

    // bubble-up 
    int i = q->elements - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (q->queue[i].key > q->queue[parent].key) {
            node temp = q->queue[i];
            q->queue[i] = q->queue[parent];
            q->queue[parent] = temp;
            i = parent;
        } else break;
    }
}

node extractMax(priorityQueue* q) {
    if (q->elements == 0) {
        fprintf(stderr, "Heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    node max = q->queue[0];
    q->queue[0] = q->queue[q->elements - 1];
    q->elements--;
    maxHeapify(q->queue, q->elements, 0);

    return max;
}

