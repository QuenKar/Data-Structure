#include"AdjMatrixGraph.h"


int main()
{
	vector<string> vs{ "���������","���Դ���","΢��ԭ��","c����","��ɢ��ѧ","���","���ݽṹ","���ݿ�","����ϵͳ","����ԭ��" };
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