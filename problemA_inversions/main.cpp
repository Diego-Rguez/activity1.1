#include <iostream>
#include <vector>
using namespace std;

long long merge_sort_count(vector<int> &A, int left, int mid, int right)
{
    long long inversiones_cruzadas = 0;
    vector<int> temporal;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (A[i] <= A[j])
        {
            temporal.push_back(A[i]);
            i++;
        }
        else
        {
            temporal.push_back(A[j]);
            j++;
            inversiones_cruzadas += (mid - i + 1);
        }
    };

    while (i <= mid)
    {
        temporal.push_back(A[i]);
        i++;
    };

    while (j <= right)
    {
        temporal.push_back(A[j]);
        j++;
    };

    for (int k = 0; k < temporal.size(); k++)
    {
        A[left + k] = temporal[k];
    };

    return inversiones_cruzadas;
};

long long contar_inversiones(vector<int> &A, int left, int right)
{
    long long inversiones = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        inversiones += contar_inversiones(A, left, mid);
        inversiones += contar_inversiones(A, mid + 1, right);
        inversiones += merge_sort_count(A, left, mid, right);
    };
    return inversiones;
};

int main()
{
    // TEST 1: Standard Case
    // Array: [8, 4, 2, 1] -> Inversions: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1)
    // Expected: 6
    vector<int> test1 = {8, 4, 2, 1};
    cout << "Test 1 (Standard Case): " << contar_inversiones(test1, 0, test1.size() - 1)
         << " | Expected: 6\n";

    // TEST 2: Already Sorted
    // Array: [1, 2, 3, 4, 5] -> No element is out of order.
    // Expected: 0
    vector<int> test2 = {1, 2, 3, 4, 5};
    cout << "Test 2 (Already Sorted): " << contar_inversiones(test2, 0, test2.size() - 1)
         << " | Expected: 0\n";

    // TEST 3: Reverse Sorted
    // Array: [5, 4, 3, 2, 1] -> Maximum possible inversions: n*(n-1)/2 = 5*4/2 = 10
    // Expected: 10
    vector<int> test3 = {5, 4, 3, 2, 1};
    cout << "Test 3 (Reverse Sorted): " << contar_inversiones(test3, 0, test3.size() - 1)
         << " | Expected: 10\n";

    // TEST 4: Duplicates
    // Array: [2, 4, 1, 3, 2] -> Inversions: (2,1), (4,1), (4,3), (4,2), (3,2)
    // Note: Equal elements (e.g., 2 and 2) do NOT count as inversions because A[i] <= A[j].
    // Expected: 5
    vector<int> test4 = {2, 4, 1, 3, 2};
    cout << "Test 4 (Duplicates): " << contar_inversiones(test4, 0, test4.size() - 1)
         << " | Expected: 5\n";

    return 0;
}
