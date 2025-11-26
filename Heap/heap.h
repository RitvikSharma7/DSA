#ifndef HEAP_H
#define HEAP_H

/* 
 * Max-Heap implementation and Heapsort utilities.
 *
 * Public API:
 *   - buildMaxHeap: convert an array into a valid max heap
 *   - maxHeapify: fix a single subtree (used internally but exposed for completeness)
 *   - heapsort: sort array in ascending order using heapsort
 */

/*
 * maxHeapify
 * -----------------------------------
 * Ensures the subtree rooted at `index` follows the max-heap property.
 *
 * Parameters:
 *   array[] : the heap array
 *   size    : number of elements in heap
 *   index   : index to heapify from
 */
void maxHeapify(int array[], int size, int index);

/*
 * buildMaxHeap
 * -----------------------------------
 * Turns an array into a max heap by calling maxHeapify bottom-up.
 *
 * Parameters:
 *   array[] : input array
 *   size    : number of elements
 */
void buildMaxHeap(int array[], int size);

/*
 * heapsort
 * -----------------------------------
 * Sorts an array in ascending order using heap sort.
 *
 * Parameters:
 *   array[] : array to sort
 *   size    : number of elements
 */
void heapsort(int array[], int size);

#endif // HEAP_H
