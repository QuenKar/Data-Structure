#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
typedef int ElemType;

#define GET_HEIGHT(T) (T == nullptr ? -1 : T->height )

struct AVL_node
{
	ElemType data;
	AVL_node* lchild;
	AVL_node* rchild;
	int height;

	~AVL_node() { delete lchild; delete rchild; lchild = rchild = nullptr; }
};

int Max(int a, int b)
{
	return a > b ? a : b;
}

class AVL_Tree
{
public:
	AVL_Tree();

	void Insert(ElemType x) { root = Insert_Node(root, x); }
	void Delete(ElemType x) { root = Delete(root, x); }
	void Inorder() { InOrder(root);	cout << '\n';}
	void PreOrder() { PreOrder(root); 	cout << '\n';}
	
protected:
	AVL_node* Insert_Node(AVL_node* T, ElemType x);
	AVL_node* SingleLeftRotation(AVL_node* A);
	AVL_node* SingleRightRotation(AVL_node* A);
	AVL_node* DoubleLeftRightRotation(AVL_node* A);
	AVL_node* DoubleRightLeftRotation(AVL_node* A);
	
	void PreOrder(AVL_node* a);
	void InOrder(AVL_node* a);

	AVL_node* Delete(AVL_node* A, ElemType x);
	AVL_node* findMin(AVL_node* A) { while (A->lchild)A = A->lchild; return A; }
	int getBalance(AVL_node* A) { return GET_HEIGHT(A->lchild) - GET_HEIGHT(A->rchild); }

private:
	AVL_node* root;
};

inline AVL_Tree::AVL_Tree()
{
	root = nullptr;
}


inline AVL_node* AVL_Tree::Insert_Node(AVL_node* T, ElemType x)
{
	if (!T)
	{
		T = new AVL_node;
		T->data = x;
		T->lchild = nullptr;
		T->rchild = nullptr;
		T->height = 0;
	}
	else if (x < T->data)
	{
		T->lchild = Insert_Node(T->lchild, x);
		//平衡操作
		if (GET_HEIGHT(T->lchild) - GET_HEIGHT(T->rchild) == 2)
		{
			//LL
			if (x < T->lchild->data)
				T = SingleLeftRotation(T);
			else//LR
				T = DoubleLeftRightRotation(T);
		}
	}
	else if (x > T->data)
	{
		T->rchild = Insert_Node(T->rchild, x);
		if (GET_HEIGHT(T->lchild) - GET_HEIGHT(T->rchild) == -2)
		{
			//RR
			if (x > T->rchild->data)
				T = SingleRightRotation(T);
			else//RL
				T = DoubleRightLeftRotation(T);
		}
	}
	//重新计算每个节点高度
	T->height = Max(GET_HEIGHT(T->lchild), GET_HEIGHT(T->rchild)) + 1;

	return T;
}
//LL
AVL_node* AVL_Tree::SingleLeftRotation(AVL_node* A)
{
	AVL_node* B = A->lchild;
	A->lchild = B->rchild;
	B->rchild = A;

	A->height = Max(GET_HEIGHT(A->lchild), GET_HEIGHT(A->rchild)) + 1;
	B->height = Max(GET_HEIGHT(B->lchild), GET_HEIGHT(A)) + 1;

	return B;
}
//RR
AVL_node* AVL_Tree::SingleRightRotation(AVL_node* A)
{
	AVL_node* B = A->rchild;
	A->rchild = B->lchild;
	B->lchild = A;

	A->height = Max(GET_HEIGHT(A->lchild), GET_HEIGHT(A->rchild)) + 1;
	B->height = Max(GET_HEIGHT(B->rchild), GET_HEIGHT(A)) + 1;

	return B;
}
//LR
inline AVL_node* AVL_Tree::DoubleLeftRightRotation(AVL_node* A)
{
	A->lchild = SingleRightRotation(A->lchild);

	return SingleLeftRotation(A);
}
//RL
inline AVL_node* AVL_Tree::DoubleRightLeftRotation(AVL_node* A)
{
	A->rchild = SingleLeftRotation(A->rchild);

	return SingleRightRotation(A);
}

inline void AVL_Tree::PreOrder(AVL_node* a)
{
	if (a)
	{
		cout << a->data << ' ';
		PreOrder(a->lchild);
		PreOrder(a->rchild);
	}
}

inline void AVL_Tree::InOrder(AVL_node* a)
{
	if (a)
	{
		InOrder(a->lchild);
		cout << a->data << ' ';
		InOrder(a->rchild);
	}
}

inline AVL_node* AVL_Tree::Delete(AVL_node* p, ElemType x)
{
	//删除操作
	if (p == nullptr)
		return p;
	if (p->data > x)
		p->lchild = Delete(p->lchild, x);
	else if (p->data < x)
		p->rchild = Delete(p->rchild, x);
	else
	{
		if (p->lchild && p->rchild)
		{
			swap(p->data, findMin(p->rchild)->data);//将p的值与右子树中的最小值交换
			p->rchild = Delete(p->rchild, x);
		}
		else
			p = (p->lchild != nullptr) ? p->lchild : p->rchild;
	}
	//从下往上依次调平衡，与插入操作相同
	if (p == nullptr)
		return p;
	//LL
	if (getBalance(p) == 2 && getBalance(p->lchild) >= 0)
		return SingleLeftRotation(p);
	//LR
	if (getBalance(p) == 2 && getBalance(p->lchild) < 0)
		return DoubleLeftRightRotation(p);
	//RL
	if (getBalance(p) == -2 && getBalance(p->rchild) >= 0)
		return DoubleRightLeftRotation(p);
	//RR
	if (getBalance(p) == -2 && getBalance(p->rchild) < 0)
		return SingleRightRotation(p);

	return p;
}

