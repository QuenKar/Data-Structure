#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define DEFAULT_SIZE 20
#define Error -1
#define OK 10000000

enum Status { VISIT, UNVISIT };

class AdjMatrixGraph
{
public:
	//Basic Operations
	AdjMatrixGraph();
	AdjMatrixGraph(int vexNum);
	~AdjMatrixGraph();
	void Insert(int vex1, int vex2);
	int Firstvex(int vex);
	int Nextvex(int vex1, int vex2);
	void Display();

	//广度遍历
	void BFS(int vex);
	//深度遍历
	void Recur_DFS();
	void Without_Recur_DFS(int vex);

	//求强连通
	void tarjan();

	//有向树
	void DirTree();

	//拓扑排序
	int TopologicSort();
protected:
	void DFS(int vex);
	void tarjan(int u);
	void FindInDegree(int* a);
private:
	char* vertexes;//记录顶点
	int** arcs;//记录边
	int vexNum, vexMaxNum, arcNum;
	Status** flag_arc;
	Status* flag_vex;
};
//-----------------Basic Operations-----------//
//-----------------Basic Operations-----------//

inline AdjMatrixGraph::AdjMatrixGraph()
{
	vexMaxNum = DEFAULT_SIZE;
	vexNum = arcNum = 0;
	vertexes = nullptr;
	arcs = nullptr;
	flag_arc = nullptr;
	flag_vex = nullptr;
}

AdjMatrixGraph::AdjMatrixGraph(int vertexNum)
{
	vexMaxNum = DEFAULT_SIZE;
	arcNum = 0;
	vexNum = vertexNum;

	vertexes = new char[vertexNum];

	//输入节点代表的符号
	for (int i = 0; i < vertexNum; i++)
		cin >> vertexes[i];

	arcs = new int* [vertexNum];
	flag_arc = new Status * [vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		arcs[i] = new int[vertexNum];
		flag_arc[i] = new Status[vertexNum];
	}
	for (int i = 0; i < vertexNum; i++)
	{

		for (int j = 0; j < vertexNum; j++)
		{
			arcs[i][j] = 0;
			flag_arc[i][j] = UNVISIT;
		}
	}

}

inline AdjMatrixGraph::~AdjMatrixGraph()
{
	if (vertexes)
		delete[] vertexes;
	if (flag_arc)
		delete[] flag_arc;
	if (arcs)
		delete[] arcs;
}

inline void AdjMatrixGraph::Insert(int vex1, int vex2)
{
	if (vex1<0 || vex1>vexNum)
		return;
	arcs[vex1][vex2] = 1;
	arcNum++;
}

inline int AdjMatrixGraph::Firstvex(int vex)
{
	for (int i = 0; i < vexNum; i++)
	{
		if (arcs[vex][i] == 1)
			return i;
	}
	return Error;
}

inline int AdjMatrixGraph::Nextvex(int vex1, int vex2)
{
	for (int i = vex2 + 1; i < vexNum; i++)
	{
		if (arcs[vex1][i] == 1)
			return i;
	}
	return Error;
}

inline void AdjMatrixGraph::Display()
{
	if (vexNum != 0)
	{
		for (int i = 0; i < vexNum; i++)
		{
			cout << "| ";
			for (int j = 0; j < vexNum; j++)
				cout << arcs[i][j] << " ";
			cout << "|" << endl;
		}
	}
}

//--------------------------BFS---------------------------//
//--------------------------------------------------------//
//从vex开始遍历

