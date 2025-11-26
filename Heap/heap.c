#include <stdio.h>
#include <stdlib.h>

void maxHeapify(int array[], int size, int index){
    while(index < size){
        int largest = index;
        int leftChild = 2*index + 1;
        int rightChild = 2*index + 2;

        if (leftChild <= (size - 1) && array[largest] < array[leftChild]){
            largest = leftChild;
            
        }

        if (rightChild <= (size -1) && array[largest] < array[rightChild]){
            largest = rightChild;
        }
        if (largest != index){
            int temp = array[largest];
            array[largest] = array[index];
            array[index] = temp;
        } else {
            break;
        }
        index = largest;
    }
}

void buildMaxHeap(int array[], int size){
    for (int i = (size/2) - 1; i >= 0; i--){
        maxHeapify(array, size, i);
    }
} 

void heapsort(int array[], int size){
    int len = size;
    buildMaxHeap(array,size);
    while (len > 1){
        int temp = array[0];
        array[0] = array[len - 1];
        array[len - 1] = temp;
        len--;
        maxHeapify(array, len, 0);
    }

}

int main(void){
    int array[] = {10,1,18,9,20,55,3};
     for (int i = 0; i < 7; i++){
        printf("%d ", array[i]);
    }
    puts("\n------Heapifying Array-------");
    buildMaxHeap(array, 7);
    for (int i = 0; i < 7; i++){
        printf("%d ", array[i]);
    }
     puts("\n------Sorting Array-------");
    heapsort(array, 7);
    for (int i = 0; i < 7; i++){
        printf("%d ", array[i]);
    }
    return EXIT_SUCCESS;
}