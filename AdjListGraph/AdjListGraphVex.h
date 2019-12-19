#pragma once
#include"AdjListGraphArc.h"

typedef int ElemType;

struct AdjListDirGraphVex
{
	ElemType data;
	AdjListDirGraphArc* firstArc;

	AdjListDirGraphVex();
	AdjListDirGraphVex(ElemType VexValue, AdjListDirGraphArc* _firstArc = nullptr);
};


inline AdjListDirGraphVex::AdjListDirGraphVex():firstArc(nullptr)
{
}

inline AdjListDirGraphVex::AdjListDirGraphVex(ElemType VexValue, AdjListDirGraphArc* _firstArc)
{
	data = VexValue;
	firstArc = _firstArc;
}
