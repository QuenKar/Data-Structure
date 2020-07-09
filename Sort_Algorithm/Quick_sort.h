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

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    qsort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            cout << ' ';
        cout << a[i];
    }
    return 0;
}
