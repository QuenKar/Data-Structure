#include <bits/stdc++.h>
using namespace std;

int a[100010];

void qsort(int a[], int left, int right)
{
    int mid = a[(left + right) / 2];
    int i = left, j = right;
    do
    {
        while (a[i] < mid)
            i++;
        while (a[j] > mid)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j)
        qsort(a, left, j);
    if (i < right)
        qsort(a, i, right);
}
