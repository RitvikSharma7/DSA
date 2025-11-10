#include <stdio.h>
#include <stdlib.h>

int main(void){
    int array[100]; // declaring an array of 100 elements of integer type
    for (int i = 0; i < 100; i++){
        array[i] = 0;
    }
    for (int i = 0; i < 100; i++){
        printf("%d ", array[i]);
    }
    return 0 ;
}
