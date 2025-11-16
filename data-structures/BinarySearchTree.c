#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct treeNode{
    int data;
    struct treeNode* leftChild;
    struct treeNode* rightChild;
}treeNode;

treeNode* newNode(int value){
    treeNode* node = malloc(sizeof(treeNode));
    if (node == NULL){
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    node->data = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

treeNode* insert(treeNode* node ,int value){
    if (node == NULL){
        return newNode(value);
    } else {
        if (node->data > value){
            node->leftChild = insert(node->leftChild,value);         
        } else {
            node->rightChild = insert(node->rightChild,value);
        }
    }
    return node;
}
/*
void insert(int value){
    treeNode* node = newNode(value);
    if (root == NULL){
        root = node;
        return;
    }
    treeNode* curr = root;
    treeNode* parent = NULL;
    while (curr != NULL){
        parent = curr;
        if (value < curr->data){
            curr = curr->leftChild;
        } else {
            curr = curr->rightChild;
        }
    }
    if (value < parent->data){
        parent->leftChild = node;
    } else {
        parent->rightChild = node;
    }
}
*/

bool search(treeNode* node, int value){
    if (node == NULL){
        return false;
    } else if (node->data == value) {
        return true;
    } else if (node->data > value){
        return search(node->leftChild, value);
    } else {
        return search(node->rightChild, value);
    }
}
/*
bool search(int value){
    treeNode* curr = root;
    while(curr != NULL){
        if (curr->data == value){
            return true;
        } else if (value < curr->data) {
            curr = curr->leftChild;
        } else {
            curr = curr->rightChild;
        }
    }
    return false;
}
*/

void traversal(treeNode* node){
    if (node == NULL){
        return;
    }
    traversal(node->leftChild);
    printf("%d ", node->data);
    traversal(node->rightChild);
}

int main(void){
    treeNode* root = NULL;
    root = insert(root,15);
    root = insert(root, 13);
    root = insert(root, 16);
    int number;
    int result;
    do {
        printf("\nEnter an integer: ");
        result = scanf("%d", &number);
        if (result == 0) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); 
        }
    } while (result == 0);
    if (search(root,number)){
        printf("Value %d exists in tree.\n");
    } else {
        printf("Value %d does not exist in tree.\n");
    }
    traversal(root);
}
