#pragma once
#include<iostream>
#include<map>
#include<iomanip>
using namespace std;

map<char, string> HuffCode;

struct HuffmanNode
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
	HuffmanNode() { weight = 0; parent = 0; lchild = 0; rchild = 0; }
	HuffmanNode(int w, int p, int lc, int rc)
		:weight(w), parent(p), lchild(lc), rchild(rc) {}
};

typedef HuffmanNode HuffmanTree;

void Selete(HuffmanTree* HT, int len, int& s1, int& s2)
{
	s1 = s2 = 0;
	int min1 = INT_MAX;//最小
	int min2 = INT_MAX;//次小

	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0)
		{
			if (HT[i].weight < min1)
			{
				min2 = min1;
				s2 = s1;
				min1 = HT[i].weight;
				s1 = i;
			}
			else if ((HT[i].weight >= min1) && (HT[i].weight < min2))
			{
				min2 = HT[i].weight;
				s2 = i;
			}
		}
	}
}


void HuffmanCoding(HuffmanTree* HT, int* w, int n)
{
	if (n <= 1)
		return;
	int m = n * 2 - 1;
	HT = new HuffmanNode[m + 1];//从1开始存数
	for (int p = 1; p <= n; p++, w++)
		HT[p] = { *w,0,0,0 };
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Selete(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s2;
		HT[i].rchild = s1;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	for (int i = 1; i <= n; i++)
	{
		string code;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				code = '0' + code;
			else
				code = '1' + code;
		}
		HuffCode[i - 1 + 'A'] = code;
	}
}

void display(int w[])
{
	cout << left << setw(12) << "node" << setw(12) << "Weight" << setw(12) << "HuffmanCode" << '\n';
	int i = 0;
	for (auto it = HuffCode.begin(); it != HuffCode.end(); ++it, ++i)
		cout << left << setw(12) << it->first << setw(12) << w[i] << setw(12) << it->second << '\n';
}