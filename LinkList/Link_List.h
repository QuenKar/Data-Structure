#pragma once
#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#endif // LINKLIST_H_INCLUDED

#include<iostream>
using namespace std;
class Node
{
public:
	int data;
	Node* next;
};

class List
{
public:
	Node* head;
	List();

	void create_List(int len);
	void insert_Node(int pos, int d);
	void delete_Node(int pos);
	Node* search_Node(int da);
	void Merge_List(List* Lb);
	void reverse_List();
	void output();
};

List::List()
{
	head = new Node;
	head->next = nullptr;
}
//倒序输入
void List::create_List(int len)
{
	Node* p = head;
	while (len)
	{
		Node* s = new Node;
		cin >> s->data;
		s->next = p->next;
		p->next = s;
		p = s;
		len--;
	}
}

void List::insert_Node(int pos, int d)
{
	Node* r = head;

	Node* s = new Node;
	s->data = d;

	while (pos)
	{
		r = r->next;
		pos--;
	}
	s->next = r->next;
	r->next = s;
}

void List::delete_Node(int pos)
{
	Node* r = head;

	while (pos - 1 != 0)
	{
		r = r->next;
		pos--;
	}

	Node* q = r->next;
	r->next = q->next;
	delete q;
	q = nullptr;
}

Node* List::search_Node(int da)
{
	Node* r = head->next;
	while (r)
	{
		if (r->data == da)
		{
			cout << "have found!"<<'\n';
			return r;
		}
			
		else
			r = r->next;
	}
	if (r == nullptr)
		cout << "not found"<<'\n';
}

void List::Merge_List(List * Lb)
{
	Node* r = head;//La的循环变量
	Node* p = Lb->head;//Lb的循环变量

	while (r->next)
	{
		while (p->next)
		{
			if (r->next->data == p->next->data)
			{
				Node* d = p->next;
				p->next = d->next;
				delete d;
				p = p->next;
			}
			else
				p = p->next;
		}
		p = Lb->head;
		r = r->next;
	}
	r->next = Lb->head->next;
	delete Lb->head;
}
//倒置链表方法一
/*
void List::reverse_List()
{
	Node* F = head->next;//记录最后一个结点位置
	Node* p = head->next;

	Node* i = head->next;
	Node* j = head;
	while (p)
	{
		i = p;
		p = p->next;
		i->next = j;
		j = i;
	}
	head->next = i;
	F->next = nullptr;
}
*/
//倒置链表方法二，这方法比上面的少用一个指针。
void List::reverse_List()
{
	Node* F = head->next;//记录最后一个结点位置

	Node* p = head->next->next;
	Node* r = head->next->next;

	while (p)
	{
		p = p->next;
		r->next = head->next;
		head->next = r;
		r = p;
	}
	F->next = nullptr;
}


inline void List::output()
{
	Node* r = head->next;
	while (r)
	{
		cout << r->data << ' ';
		r = r->next;
	}
	cout << '\n';
}
