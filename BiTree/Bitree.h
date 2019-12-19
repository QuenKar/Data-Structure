#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<iomanip>
using namespace std;

typedef char Elemtype;
struct BiNode
{

	Elemtype data;
	BiNode* lchild, * rchild;
};

class Bitree
{
public:
	Bitree() { root = Create(root); height = 0; }
	~Bitree() { Release(root); }

	void Recur_PreOrder() { PreOrder(root); }
	void Recur_InOrder() { InOrder(root); }
	void Recur_PostOrder() { PostOrder(root); }
	void LevelOrder();

	void Non_Recur_PreOrder();
	void Non_Recur_InOrder();
	void Non_Recur_PostOrder();

	int GetHeight() { return height; }

private:
	BiNode* Create(BiNode* root);
	void Release(BiNode* root);
	void PreOrder(BiNode* root);
	void InOrder(BiNode* root);
	void PostOrder(BiNode* root);

	BiNode* root;
	int height;
};

BiNode* Bitree::Create(BiNode* root)
{
	Elemtype ch;
	cin >> ch;
	if (ch == '#')
		root = nullptr;
	else
	{
		root = new BiNode;
		root->data = ch;
		root->lchild = Create(root->lchild);
		root->rchild = Create(root->rchild);
	}
	return root;
}

void Bitree::Release(BiNode* root)
{
	if (root)
	{
		Release(root->lchild);
		Release(root->rchild);
		delete root;
		root = nullptr;
	}
}

void Bitree::PreOrder(BiNode* root)
{
	if (root)
	{
		cout << setw(4) << root->data;
		PreOrder(root->lchild);
		PreOrder(root->rchild);
	}
}

void Bitree::InOrder(BiNode* root)
{
	if (root)
	{
		InOrder(root->lchild);
		cout << setw(4) << root->data;
		InOrder(root->rchild);
	}
}

void Bitree::PostOrder(BiNode* root)
{
	if (root)
	{
		PostOrder(root->lchild);
		PostOrder(root->rchild);
		cout << setw(4) << root->data;
	}
}

inline void Bitree::Non_Recur_PreOrder()
{
	stack<BiNode*> s;
	BiNode* p = root;
	while (!s.empty() || p)
	{
		while (p)
		{
			cout << setw(4) << p->data;
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
	cout << '\n';
}

inline void Bitree::Non_Recur_InOrder()
{
	stack<BiNode*> s;
	BiNode* p = root;
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
			cout << setw(4) << p->data;
			p = p->rchild;
		}
	}
	cout << '\n';
}

inline void Bitree::Non_Recur_PostOrder()
{
	stack<BiNode*> s;
	BiNode* pCurrent, * pVisited = nullptr;
	pCurrent = root;
	while (pCurrent)
	{
		s.push(pCurrent);
		pCurrent = pCurrent->lchild;
	}
	while (!s.empty())
	{
		pCurrent = s.top();
		s.pop();
		if (pCurrent->rchild == nullptr || pCurrent->rchild == pVisited)
		{
			cout << setw(4) << pCurrent->data;
			pVisited = pCurrent;
		}
		else
		{
			s.push(pCurrent);
			pCurrent = pCurrent->rchild;
			while (pCurrent)
			{
				s.push(pCurrent);
				pCurrent = pCurrent->lchild;
			}
		}
	}
	cout << '\n';
}

void Bitree::LevelOrder()
{
	queue<BiNode*> q;
	BiNode* p = root;
	if (p)
		q.push(p);

	while (!q.empty())
	{
		height++;
		int size = q.size();
		int cnt = 0;
		while (cnt < size)
		{
			p = q.front();
			q.pop();
			cout << setw(4) << p->data;
			if (p->lchild)
				q.push(p->lchild);
			if (p->rchild)
				q.push(p->rchild);
			cnt++;
		}
	}
	cout << '\n';
}