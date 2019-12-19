#pragma once

#include"AdjListGraphArc.h"
#include"AdjListGraphVex.h"
#include<queue>
#include<stack>
#define DEFAULT_SIZE 10
#define Error -1

enum Status{VISIT,UNVISIT};


class AdjListDirGraph
{
public:
	AdjListDirGraph(int _vexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(ElemType* Vexs, int _vexNum, int _vexMaxNum = DEFAULT_SIZE);
	~AdjListDirGraph();

	void Clear();
	bool isEmpty();
	ElemType GetElem(int vex);
	int GetOrder(ElemType& e);
	void InsertArc(int vex1, int vex2);//!!!
	void InsertVex(ElemType& e);//!!!
	void DeleteArc(int vex1, int vex2);//!!!
	void DeleteVex(ElemType& e);//!!!
	int GetVexNum();
	int GetArcNum();
	int FirstAdjVex(int vex);//!!!
	int NextAdjVex(int vex1, int vex2);//!!!
	void Display();

	//广度遍历
	void BFS(int vex);
	//深度遍历
	void Recur_DFS();
	void Without_Recur_DFS(int vex);

protected:
	void DFS(int vex);

private:
	Status* flag_vex;
	AdjListDirGraphVex* vexTable;
	int vexNum;
	int arcNum;
	int vexMaxNum;
};

AdjListDirGraph::AdjListDirGraph(int _vexMaxNum)
{
	vexMaxNum = _vexMaxNum;
	vexNum = arcNum = 0;
	flag_vex = new Status[vexMaxNum];
	vexTable = new AdjListDirGraphVex[vexMaxNum];
}

inline AdjListDirGraph::AdjListDirGraph(ElemType* Vexs, int _vexNum, int _vexMaxNum)
{
	vexMaxNum = _vexMaxNum;
	vexNum = _vexNum;
	flag_vex = new Status[vexMaxNum];
	vexTable = new AdjListDirGraphVex[vexMaxNum];
	for (int i = 0; i < vexNum; i++)
	{
		flag_vex[i] = UNVISIT;
		vexTable[i].data = Vexs[i];
	}
}

inline AdjListDirGraph::~AdjListDirGraph()
{
	if (flag_vex)
		delete[] flag_vex;
	Clear();
	if (vexTable)
		delete[] vexTable;
}

inline void AdjListDirGraph::Clear()
{
	AdjListDirGraphArc* p;
	for (int i = 0; i < vexNum; i++)
	{
		while (vexTable[i].firstArc != nullptr)
		{
			p = vexTable[i].firstArc;
			vexTable[i].firstArc = p->nextArc;
			delete p;
		}
	}
	arcNum = 0;
}

inline bool AdjListDirGraph::isEmpty()
{
	return vexNum == 0;
}

inline ElemType AdjListDirGraph::GetElem(int vex)
{
	return vexTable[vex].data;
}

inline int AdjListDirGraph::GetOrder(ElemType& e)
{
	for (int i = 0; i < vexNum; i++)
		if (vexTable[i].data == e)
			return i;
	return -1;
}

inline void AdjListDirGraph::InsertArc(int vex1, int vex2)
{
	if (vex1<0 || vex1>=vexMaxNum)
		cout << "vex1 Error!!!";
	else if (vex2<0 || vex2>=vexMaxNum)
		cout << "vex2 Error!!!";
	else if(vex1==vex2)
		cout<< "vex1不能等于vex2!";
	else
	{
		vexTable[vex1].firstArc = new AdjListDirGraphArc(vex2, vexTable[vex1].firstArc);//这个写法有点nb。既构造了新的边，也完成了插入操作。
		arcNum++;     
	}
}

inline void AdjListDirGraph::InsertVex(ElemType& e)
{
	if (vexNum >= vexMaxNum)
		cout << "The Graph's Vexs are full";
	else
	{
		flag_vex[vexNum] = UNVISIT;
		vexTable[vexNum].data = e;
		vexTable[vexNum].firstArc = nullptr;
		vexNum++;
	}
}

inline void AdjListDirGraph::DeleteArc(int vex1, int vex2)
{
	if (vex1 < 0 || vex1 >= vexMaxNum)
		cout << "vex1 Error!!!";
	if (vex2 < 0 || vex2 >= vexMaxNum)
		cout << "vex2 Error!!!";
	AdjListDirGraphArc* p = vexTable[vex1].firstArc;
	while (p->nextArc != nullptr && p->nextArc->adjvex != vex2)
		p = p->nextArc;
	AdjListDirGraphArc* tmp = p->nextArc;
	p = p->nextArc->nextArc;
	delete tmp;
	arcNum--;
}

inline void AdjListDirGraph::DeleteVex(ElemType& e)
{
	int v = GetOrder(e);
	int u;
	if (v == -1)
		cout << "The vex is Non-existed!";
	else
	{
		for (u = 0; u < vexNum; u++)
		{
			if (u != v)
				DeleteArc(u, v);
		}
		AdjListDirGraphArc* p = vexTable[v].firstArc;
		AdjListDirGraphArc* tmp;
		while (p)
		{
			tmp = p;
			p = p->nextArc;
			delete tmp;
			arcNum--;
		}
		if (v == vexNum - 1)
			vexNum--;
		else
		{
			vexNum--;
			vexTable[v] = vexTable[vexNum];
			vexTable[vexNum].firstArc = nullptr;
			flag_vex[v] = flag_vex[vexNum];
			for (u = 0; u < vexNum; u++)
			{
				if (u != v)
				{
					p = vexTable[u].firstArc;
					while (p)
					{
						if (p->adjvex == vexNum)
						{
							p->adjvex = v;
						}
						p = p->nextArc;
					}
				}
			}
		}
	}
}

inline int AdjListDirGraph::GetVexNum()
{
	return vexNum;
}

inline int AdjListDirGraph::GetArcNum()
{
	return arcNum;
}

inline int AdjListDirGraph::FirstAdjVex(int vex)
{
	if(vex<0||vex>=vexMaxNum)
		cout<< "vex不合法!";
	if (vexTable[vex].firstArc == nullptr)
		return Error;
	else
		return vexTable[vex].firstArc->adjvex;
}

inline int AdjListDirGraph::NextAdjVex(int vex1, int vex2)
{
	if (vex1 < 0 || vex1 >= vexNum)
		cout << "vex1不合法!";
	if (vex2 < 0 || vex2 >= vexNum)
		cout << "vex2不合法!";
	AdjListDirGraphArc* p = vexTable[vex1].firstArc;
	while (p != nullptr&&p->adjvex!=vex2)
	{
		p = p->nextArc;
	}
	if (p == nullptr || p->nextArc == nullptr)
		return Error;
	else
		return p->nextArc->adjvex;
}

inline void AdjListDirGraph::Display()
{
	cout << "该有向图共" << vexNum << "个顶点," << arcNum << "条弧" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		cout << vexTable[i].data << "的邻接顶点为: ";
		AdjListDirGraphArc* p = vexTable[i].firstArc;
		if (p == NULL)
			cout << "无" << endl;
		else
		{
			while (p != NULL)
			{
				cout << GetElem(p->adjvex) << " ";
				p = p->nextArc;
			}
			cout << endl;
		}

	}
}

