#pragma once
#include<iostream>
using namespace std;

void Merge(int arr[], int start, int end, int mid, int temp[])
{
	int i = start;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= end)
	{
		if (arr[i] > arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i <= mid)
		temp[k++] = arr[i++];
	while (j <= end)
		temp[k++] = arr[j++];
	for (int i = 0; i < k; i++)
		arr[start + i] = temp[i];
}

void MergeSort(int arr[], int start, int end, int temp[])
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(arr, start, mid, temp);
		MergeSort(arr, mid + 1, end, temp);
		Merge(arr, start, end, mid, temp);
	}
}

void MergeSort(int arr[], int len)
{
	int start = 0, end = len - 1;
	int* temp = new int[len];
	MergeSort(arr, start, end, temp);
}