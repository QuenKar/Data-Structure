//#pragma once
//#include<iostream>
//#include<cstdlib>
//using namespace std;
//
//class Node
//{
//public:
//	int x, y;
//	int e;
//	Node* right;
//	Node* down;
//
//	Node() { right = down = nullptr; }
//};
//
//class CrossList
//{
//public:
//	Node* rhead;
//	Node* chead;
//	int mu, nu, tu;
//
//	CrossList() { rhead = chead = nullptr; mu = nu = tu = 0; }
//	~CrossList() { delete[]rhead; delete[]chead; }
//
//	void CreateSMatrix_CL();
//	void Add_CrossList(CrossList& pb);
//};
//
//void CrossList::CreateSMatrix_CL()
//{
//	int m, n, t;
//	cin >> m >> n >> t;
//	mu = m; nu = n; tu = t;
//
//	rhead = new Node[m + 1];
//	if (!rhead)exit(1);
//	chead = new Node[n + 1];
//	if (!chead)exit(1);
//
//	int x, y, e;
//	for (cin >> x >> y >> e; x != 0; cin >> x >> y >> e)
//	{
//		Node* s = new Node;
//		if (!s)exit(1);
//
//		s->x = x; s->y = y; s->e = e;
//
//		if (rhead[s->x].right = nullptr)
//		{
//			s->right = rhead->right;
//			rhead->right = s;
//		}
//		else
//		{
//			Node* r = &rhead[s->x];
//			while (r->right->y < s->y)
//			{
//				r = r->right;
//				if (r->right = nullptr)
//					break;
//			}
//			s->right = r->right;
//			r->right = s;
//		}
//
//		if (chead[s->y].down = nullptr)
//		{
//			s->down = chead->down;
//			chead->down = s;
//		}
//		else
//		{
//			Node* c = &chead[s->y];
//			while (c->down->x < s->x)
//			{
//				c = c->down;
//				if (c->down = nullptr)
//					break;
//			}
//			s->down = c->down;
//			c->down = s;
//		}
//	}
//}
//
//inline void CrossList::Add_CrossList(CrossList& Pb)
//{
//	for (int i = 1; i <= mu; i++)
//	{
//		Node* pa = rhead[i].right;
//		Node* pb = Pb.rhead[i].right;
//		Node* pre = &rhead[i];
//
//		if (pa == nullptr && pb == nullptr)
//			continue;
//
//		if (pa != nullptr && pb == nullptr)
//			continue;
//
//		while (pb != nullptr)
//		{
//			if (pa->y > pb->y)
//			{
//				Node* s = new Node;
//				s->x = pb->x;
//				s->y = pb->y;
//				s->e = pb->e;
//				s->right = nullptr;
//				s->down = nullptr;
//
//				s->right = pre->right;
//				pre->right = s;
//
//				pb = pb->right;
//			}
//
//			if (pa != nullptr && pa->y < pb->y)
//			{
//				pre = pa;
//				pa = pa->right;
//			}
//
//			if (pa->y == pb->y)
//			{
//				pa->e += pb->e;
//				if (pa->e == 0)
//				{
//					Node* p = pa;
//					pre->right = pa->right;
//					pa = pa->right;
//					pb = pb->right;
//
//					Node* c = rhead[pa->y].down;
//					while (c->down != p)
//						c = c->down;
//					c->down = c->down->down;
//
//					delete p;
//					p = nullptr;
//				}
//			}
//		}
//	}
//}
//