//--------------------------BFS---------------------------//
//--------------------------------------------------------//
//从vex开始遍历

inline void AdjListDirGraph::BFS(int vex)
{
	flag_vex = new Status[vexNum];
	for (int i = 0; i < vexNum; i++)
		flag_vex[i] = UNVISIT;

	queue<int> q;

	for (int i = 0; i < vexNum; i++)
	{
		if (flag_vex[i] == UNVISIT)
		{
			q.push(i);
			while (!q.empty())
			{
				i = q.front();
				flag_vex[i] = VISIT;
				q.pop();

				for (int j = FirstAdjVex(i); j != Error; j = NextAdjVex(i, j))
				{
					if (flag_vex[j] == UNVISIT)
					{
						cout << vexTable[i].data << "-->" << vexTable[j].data << '\n';
						q.push(j);
					}
				}

			}
		}
	}
	cout << '\n';
}

//-----------------------------DFS--------------------------//
//----------------------------------------------------------//

void AdjListDirGraph::Recur_DFS()
{
	flag_vex = new Status[vexNum];
	for (int i = 0; i < vexNum; i++)
		flag_vex[i] = UNVISIT;

	for (int i = 0; i < vexNum; i++)
		if (flag_vex[i] == UNVISIT)
			DFS(i);
}

inline void AdjListDirGraph::DFS(int vex)
{
	if (flag_vex[vex] == UNVISIT)
	{
		flag_vex[vex] = VISIT;
	}
	int j = FirstAdjVex(vex);
	while (j != Error)
	{
		if (flag_vex[j] == UNVISIT)
		{
			cout << vexTable[vex].data << "-->" << vexTable[j].data << '\n';
			DFS(j);
		}
		else
			j = NextAdjVex(vex, j);
	}
}

//------------------------非递归DFS-------------------------//
//----------------------------------------------------------//
inline void AdjListDirGraph::Without_Recur_DFS(int vex)
{
	flag_vex = new Status[vexNum];
	for (int i = 0; i < vexNum; i++)
		flag_vex[i] = UNVISIT;

	stack<int> s;

	for (int i = 0; i < vexNum; i++)
	{
		if (flag_vex[i] == UNVISIT)
		{
			s.push(i);
			while (!s.empty())
			{
				int tmp = s.top();
				s.pop();
				flag_vex[tmp] = VISIT;

				int vex = tmp;
				for (tmp = FirstAdjVex(vex); tmp != Error; )
				{
					if (flag_vex[tmp] == UNVISIT)
					{
						cout << vexTable[vex].data << "-->" << vexTable[tmp].data << '\n';
						s.push(tmp);
						break;
					}
					else
						tmp = NextAdjVex(vex, tmp);
				}

			}
		}
	}
	cout << '\n';
}
