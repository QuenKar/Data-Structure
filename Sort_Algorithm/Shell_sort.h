#pragma once
#include<iostream>
using namespace std;

void Shell_sort(int* a, int len)
{
	
	for (int increment = 3; increment > 0; increment -= 2)
	{
		for (int i = increment; i < len; i++)
		{
			int tmp = a[i];
			int j = i;
			for (; j > 0 && a[j - increment] < tmp; j -= increment)
				a[j] = a[j - increment];
			a[j] = tmp;
		}
	}
}