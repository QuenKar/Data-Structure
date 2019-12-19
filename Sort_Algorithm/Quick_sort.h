#pragma once
#include<iostream>
using namespace std;

int partition(int a[], int low, int high)
{
	int i = low, j = high;
	int x = a[low];
	while (i < j)
	{
		while (i < j && a[j] <= x) --j;
		a[i] = a[j];
		while (i < j && a[i] >= x)++i;
		a[j] = a[i];
	}
	swap(x, a[i]);
	return i;
}

void QSort(int arr[], int l, int r) {
	if (l < r)
	{
		int pivot = partition(arr, l, r);
		if (l < pivot - 1)
			QSort(arr, l, pivot - 1);
		if (pivot + 1 < r)
			QSort(arr, pivot + 1, r);
	}
}