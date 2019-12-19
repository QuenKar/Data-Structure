#pragma once
#include<iostream>
using namespace std;
#define MAXDATA 10000

class MaxHeap
{
	int* data;
	int capacity;
	int size;

public:
	MaxHeap() { data = nullptr; capacity = 0; size = 0; }
	MaxHeap(int* a, int len);
	bool Insert_Data(int x);
	bool isFull() { return size > capacity; }
	int Delete_MaxData();
	void Heap_sort()
	{
		for (int i = 0; i < capacity; i++)
			cout << Delete_MaxData() << ' ';
	}
protected:
	void Max_AdjustMinHeap();
	void Max_PercDown(int p);
};

MaxHeap::MaxHeap(int* a, int len)
{
	capacity = len;
	size = 0;
	data = new int[capacity];
	data[0] = MAXDATA;
	for (int i = 0; i < len; i++)
		Insert_Data(a[i]);
}

inline bool MaxHeap::Insert_Data(int x)
{
	int i;
	if (isFull())
		return false;

	i = ++size;
	for (; x > data[i / 2]; i /= 2)
	{
		data[i] = data[i / 2];
	}
	data[i] = x;
	return true;
}

inline int MaxHeap::Delete_MaxData()
{
	int parent, child;
	int mindata, x;

	mindata = data[1];
	x = data[size--];

	for (parent = 1; parent * 2 <= size; parent = child)
	{
		child = parent * 2;

		if ((child != size) && (data[child] < data[child + 1]))
			child++;
		if (x >= data[child])
			break;
		else
			data[parent] = data[child];
	}
	data[parent] = x;

	return mindata;
}

inline void MaxHeap::Max_AdjustMinHeap()
{
	for (int i = size / 2; i > 0; i--)
		Max_PercDown(i);
}

inline void MaxHeap::Max_PercDown(int p)
{
	int parent, child;
	int x;

	x = data[p];
	for (parent = p; parent * 2 <= size; parent = child)
	{
		child = parent * 2;
		if ((child != size) && (data[child] < data[child + 1]))
			child++;
		if (x > data[child])break;
		else
			data[parent] = data[child];
	}

	data[parent] = x;

}

