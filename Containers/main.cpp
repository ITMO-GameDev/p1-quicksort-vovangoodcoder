#include <iostream>
#include <iterator>
#include "array.h"

using namespace std;

int main()
{
    Array<int> a;
    int i;
    for (i = 0; i < 10; i++)
        a.insert(i);

    for (i = 0; i < a.getSize(); ++i)
        a[i] *= 2;

   
    for(auto it = a.iterator(); it.hasNext(); it.next())
        std::cout << it.get() << std::endl;
}