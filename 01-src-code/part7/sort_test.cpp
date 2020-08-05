#include <iostream>
#include "sort.hpp"
#include <vector>
#include <string>
#include "../lib/uniform_random.h"

using namespace std;
using namespace DS;

void checkSort(const vector<string> &a, const string& msg)
{
    for (std::size_t i = 0; i < a.size(); ++i)
        if (a[i].length() != i)
            cout << msg << " error at " << i << endl;
    cout << "Finished checksort " << msg << endl;
}


template<typename AnyType>
void permute(vector<AnyType> &a)
{
    static UniformRandom r;

    for (std::size_t j = 1; j < a.size(); ++j)
        swap(a[j], a[r.nextInt(0, j)]);
}


int main()
{
    const int NUM_ITEMS = 1000;

    vector<string> a(NUM_ITEMS);        // This input adds factor of N to running time
    for (std::size_t i = 1; i < a.size(); ++i)  // but we want to test std::move logic
        a[i] = a[i - 1] + 'a';

    for (int theSeed = 0; theSeed < 10; ++theSeed)
    {
        cout << "epoch " << theSeed << endl;
        permute(a);
        insertionSort(a);
        checkSort(a, "insertionSort(a)");

        permute(a);
        insertionSort(begin(a), end(a));
        checkSort(a, "insertionSort(begin(a), end(a))");

        permute(a);
        heapSort(a);
        checkSort(a, "heapSort(a)");

        permute(a);
        shellSort(a);
        checkSort(a, "shellSort(a)");

        permute(a);
        mergeSort(a);
        checkSort(a, "mergeSort(a)");

        permute(a);
        quickSort(a);
        checkSort(a, "quickSort(a)");

        permute(a);
        SORT(a);
        checkSort(a, "SORT(a)");

        permute(a);
        quickSelect(a, NUM_ITEMS / 2);
        cout << a[NUM_ITEMS / 2 - 1].length() << " " << NUM_ITEMS / 2 << endl;
        cout << "========" << endl;
    }

    cout << "Checking SORT, Fig 7.13" << endl;
    int N = NUM_ITEMS * NUM_ITEMS;
    vector<int> b(N);
    for (int i = 0; i < N; ++i)
        b[i] = i;
    permute(b);
    SORT(b);
    for (int i = 0; i < N; ++i)
        if (b[i] != i)
            cout << "OOPS!!" << endl;

    return 0;
}