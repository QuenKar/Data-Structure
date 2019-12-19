#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define Vexcounts 6

char vextex[] = { 'A','B','C','D','E','F' };

struct Arc
{
	int u;
	int v;
	int weight;
	Arc(int _u,int _v,int _weight):u(_u),v(_v),weight(_weight){}
};

void AdjMatrix(int adjMat[][Vexcounts])
{
	for (int i = 0; i < Vexcounts; i++)
	{
		for (int j = 0; j < Vexcounts; j++)
		{
			adjMat[i][j] = INT_MAX;
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

//Kruskal
void AssignArc(int adjMat[][Vexcounts], vector<Arc>& vA)
{
	for (int i = 0; i < Vexcounts; i++)
	{
		for (int j = 0; j < Vexcounts; j++)
		{
			if (adjMat[i][j] != INT_MAX)
			{
				vA.push_back(Arc(i, j, adjMat[i][j]));
			}
		}
	}
}
//从小到大排列
bool cmp(Arc a, Arc b)
{
	return a.weight < b.weight;
}
//判断顶点u与v是否在一个集合内
bool FindUnion_Set(int u, int v, vector<int>& union_set)
{
	if (union_set[u] != union_set[v])
	{
		int value = union_set[v];
		for (int i = 0; i < union_set.size(); i++)
		{
			if (union_set[i] == value)
				union_set[i] = union_set[u];
		}
		return true;
	}
	else
		return false;
}

void Kruskal(int adjMat[][Vexcounts])
{
	vector<Arc> vA;
	AssignArc(adjMat, vA);
	sort(vA.begin(), vA.end(), cmp);

	vector<int> Union_set(Vexcounts);
	for (int i = 0; i < Vexcounts; i++)
		Union_set[i] = i;
	
	for (int i = 0; i < vA.size(); i++)
	{
		int _u = vA[i].u;
		int _v = vA[i].v;
		if (FindUnion_Set(_u, _v, Union_set))
		{
			cout << vextex[_u] << " -- "
				<< vextex[_v] << "	" << adjMat[_u][_v] << '\n';
		}
	}
}