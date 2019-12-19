#pragma once
#include<iostream>
#include<vector>
using namespace std;

int sum_succeed = 0;

struct node
{
	int data;
	node* next;
	node() { next = nullptr; }
};

class HashTable_list
{
public:
	HashTable_list() { for (int i = 0; i < SZ; i++)hashtable[i].data = INF; }

	node* search(int key);
	bool insert(int key);
	int get(node* pos);
	void display();
	double search_fail_rate();
private:
	const static int SZ = 10, INF = INT_MAX;
	
	node hashtable[SZ];
	int hash(int key) { return (key * 3) % 7; }
};

node* HashTable_list::search(int key)
{
	int addr = hash(key);
	if (hashtable[addr].data == key)
	{
		sum_succeed += 1;
		return &hashtable[addr];
	}
	sum_succeed += 1;
	node* p = hashtable[addr].next;
	while (p != nullptr)
	{
		sum_succeed += 1;
		if (p->data == key)
			return p;
		else
			p = p->next;
	}
	if (!p)
		return nullptr;
}

inline bool HashTable_list::insert(int key)
{
	int addr = hash(key);
	if (hashtable[addr].data == INF)
		hashtable[addr].data = key;
	else 
	{
		node* tmp = new node;
		tmp->data = key;
		tmp->next = hashtable[addr].next;
		hashtable[addr].next = tmp;
	}
	return true;
}

inline int HashTable_list::get(node* pos)
{
	return pos->data;
}

inline void HashTable_list::display()
{
	for (int i = 0; i < SZ; i++)
	{
		node* p = &hashtable[i];
		while (p)
		{
			if (p->data != INF)
				cout << p->data << ' ';
			else
				cout << -1;
			p = p->next;
		}
		cout << '\n';
	}
}

inline double HashTable_list::search_fail_rate()
{
	int sum_fail = 0;
	for (int i = 0; i < SZ; i++)
	{
		node* p = &hashtable[i];
		if (p->data != INF)
			sum_fail += 1;
		while (p)
		{
			sum_fail += 1;
			p = p->next;
		}
	}
	return sum_fail * 1.0 / SZ;
}
