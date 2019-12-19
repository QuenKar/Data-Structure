#pragma once
#include<iostream>
#include<iomanip>
#include<stack>
using namespace std;

typedef char ElemType;
enum PointTag
{
	link,thread
};
struct ThrBiNode
{
	ElemType data;
	ThrBiNode* rchild, * lchild;
	PointTag rtag, ltag;
	ThrBiNode() { rchild = nullptr; lchild = nullptr; rtag = link; ltag = link; }
};

class ThrBiTree
{
	ThrBiNode* Thrt;
	ThrBiNode* pre;
	
	ThrBiNode* root;
public:
	ThrBiTree() { root = Create(root); pre = nullptr; Thrt = nullptr; }
	~ThrBiTree() { delete Thrt; Release(root); }
	
	void InThrOrder();

protected:
	ThrBiNode* Create(ThrBiNode* root);
	void Release(ThrBiNode* bt);
	void InThread(ThrBiNode* Thrt);
	void InThreading(ThrBiNode* p);
	void Non_Recur_InThreading();
};

ThrBiNode* ThrBiTree::Create(ThrBiNode* root)
{
	ThrBiNode* T = root;
	ElemType ch;
	cin >> ch;
	if (ch == '#')
		T = nullptr;
	else
	{
		T = new ThrBiNode;
		T->data = ch;
		T->lchild = Create(T->lchild);
		T->rchild = Create(T->rchild);
	}
	return T;
}
//É¾³ýº¯ÊýÔõÃ´Ð´£¿£¿£¿
inline void ThrBiTree::Release(ThrBiNode* bt)
{
	if (bt->ltag != thread)
		Release(bt->lchild);
	if (bt->rtag != thread)
		Release(bt->rchild);
	delete bt;
	bt = nullptr;
}

inline void ThrBiTree::InThread(ThrBiNode* Thrt)
{
	Thrt->rtag = thread;
	Thrt->rchild = Thrt;
	if (!root)
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = root;
		pre = Thrt;
		
		ThrBiNode* p = root;

		//InThreading(p);
		Non_Recur_InThreading();

		pre->rtag = thread;
		pre->rchild = Thrt;
		Thrt->rtag = thread;
		Thrt->rchild = pre;

	}
}

inline void ThrBiTree::InThreading(ThrBiNode* p)
{
	if (p)
	{
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->ltag = thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->rtag = thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}

inline void ThrBiTree::Non_Recur_InThreading()
{
	stack<ThrBiNode*> s;
	ThrBiNode* p = root;
	while (!s.empty() || p)
	{
		while (p)
		{
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			if (!p->lchild)
			{
				p->ltag = thread;
				p->lchild = pre;
			}
			if (!pre->rchild)
			{
				pre->rtag = thread;
				pre->rchild = p;
			}
			pre = p;
			p = p->rchild;
		}
	}
	cout << '\n';
}

inline void ThrBiTree::InThrOrder()
{
	Thrt = new ThrBiNode;
	if (!root)
		return;
	else
	{
		InThread(Thrt);
	}
	ThrBiNode* p = root->lchild;
	while (p != Thrt)
	{
		while (p->rtag == link)
			p = p->lchild;
		cout << setw(4) << p->data;
		while (p->rchild != Thrt && p->rtag == thread)
		{
			p = p->rchild;
			cout << setw(4) << p->data;
		}
		p = p->rchild;
	}
}