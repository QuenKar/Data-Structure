#include<iostream>
#include<stack>
#include<queue>
#include<vector>
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

	//拓扑排序
	int TopologicSort(vector<string>& vs);
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

//------------------------拓扑排序------------------------//
//--------------------------------------------------------//
/*
使用邻接矩阵来表示有向无环图。
关于邻接矩阵的类定义与相关函数在此不做赘述。
*/

inline int AdjMatrixGraph::TopologicSort(vector<string> &vs)
{
	int* Indegree = new int[vexNum];//保存各顶点入度的信息
	flag_vex = new Status[vexNum];//顶点标记数组
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

	queue<int> ss;//需要一个队列来进行遍历
	int i = 0;
	int cnt = 0;
	for (i; i < vexNum; i++)
	{
		if (Indegree[i] == 0)
		{
			flag_vex[i] = VISIT;
			ss.push(i);
			cnt++;
		}
	}
	//记录已输出的顶点个数，假如最后栈为空遍历结束
	
	while (!ss.empty())
	{
		int _size = ss.size();
		while (_size != 0)
		{
			i = ss.front();
			ss.pop();
			cout << vs[i] << " ";
			_size--;
	
			for (int j = 0; j < vexNum; j++)
			{
				if (arcs[i][j] == 1 && flag_vex[j] == UNVISIT)
				{
					Indegree[j]--;
					if (Indegree[j] == 0)
					{
						flag_vex[j] = VISIT;
						ss.push(j);
						cnt++;
					}
				}
			}
		}
		cout << '\n';
	}
	//但是cnt仍小于图的顶点个数，则证明图中有环。
	if (cnt < vexNum)
		return Error;

	return OK;
}
