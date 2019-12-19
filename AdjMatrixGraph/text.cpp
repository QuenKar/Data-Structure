#include"AdjMatrixGraph.h"


int main()
{
	AdjMatrixGraph G(6);
	G.Insert(1, 0);
	G.Insert(5, 0);
	G.Insert(4, 0);
	G.Insert(5, 4);
	G.Insert(5, 1);
	G.Insert(1, 3); 
	G.Insert(3, 2);
	G.Insert(2, 1);
	G.Insert(2, 5);
	G.Insert(3, 4);

	G.Display();
	cout << "广度遍历：\n";
	G.BFS(0);
	cout << "递归深度遍历：\n";
	G.Recur_DFS();
	cout << "非递归深度遍历：\n";
	G.Without_Recur_DFS(0);
	
	G.tarjan();
	//G.DirTree();

	/*AdjMatrixGraph G2(12);
	G2.Insert(0, 3);
	G2.Insert(0, 1);
	G2.Insert(0, 2);
	G2.Insert(0, 11);
	G2.Insert(8, 9);
	G2.Insert(9, 11);
	G2.Insert(8, 10);
	G2.Insert(8, 11);
	G2.Insert(10, 5);
	G2.Insert(5, 7);
	G2.Insert(3, 4);
	G2.Insert(4, 6);
	G2.Insert(1, 2);
	G2.Insert(2, 6);
	G2.Insert(2, 4);
	G2.Insert(2, 7);
	G2.Display();
	G2.TopologicSort();*/

	return 0;
}

//1 2 3 4 5 6
//1 2 3 4 5 6 7 8 9 a b c 