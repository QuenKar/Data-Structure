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

	//��������
	int TopologicSort(vector<string>& vs);
private:

	char* vertexes;//��¼����
	int** arcs;//��¼��
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

	//����ڵ����ķ���
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

//------------------------��������------------------------//
//--------------------------------------------------------//
/*
ʹ���ڽӾ�������ʾ�����޻�ͼ��
�����ڽӾ�����ඨ������غ����ڴ˲���׸����
*/

inline int AdjMatrixGraph::TopologicSort(vector<string> &vs)
{
	int* Indegree = new int[vexNum];//�����������ȵ���Ϣ
	flag_vex = new Status[vexNum];//����������
	for (int i = 0; i < vexNum; i++)
	{
		Indegree[i] = 0;
		flag_vex[i] = UNVISIT;
	}
	//�������������
	for (int j = 0; j < vexNum; j++)
	{
		for (int i = 0; i < vexNum; i++)
		{
			if (arcs[i][j] == 1)
				Indegree[j]++;
		}
	}

	queue<int> ss;//��Ҫһ�����������б���
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
	//��¼������Ķ���������������ջΪ�ձ�������
	
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
	//����cnt��С��ͼ�Ķ����������֤��ͼ���л���
	if (cnt < vexNum)
		return Error;

	return OK;
}
