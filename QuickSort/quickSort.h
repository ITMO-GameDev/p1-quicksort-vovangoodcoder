#ifndef H_QUICKSORT
#define H_QUICKSORT

#include <iostream>
#include <memory>

using namespace std;

const int INSERT_SORT_VALUE = 20;


template<typename T>
T mediana(T* first, T* second, T* third)
{
    if (*first <= *second)
    {
        if (*third >= *second)
            return *second;
        else if (*third >= *first)
            return *third;
        else
            return *first;
    }
    else
    {
        if (*second >= *third)
            return *second;
        else if (*third <= *first)
            return *third;
        else
            return *first;
    }
}


template <typename T>
T getPivot(T* first, T* last)
{
    T* middleElementIndex;
    middleElementIndex = first + ((last - first) / 2);
    return mediana(first, middleElementIndex, last);
}


template<typename T, typename ComparatorFunc>
int hoarePartition(T* first, T* last, ComparatorFunc comparator)
{
    int i = -1;
    int j = last - first + 1;
    T pivot = getPivot(first, last);

    while (true) {
        do { i++; } while (comparator(first[i], pivot));

        do { j--; } while (comparator(pivot, first[j]));

        if (i >= j)
            return j;
        std::swap(first[i], first[j]);
    }
}


template<typename T, typename ComparatorFunc>
void sortChoice(T* first, T* last, ComparatorFunc comparator);


template<typename T, typename ComparatorFunc>
void quickSort(T* first, T* last, ComparatorFunc comparator)
{
    while (last > first)
    {
        int pivot = hoarePartition(first, last, comparator);

        if (&first[pivot] - first < last - &first[pivot])
        {
            sortChoice(first, &first[pivot], comparator);
            first = &first[pivot + 1];
        }
        else
        {
            sortChoice(&first[pivot + 1], last, comparator);
            last = &first[pivot];
        }
    }
}


template<typename T, typename ComparatorFunc>
void insertionSort(T* first, T* last, ComparatorFunc comparator)
{
    T tmp;
    int previousElementIndex;

    for (int cnt = 1; cnt < last - first + 1; cnt++)
    {
        tmp = first[cnt];
        previousElementIndex = cnt - 1;
        while (previousElementIndex >= 0 && comparator(tmp, first[previousElementIndex]))
        {
            first[previousElementIndex + 1] = first[previousElementIndex];
            first[previousElementIndex] = tmp;
            previousElementIndex--;
        }
    }
}


template<typename T, typename ComparatorFunc>
void sortChoice(T* first, T* last, ComparatorFunc comparator)
{
    if (last - first < INSERT_SORT_VALUE)
        insertionSort(first, last, comparator);
    else
        quickSort(first, last, comparator);
}


template <typename T>
bool comp(T a, T b)
{
    return a < b;
}


template <typename T>
void printArray(const T* first, const T* last)
{
    for (int i = 0; first + i <= last; i++)
        std::cout << *(first + i) << " ";
    std::cout << "\n";
}

template <typename T>
T* sort(T* arr, int size)
{
    bool (*comparator_ptr)(T, T) = comp;
    sortChoice(arr, arr + size - 1, comparator_ptr);
    return arr;
}

#endif
