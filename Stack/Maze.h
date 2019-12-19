#pragma once

#include<iostream>
using namespace std;

#define MAXSIZE 1000
//迷宫地图
int Maze[10][10] = 
{ 
1,1,1,1,1,1,1,1,1,1,
1,0,0,1,0,0,0,1,0,1,
1,0,0,1,0,0,0,1,0,1,
1,0,0,0,0,1,1,0,0,1,
1,0,1,1,1,0,0,0,0,1,
1,0,0,0,1,0,0,0,0,1,
1,0,1,0,0,0,1,0,0,1,
1,0,1,1,1,0,1,1,0,1,
1,1,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1
};
//作为记录走过的地方
int flag[10][10] = 
{ 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };//四个方向，上右下左顺序

int const_row = 10;
int const_column = 10;
int start_pos = Maze[1][1];
int end_pos = Maze[8][8];

template <typename T>
class Stack
{
public:
	T* base;
	T* top;

	Stack() 
	{
		base = new T[MAXSIZE];
		top = base;
	}

	bool EmptyStack();
	void PushStack(T e);
	T Pop();
	bool ClearStack();

	~Stack() { delete[] base; top = nullptr; }
};


template <typename T>
inline bool Stack<T>::EmptyStack()
{
	if (top == base)
		return true;
	else
		return false;
}

template <typename T>
inline void Stack<T>::PushStack(T e)
{
	if (top - base != MAXSIZE - 1)
	{
		*top = e;
		top++;
	}
}

template <typename T>
inline T Stack<T>::Pop()
{
	if (!(this->EmptyStack()))
	{
		T e = *(top - 1);
		top--;
		return e;
	}
}

template <typename T>
inline bool Stack<T>::ClearStack()
{
	top = base;
	return true;
}

class Pos
{
public:
	int row;
	int column;
	int di;

	Pos() { row = column = di = 0; }
	Pos(int _row, int _column) :row(_row), column(_column) { di = 0; }
	void print() { cout << '(' << row << ',' << column << ')' << ' '; }
};

//输入迷宫首地址，终点位置(只能找到一条路)
bool GetPath(int maze[][10], int end_row, int end_column, Stack<Pos>* s, Pos start)
{
	s->PushStack(start);
	while (!s->EmptyStack())
	{
		Pos cur = *(s->top-1);
		maze[cur.row][cur.column] = 2;
		if (cur.row == end_row && cur.column == end_column)
		{
			for (Pos* r = s->base; r != s->top; r++)
			{
				r->print();
			}
			return true;
		}

		//探寻四个方向
		//向右
		if (cur.column + 1 <= const_column && maze[cur.row][cur.column + 1] == 0)
		{
			cur.column += 1;
			s->PushStack(cur);
			continue;
		}
		//向下
		if (cur.row + 1 <= const_row && maze[cur.row + 1][cur.column] == 0)
		{
			cur.row += 1;
			s->PushStack(cur);
			continue;
		}
		//向左
		if (cur.column >= 0 && maze[cur.row][cur.column - 1] == 0)
		{
			cur.column -= 1;
			s->PushStack(cur);
			continue;
		}
		//向上
		if (cur.row >= 0 && maze[cur.row - 1][cur.column] == 0)
		{
			cur.row -= 1;
			s->PushStack(cur);
			continue;
		}
		s->Pop();
	}
	return false;
}

void ouput(int maze[][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << maze[i][j]<<' ';
		}
		cout << '\n';
	}
}

//显示所有路径
Stack<Pos> Path;
Stack<Pos> temp;
int cnt = 0;
void GetPath2(int row, int col,int end_row,int end_column)
{
	
	if (row == end_row && col == end_column)
	{
		int show_maze[10][10] =
		{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,1,0,0,0,1,0,1,
		1,0,0,1,0,0,0,1,0,1,
		1,0,0,0,0,1,1,0,0,1,
		1,0,1,1,1,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,1,
		1,0,1,0,0,0,1,0,0,1,
		1,0,1,1,1,0,1,1,0,1,
		1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1
		};

		cnt++;
		Path.PushStack(Pos(row, col));
		while (!Path.EmptyStack())
		{
			Pos s = Path.Pop();
			temp.PushStack(s);
		}
		
		cout << "The " << cnt << " way:"<<'\n';
		while (!temp.EmptyStack())
		{
			
			Pos s = temp.Pop();
			cout << '(' << s.row << ',' << s.column << ')' << ' ';
			show_maze[s.row][s.column] = 7;
			Path.PushStack(s);
		}
		cout << '\n';
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << show_maze[i][j]<<' ';
			}
			cout << '\n';
		}
		cout << endl;
		
		Path.Pop();
		return;
	}
	if (row >= const_row || row < 0 || col >= const_column || col < 0)
	{
		return;
	}
	if (flag[row][col] == 1)
		return;
	if (Maze[row][col] != 0)
		return;

	Path.PushStack(Pos(row, col));
	flag[row][col] = 1;

	for (int i = 0; i < 4; i++)
	{
		int xrow = row + dir[i][0];
		int xcol = col + dir[i][1];

		GetPath2(xrow, xcol, end_row, end_column);
	}

	flag[row][col] = 0;
	Path.Pop();
	return;
}