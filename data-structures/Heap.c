#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef Node{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* buildNode(int v){
    Node* node = malloc(sizeof(Node));
    node->value = v;
    node->left = NULL;
    node->right = NULL;
    return node;

}

void heapify(int a[], int i, int size){
    while(i < size){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int index = i;

        if (left <= size -1 && a[i] < a[left]){
            index = left;
        }

        if (right <= size -1 && a[index] < a[right]){
            index = right;
        }

        if (index == i){
            break;
        }

        int temp = a[i];
        a[i] = a[index];
        a[index] = temp;
        i = index;
    }
}   

void buildHeap(int a[], int size) {
    for (int i = size/2 - 1; i >= 0; i--) {
        heapify(a, i, size);
    }
}

void heapSort(int a[], int size) {
    buildHeap(a, size);

    while (size > 1) {
        int temp = a[0];
        a[0] = a[size - 1];
        a[size - 1] = temp;

        printf("%d ", a[size - 1]);

        size -= 1;
        heapify(a, 0, size); 
    }
}


Node* buildHeap(int a[], int i, int size) {
    if (i >= size) return NULL;

    Node* root = buildNode(a[i]);

    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < size) {
        root->left = buildHeap(a, leftChild, size);
    }

    if (rightChild < size) {
        root->right = buildHeap(a, rightChild, size);
    }

    return root;
}
