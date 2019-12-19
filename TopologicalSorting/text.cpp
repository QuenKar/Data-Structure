#include"AdjMatrixGraph.h"


int main()
{
	vector<string> vs{ "计算机导论","线性代数","微机原理","c语言","离散数学","汇编","数据结构","数据库","操作系统","编译原理" };
	AdjMatrixGraph G2(10);
	G2.Insert(0, 2);
	G2.Insert(0, 3);
	G2.Insert(0, 4);
	G2.Insert(1, 4);
	G2.Insert(3, 5);
	G2.Insert(3, 6);
	G2.Insert(3, 7);
	G2.Insert(4, 6);
	G2.Insert(6, 7);
	G2.Insert(6, 8);
	G2.Insert(5, 8);
	G2.Insert(6, 9);
	G2.Insert(5, 9);
	
	G2.Display();
	G2.TopologicSort(vs);

	return 0;
}

//1 2 3 4 5 6 7 8 9 10