inline void AdjMatrixGraph::BFS(int vex)
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

				for (int j = Firstvex(i); j != Error; j = Nextvex(i, j))
				{
					if (flag_vex[j] == UNVISIT)
					{
						cout << vertexes[i] << "-->" << vertexes[j] << '\n';
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

void AdjMatrixGraph::Recur_DFS()
{
	flag_vex = new Status[vexNum];
	for (int i = 0; i < vexNum; i++)
		flag_vex[i] = UNVISIT;

	for (int i = 0; i < vexNum; i++)
		if (flag_vex[i] == UNVISIT)
			DFS(i);
}

inline void AdjMatrixGraph::DFS(int vex)
{
	if (flag_vex[vex] == UNVISIT)
	{
		flag_vex[vex] = VISIT;
	}
	int j = Firstvex(vex);
	while (j != Error)
	{
		if (flag_vex[j] == UNVISIT)
		{
			cout << vertexes[vex] << "-->" << vertexes[j] << '\n';
			DFS(j);
		}
		else
			j = Nextvex(vex, j);
	}
}

//------------------------非递归DFS-------------------------//
//----------------------------------------------------------//
inline void AdjMatrixGraph::Without_Recur_DFS(int vex)
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
				//cout << vertexes[tmp] << ' ';
				flag_vex[tmp] = VISIT;

				int vex = tmp;
				for (tmp = Firstvex(i); tmp != Error; )
				{
					if (flag_vex[tmp] == UNVISIT)
					{
						cout << vertexes[vex] << "-->" << vertexes[tmp] << '\n';
						s.push(tmp);
						break;
					}
					else
						tmp = Nextvex(vex, tmp);
				}

			}
		}
	}
	cout << '\n';
}
//--------------------------------------------------------//
//------------------------TARJAN--------------------------//

int DFN[100];
int low[100];
int cnt = 1;
stack<int> st;
int flag[100];
int number = 0;
int length;
int input;

void AdjMatrixGraph::tarjan(int u)
{
	DFN[u] = low[u] = cnt++;
	st.push(u);
	flag[u] = 1;

	for (int v = 0; v < length; v++)
	{
		if (arcs[u][v])
		{
			if (!DFN[v])
			{
				tarjan(v);
				if (low[u] > low[v])
					low[u] = low[v];
			}
			else
			{
				if (low[u] > DFN[v] && flag[v])//这里为什么要用dfn来判断，用low不行吗？
					low[u] = DFN[v];
			}
		}
	}

	if (DFN[u] == low[u])
	{
		number++;
		do {
			input = st.top();
			st.pop();
			cout << vertexes[input] << ' ';
			flag[input] = 0;
		} while (input != u);
		cout << '\n';
	}
}

void AdjMatrixGraph::tarjan()
{
	length = vexNum;
	int i = 0;
	for (; i < length; i++)
	{
		bool flag = false;
		for (int j = 0; j < length; j++)
			if (arcs[i][j] != 0)
				flag = true;
		if (flag == true)
		{
			tarjan(i);
			break;
		}
	}
	cout << "强连通分量个数：" << number << '\n';
}

//------------------------拓扑排序------------------------//
//--------------------------------------------------------//

inline int AdjMatrixGraph::TopologicSort()
{
	int* Indegree = new int[vexNum];
	flag_vex = new Status[vexNum];
	for (int i = 0; i < vexNum; i++)
	{
		Indegree[i] = 0;
		flag_vex[i] = UNVISIT;
	}
	//求各个顶点的入度
	for (int j = 0; j < vexNum; j++)
	{
		for (int i = 0; i < vexNum; i++)
		{
			if (arcs[i][j] == 1)
				Indegree[j]++;
		}
	}

	stack<int> ss;
	int i = 0;
	for (i; i < vexNum; i++)
	{
		if (Indegree[i] == 0)
			ss.push(i);
	}
	int cnt = 0;
	while (!ss.empty())
	{
		i = ss.top();
		ss.pop();
		if (flag_vex[i] == UNVISIT)
		{
			cout << vertexes[i] << " ";
			flag_vex[i] = VISIT;
			++cnt;
		}
		for (int j = 0; j < vexNum; j++)
		{
			if (arcs[i][j] == 1 && flag_vex[j] == UNVISIT)
			{
				arcs[i][j] = 0;
				Indegree[j]--;
			}
			if (Indegree[j] == 0 && flag_vex[j] == UNVISIT)
				ss.push(j);
		}
	}
	if (cnt < vexNum)
		return Error;

	return OK;
}

inline void AdjMatrixGraph::FindInDegree(int *Indegree)
{
	for (int j = 0; j < vexNum; j++)
	{
		for (int i = 0; i < vexNum; i++)
		{
			if (arcs[i][j] == 1)
				Indegree[j]++;
		}
	}
}