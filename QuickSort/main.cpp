#include <iostream>
#include "quickSort.h"

int main()
{
    int array[] = { 7, 2, 2, 2, 1, 5, 5, 5, 0 };
    int* arr = sort(array, sizeof(array) / sizeof(int));
    printArray(arr, arr + sizeof(array) / sizeof(int) - 1);
    return 0;
}