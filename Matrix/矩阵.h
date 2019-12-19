#include<iostream>
using namespace std;

#define MAXSIZE 1004

class Triple
{
public:
	int row, column;//保存行列
	int e;//保存值
	Triple() { row = 0; column = 0; e = 0; }
	Triple& operator=(const Triple& T)
	{
		if (this != &T)
		{
			row = T.row;
			column = T.column;
			e = T.e;
		}
		return *this;
	}
};

class TSMatrix
{
public:
	TSMatrix() { mu = 0; nu = 0; tu = 0; data = nullptr; num = nullptr; cpot = nullptr; }
	TSMatrix(int m, int n, int t) 
	{ 
		mu = m; nu = n; tu = t;
		data = new Triple[tu];
		num = nullptr;
		cpot = nullptr;
	}
	TSMatrix(const TSMatrix& T);

	
	void CreateMatrix() { _CreateMatrix(); _cpot(); }
	friend void AddMatrix(TSMatrix& C,const Triple& A, const Triple& B);
	void Print();

protected:
	void _CreateMatrix();
	void _cpot();
public:
	Triple *data;
	int* num;
	int* cpot;
	int mu, nu, tu;//行数，列数，非零元个数
};

inline TSMatrix::TSMatrix(const TSMatrix& T)
{
	if (data)
		delete[] data;
	
	if (num)
		delete[] num;

	mu = T.mu; nu = T.nu; tu = T.tu;

	data = new Triple[tu];
	num = new int[mu+1];
	cpot = new int[mu + 1];
	for (int i = 0; i < tu; i++)
		data[i] = T.data[i];
	for (int i = 0; i < mu+1; i++)
		num[i] = T.num[i];
	for (int i = 0; i < mu + 1; i++)
		cpot[i] = T.cpot[i];
}

void TSMatrix::_CreateMatrix()
{
	int m, n, t;
	cin >> m >> n >> t;
	mu = m; nu = n; tu = t;
	data = new Triple[t];
	num = new int[mu+1];//记录每一行数的个数
	for (int i = 0; i < mu + 1; i++)
		num[i] = 0;

	int r, c, e;
	for (int i = 0; i < t; i++)
	{
		cin >> r >> c >> e;
		data[i].row = r;
		data[i].column = c;
		data[i].e = e;
		num[data[i].row]++;//记录每一行数的个数
	}
}

inline void TSMatrix::_cpot()
{
	cpot = new int[mu + 1];
	cpot[0] = 0; cpot[1] = 0;
	for (int i = 2; i < mu + 1; i++)
		cpot[i] = cpot[i - 1] + num[i - 1];
}
void AddMatrix(TSMatrix& C ,const TSMatrix& A, const TSMatrix& B)
{
	
	int i = 0, j = 0;//分别记录A与B的下标
	int k = 0;
	while (k < A.tu + B.tu && i < A.tu && j < B.tu)
	{
		if (A.data[i].row < B.data[j].row)
		{
			int pos = A.cpot[A.data[i].row+1];//记录下一行的位置
			for (; i < pos; i++)
			{
				C.data[k] = A.data[i];
				k++;
			}
		}
		else if (A.data[i].row > B.data[j].row)
		{
			int pos = B.cpot[B.data[j].row];
			for (; j < pos; j++)
			{
				C.data[k] = A.data[j];
				k++;
			}
		}
		else if(A.data[i].row = B.data[j].row)
		{
			if (A.data[i].column < B.data[j].column)
			{
				C.data[k] = A.data[i];
				k++; i++;
			}
			else if(A.data[i].column > B.data[j].column)
			{
				C.data[k] = B.data[j];
				k++; j++;
			}
			else if(A.data[i].column = B.data[j].column)
			{
				C.data[k].e = A.data[i].e + B.data[j].e;
				if (C.data[k].e != 0)
				{
					C.data[k].row = A.data[i].row;
					C.data[k].column = A.data[i].column;
					i++; j++; k++;
				}
				else
				{
					i++; j++;
				}
			}
		}
	}
	if (i < A.tu)
	{
		for (; i < A.tu; i++)
			C.data[k] = A.data[i];
	}
	if (j < B.tu)
	{
		for (; j < B.tu; j++)
			C.data[k] = B.data[j];
	}
}

inline void TSMatrix::Print()
{
	for (int i = 0; i < tu; i++)
	{
		if(data[i].e!=0)
			cout << data[i].row << ' ' << data[i].column << ' ' << data[i].e << '\n';
	}
	cout << "\n\n";
}





//
//bool TransposeSMatrix_1(TSMatrix& M, TSMatrix& T)
//{
//	T.mu = M.nu;
//	T.nu = M.mu;
//	T.tu = M.tu;
//	if (T.tu)
//	{
//		int q = 1;
//		for (int col = 1; col <= M.nu; col++)
//		{
//			for (int p = 1; p <= M.tu; ++p)
//			{
//				if (M.data[p].column == col)
//				{
//					T.data[p].row = M.data[q].column;
//					T.data[p].column = M.data[q].row;
//					T.data[p].e = M.data[q].e;
//					
//					q++;
//				}
//			}
//		}
//	}
//	return true;
//}
//
//
//int num[MAXSIZE] = { 0 };
//int cpot[MAXSIZE] = { 0 };
//bool TransposeSMatrix_2(TSMatrix& M, TSMatrix& T)//T代表转置矩阵
//{
//	T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
//
//	if (T.tu)
//	{
//		for (int col = 1; col <= M.nu; col++)
//			num[col] = 0;
//
//		for (int t = 1; t < M.tu; t++)
//		{
//			++num[M.data[t].column];
//		}
//		cpot[1] = 1;
//		for (int col = 2; col <= M.nu; col++)
//			cpot[col] = cpot[col - 1] + num[col - 1];
//
//		for (int p = 1; p <= M.tu; p++)
//		{
//			int col = M.data[p].column;
//			int q = cpot[col];
//
//			T.data[q].column = M.data[p].row;
//			T.data[q].row = M.data[p].column;
//			T.data[q].e = M.data[p].e;
//			
//			++cpot[col];
//		}
//	}
//	return true;
//}