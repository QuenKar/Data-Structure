#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define Vexcounts 6
#define INI_MAX 10000

char vextex[] = { 'A','B','C','D','E','F' };

struct node
{
	unsigned int data;
	unsigned int leastcost;
}closedge[Vexcounts];

struct Arc
{
	unsigned int u;
	unsigned int v;
	unsigned int cost;
};

void AdjMatrix(unsigned int adjMat[][Vexcounts])
{
	for (int i = 0; i < Vexcounts; i++)
	{
		for (int j = 0; j < Vexcounts; j++)
		{
			adjMat[i][j] = INI_MAX;
		}
	}
	adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
	adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
	adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; 
	adjMat[2][4] = 6; adjMat[2][5] = 4;
	adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
	adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
	adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;
}
/*----------------------------Prim----------------------------*/
/*----------------------------Prim----------------------------*/
/*----------------------------Prim----------------------------*/
int MinArc(node* closedge)
{
	int min = INI_MAX;
	int index = -1;
	for(int i=0;i<Vexcounts;i++)
		if (closedge[i].leastcost < min && closedge[i].leastcost != 0)
		{
			min = closedge[i].leastcost;
			index = i;
		}
	return index;
}

void MinSpanTree_Prim(unsigned int adjMat[][Vexcounts], unsigned int s)
{
	for (int i = 0; i < Vexcounts; i++)
		closedge[i].leastcost = INI_MAX;
	closedge[s].data = s;
	closedge[s].leastcost = 0;

	for (int i = 0; i < Vexcounts; i++)
	{
		if (i != s)
		{
			closedge[i].data = s;
			closedge[i].leastcost = adjMat[s][i];
		}
	}
	for (int e = 1; e <= Vexcounts - 1; e++)
	{
		int k = MinArc(closedge);
		cout << vextex[closedge[k].data] << " -- " << vextex[k]
			<< "	" << adjMat[k][closedge[k].data] << endl;
		closedge[k].leastcost = 0;
		for (int i = 0; i < Vexcounts; i++)
		{
			if (adjMat[k][i] < closedge[i].leastcost)
			{
				closedge[i].data = k;
				closedge[i].leastcost = adjMat[k][i];
			}
		}
	}
}
