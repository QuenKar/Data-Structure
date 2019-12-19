#include"Merge_sort.h"
#include"Quick_sort.h"
#include"Heap_sort.h"
#include"Shell_sort.h"
#include"Binary_Insert_sort.h"
#include"display.h"

void recover(int* a, int* b,int len)
{
	for (int i = 0; i < len; i++)
		b[i] = a[i];
}

int main()
{
	int a[] = { 49,38,65,97,76,13,27,49 };
	int len = sizeof(a) / sizeof(int);
	int* b = new int[len];

	//------------ÕÛ°ë²åÈëÅÅÐò-----------//
	recover(a, b, len);
	cout << "\nBinary_Insert Sort:\n";
	binary_Insert_sort(b, len);
	show(b, len);

	//------------Ï£¶ûÅÅÐò--------------//
	recover(a, b, len);
	cout << "\nShell Sort:\n";
	Shell_sort(b, len);
	show(b, len);

	//------------¿ìËÙÅÅÐò--------------//
	recover(a, b, len);
	cout << "\nQuick Sort:\n";
	QSort(b, 0, len - 1);
	show(b, len);

	//------------¶ÑÅÅÐò--------------//
	MaxHeap h(a, len);
	cout << "\nHeap Sort:\n";
	h.Heap_sort();

	//------------¹é²¢ÅÅÐò--------------//
	recover(a, b, len);
	cout << "\nMerge Sort:\n";
	MergeSort(b, len);
	show(b, len);

	return 0;
}