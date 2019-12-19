#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
int sum_succeed_1 = 0;
class HashTable_linear
{
public:
	HashTable_linear() { fill(hashtable, hashtable + SZ, INF); }
	//memset(hashtable,INF,sizeof(hashtable);
	//为什么会初始化的值为-1

	int search(int key);
	bool insert(int key);
	int get(int pos);
	void display(); 

	double search_fail_rate();
private:
	const static int SZ = 10, INF = INT_MAX;
	int hashtable[SZ];

	int hash(int key) { return (key * 3) % 7; }

	void linear_detect(int& addr) { addr = (addr + 1) % SZ; }
};

int HashTable_linear::search(int key)
{
	int addr = hash(key), tmp = addr;
	sum_succeed_1 += 1;
	while (hashtable[addr] != INF)
	{
		if (hashtable[addr] == key)return addr;
		linear_detect(addr);
		sum_succeed_1 += 1;
		if (addr == tmp)
			return -1;
	}
	return addr;
}

inline bool HashTable_linear::insert(int key)
{
	int pos = search(key);
	if (pos == -1)
	{
		cout << "hashtable is full!";
		return false;
	}
	if (hashtable[pos] == key)
	{
		puts("The key has been existed!");
		return false;
	}
	hashtable[pos] = key;
	return true;
}

inline int HashTable_linear::get(int pos)
{
	return hashtable[pos];
}

inline void HashTable_linear::display()
{
	for (int i = 0; i < SZ; i++)
	{
		if (hashtable[i] != INF)
			cout << hashtable[i] << ' ';
		else
			cout << -1 << ' ';
	}
}

inline double HashTable_linear::search_fail_rate()
{
	int sum_fail = 0;
	for (int i = 0; i < 7; i++)
	{
		int j = i;
		sum_fail += 1;
		while (hashtable[j] != INF)
		{
			linear_detect(j);
			sum_fail += 1;
		}
	}
	return sum_fail * 1.0 / 7;
}
