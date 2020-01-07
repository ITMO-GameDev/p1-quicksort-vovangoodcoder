#include "quickSort.h"

int* sort(int* arr, int size) {
    bool (*comparator_ptr)(int, int) = forwardComparator;
    sortChoice(arr, arr + size - 1, comparator_ptr);
    return arr;
}