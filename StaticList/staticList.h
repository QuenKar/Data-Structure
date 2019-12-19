#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

#define MAXSIZE 1000

#define RADIX 10
#define KEY_NUM 2
vector<vector<int>> vq(RADIX);

struct node
{
	int data;
	int next;
	node() = default;
};

class StaticList
{
	int length;//记录当前静态链表值的个数
	node List[MAXSIZE];

public:
	StaticList() { length = 0; List[0].data = INT_MIN; List[0].next = 0; }
	StaticList(int len):length(len){}
	StaticList(int a[], int len);

	void StaticList_Insert_Sort();
	void Radix_Sort();

	void Display()
	{
		for (int i = 1; i <= length; i++)
			cout << List[i].data << ' ';
	}
protected:
	void Arrange();

	void Collect();
	void Distribute(int n);
};

StaticList::StaticList(int a[], int len):length(len)
{
	if (length >= MAXSIZE)
	{
		cerr << "the array is so big";
		exit(1);
	}
	//0号单元作为头结点不放元素
	List[0].data = INT_MIN;
	for (int i = 0; i < length; i++)
	{
		List[i].next = i + 1;
		List[i + 1].data = a[i];
	}
	//循环链表，最后一个元素指向头结点
	List[length].next = 0;
}

//------------------静态插入------------------//
//------------------静态插入------------------//

inline void StaticList::StaticList_Insert_Sort()
{
	List[1].next = 0;
	for (int i = 2; i <= length; i++)
	{
		int pre = 0;
		for (int j = List[0].next; ; )
		{
			while (List[j].data >= List[i].data)
			{
				pre = j;
				j = List[j].next;
			}

			List[i].next = List[pre].next;
			List[pre].next = i;
			break;

		}
	}
	Arrange();
}


inline void StaticList::Arrange()
{
	int p = List[0].next,q;
	for (int i = 1; i < length; i++)
	{
		while (p < i)
			p = List[p].next;
		q = List[p].next;
		if (p != i)
		{
			swap(List[p], List[i]);
			List[i].next = p;
		}
		p = q;
	}
}


//------------------基数排序--------------------//
//------------------基数排序--------------------//

inline void StaticList::Radix_Sort()
{
	for (int n = 0; n < KEY_NUM; n++)
	{
		Distribute(n);
		Collect();
	}
}

inline void StaticList::Distribute(int n)
{
	int temp = 0;
	for (int p = List[0].next; p != 0; p = List[p].next)
	{
		if (n != 0)
			temp = List[p].data / (n * RADIX);
		else
			temp = List[p].data;
		vq[temp % RADIX].push_back(List[p].data);
	}
}

inline void StaticList::Collect()
{
	int n = 1;
	for (int i = RADIX - 1; i >= 0; i--)
	{
		for (auto iter = vq[i].begin(); iter != vq[i].end(); ++iter)
		{
			List[n].data = (*iter);
			n++;
		}
	}
	for (int i = 0; i < RADIX; i++)
	{
		vq[i].clear();
		vq[i].shrink_to_fit();
	}
}

