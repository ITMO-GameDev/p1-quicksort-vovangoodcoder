#include "pch.h"
#include "../QuickSort/quickSort.cpp"

using namespace std;

TEST(QuickSortTest, positiveValues) 
{
    int size = 7;
    int arr1[] = { 2, 3, 2, 1, 6, 6, 6 };
    int arr2[] = { 1, 2, 2, 3, 6, 6, 6 };
    EXPECT_TRUE(0 == std::memcmp(sort(arr1, size), arr2, sizeof(arr1)));
    
    size = 6;
    int arr3[] = { 2, 3, 2, 1, 6, 6 };
    int arr4[] = { 1, 2, 2, 3, 6, 6 };
    EXPECT_TRUE(0 == std::memcmp(sort(arr3, size), arr4, sizeof(arr3)));
    
    size = 2;
    int arr5[] = {0, 0};
    int arr6[] = {0, 0};
    EXPECT_TRUE(0 == std::memcmp(sort(arr5, size), arr6, sizeof(arr5)));

    size = 3;
    int arr7[] = {1,0,9};
    int arr8[] = {0,1,9};
    EXPECT_TRUE(0 == std::memcmp(sort(arr7, size), arr8, sizeof(arr7)));

    size = 1;
    int arr9[] = {5};
    int arr10[] = {5};
    EXPECT_TRUE(0 == std::memcmp(sort(arr9, size), arr10, sizeof(arr9)));
}