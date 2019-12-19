#include"Kruskal.h"

int main()
{

	int adjMat[Vexcounts][Vexcounts] = { INT_MAX };
	AdjMatrix(adjMat);
	cout << "Kruskal:\n";
	Kruskal(adjMat);

	return 0;
}