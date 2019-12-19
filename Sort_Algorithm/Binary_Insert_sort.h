#pragma once
#include<iostream>
using namespace std;

void binary_Insert_sort(int* a, int len)
{
	int low, high, mid;
	for (int i = 1; i < len; i++)
	{
		int tmp = a[i];
		low = 0; high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (a[mid] < tmp)
				high = mid - 1;
			else
				low = mid + 1;
		}
		int j = i - 1;
		for (; j >= high + 1; j--)
			a[j + 1] = a[j];
		a[j + 1] = tmp;
	}
}