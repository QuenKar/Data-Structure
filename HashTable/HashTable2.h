#pragma once
#include<iostream>
using namespace std;

const int a[] = { 1,-1,4,-4,9,-9,16,-16,25,-25 };
int sum_succeed_2 = 0;
class HashTable_twice
{
public:
	HashTable_twice(){ fill(hashtable, hashtable + SZ, INF); }
	bool insert(int key);
	int search(int key);
	void display();
	int get(int pos);

	double search_fail_rate();
private:
	const static int SZ = 10, INF = INT_MAX;
	int hashtable[SZ];

	int hash(int key) { return (key * 3) % 7; }
	bool twice_detect(int& addr, int& n);
};

bool HashTable_twice::insert(int key)
{
	int pos = search(key);
	if (pos == -1)
	{
		cout << "\nInsertion is error!\n";
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

inline int HashTable_twice::search(int key)
{
	int addr = hash(key), n = 0;
	sum_succeed_2 += 1;
	while (hashtable[addr] != INF)
	{
		if (hashtable[addr] == key)return addr;
		bool flag=twice_detect(addr, n);
		sum_succeed_2 += 1;
		if (flag == false)
			return -1;
	}
	return addr;
}

inline void HashTable_twice::display()
{
	for (int i = 0; i < SZ; i++)
	{
		if (hashtable[i] != INF)
			cout << hashtable[i] << ' ';
		else
			cout << -1 << ' ';
	}
}

inline int HashTable_twice::get(int pos)
{
	return hashtable[pos];
}

inline double HashTable_twice::search_fail_rate()
{
	int sum_fail = 0;
	for (int i = 0; i < 7; i++)
	{ 
		int j = i;
		int n = 0;
		sum_fail += 1;
		while (n < 10 && hashtable[j] != INF)
		{
			twice_detect(j,n);
			sum_fail += 1;
		}
	}
	return sum_fail * 1.0 / 7;
}

inline bool HashTable_twice::twice_detect(int& addr, int& n)
{
	if (n < SZ)
	{
		addr = addr + a[n];
		n++;
		return true;
	}
	else
		return false;
}
