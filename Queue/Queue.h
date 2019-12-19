#pragma once

#include<iostream>
#include<iomanip>
using namespace std;

class Node
{
public:
	int data;
	Node* next;
};

class Queue
{
public:
	Node* front;
	Node* rear;

	Queue()
	{
		front = rear = new Node;
		rear->next = nullptr;
	}

	void DestoryNode();
	bool QueueEmpty();

	void EnQueue(int da);
	int DeQueue();
};

inline void Queue::DestoryNode()
{
	while (front)
	{
		rear = front->next;
		delete front;
		front = rear;
	}
}

inline bool Queue::QueueEmpty()
{
	if (front == rear)
		return true;
	else
		return false;
}

inline void Queue::EnQueue(int da)
{
	Node* s = new Node;
	if (!s)return;

	s->data = da;
	s->next = rear->next;
	rear->next = s;
	rear = s;
}

inline int Queue::DeQueue()
{
	if (front == rear)
		return -1;
	else
	{
		Node* p = front->next;
		front->next = p->next;
		int e = p->data;
		if (p == rear)
		{
			rear = front;
		}
		delete p;
		return e;
	}
}

void yanghui(Queue & Q)
{
	int n;
	cin >> n;
	int k = 1;
	Q.EnQueue(1);
	Q.EnQueue(0);
	cout <<setw(6) << 1 << endl;;
	int e;
	while (k <= n)
	{
		int s = 0;
		do
		{
			e = Q.DeQueue();
			Q.EnQueue(s + e);
			s = e;

		} while (e != 0);
		Q.EnQueue(e);
		k++;
		Node * r = Q.front->next;
		while (r->data != 0)
		{
			cout<<setw(6)<< r->data << ' ';
			r = r->next;
		}
		cout << '\n';
	}
}