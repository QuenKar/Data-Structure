#include"AdjListDirGraph.h"

int main()
{
	int a[6] = { 1,2,3,4,5,6 };
	AdjListDirGraph G(a,6);
	G.InsertArc(1, 0);
	G.InsertArc(5, 0);
	G.InsertArc(4, 0);
	G.InsertArc(5, 4);
	G.InsertArc(5, 1);
	G.InsertArc(1, 3);
	G.InsertArc(3, 2);
	G.InsertArc(2, 1);
	G.InsertArc(2, 5);
	G.InsertArc(3, 4);

	G.Display();
	cout << "��ȱ�����\n";
	G.BFS(0);
	cout << "�ݹ���ȱ�����\n";
	G.Recur_DFS();
	G.Display();
	cout << "�ǵݹ���ȱ�����\n";
	G.Without_Recur_DFS(0);

	return 0;
}