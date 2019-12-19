#pragma once
#include<iostream>
using namespace std;

typedef int ElemType;

struct AdjListDirGraphArc
{
	int adjvex;
	AdjListDirGraphArc* nextArc;

	AdjListDirGraphArc();
	AdjListDirGraphArc(int _adjVex, AdjListDirGraphArc* _nextArc = nullptr);
};


inline AdjListDirGraphArc::AdjListDirGraphArc():adjvex(-1),nextArc(nullptr)
{

}


inline AdjListDirGraphArc::AdjListDirGraphArc(int _adjVex, AdjListDirGraphArc* _nextArc)
{
	adjvex = _adjVex;
	nextArc = _nextArc;
}
