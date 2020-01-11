#include "pch.h"
#include "../Containers/array.h"

using namespace std;

int* toArray(Array<int> a) {
    int const size = a.getSize();
    int* arr;
    arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = a[i];
    return arr;
}

TEST(ContainersTest, Test) {
    Array<int> a;

    a.insert(200);
    a.insert(100);
    int arr[] = { 200, 100 };
    int* toArr = toArray(a);
    EXPECT_TRUE(0 == std::memcmp(arr, toArr, sizeof(arr)));
    delete toArr;

    a.remove(100);
    int arr1[] = {200};
    toArr = toArray(a);
    EXPECT_TRUE(0 == std::memcmp(arr1, toArr, sizeof(arr1)));
    delete toArr;

    int i;
    for (i = 0; i < 10; i++)
        a.insert(i);

    for (i = 0; i < a.getSize(); ++i)
        a[i] *= 2;

    int arr2[] = {400, 0, 2, 4, 6, 8, 10, 12, 14, 16};
    toArr = toArray(a);
	EXPECT_TRUE(0 == std::memcmp(arr2, toArr , sizeof(arr2)));
    delete toArr;

    a[1] = 100;
    int arr3[] = {400, 100, 2, 4, 6, 8, 10, 12, 14, 16 };
    toArr = toArray(a);
    EXPECT_TRUE(0 == std::memcmp(arr3, toArr, sizeof(arr3)));
    delete toArr;
}