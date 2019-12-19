#pragma once
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
class String
{
public:
	char* ch;
	int length;

	String() { ch = nullptr; length = 0; }
	String(const char* chars);
	String(const String&); //不要总是忘记写
	~String();
	
	void StrInsert(int pos, String T);//在指定位置插入字符串T
	int StrLength();
	friend int StrCompare(String s1, String s2);//字符串比较
	void ClearStr();
	friend void Connect(String& S, String& s1, String& s2);
	String SubString(int pos, int len);//从某个位置开始返回长度为len的字符串

	String& operator=(const String& s);
	friend ostream& operator<<(ostream& os, String& s);

	int Index(const String& T, int pos);
	int KMP(const String& T);
	void SunDay(const String& T);
};

String::String(const char* chars)
{
	ch = new char[strlen(chars)+1];
	if (ch)
		strcpy_s(ch,sizeof(char)*(strlen(chars)+1), chars);

	length = strlen(chars);
}

inline String::String(const String& s)
{
	if (!s.ch)
	{
		return;
	}

	ch = new char[s.length + 1];
	strcpy_s(ch, sizeof(char) * (s.length + 1), s.ch);

	length = s.length;

}

inline String::~String()
{
	delete[] ch;
	ch = nullptr;
}


int StrCompare(String s1, String s2)
{
	for (int i = 0; i < s1.length && i < s2.length; i++)
	{
		if (s1.ch[i] != s2.ch[i])
		{
			return s1.ch[i] - s2.ch[i];
		}
	}
	return s1.length - s2.length;
}

inline String& String::operator=(const String& s)
{
	if (this == &s)
	{
		return *this;
	}

	ClearStr();

	ch = new char[s.length + 1];
	if(ch)
		strcpy_s(ch,sizeof(char)*(s.length + 1),s.ch);

	length = s.length;

	return *this;
}

inline ostream& operator<<(ostream& os, String& s)
{
	if (s.ch)
		os << s.ch;
	else
		os << "";

	return os;
}
//清空字符串
inline void String::ClearStr()
{
	if (ch)
	{
		delete[] ch;
		length = 0;
	}
}

//返回字符串长度
inline int String::StrLength()
{
	return length;
}

//返回从某字符开始长度为n的字符串
inline String String::SubString(int pos, int len)
{
	if (pos<1 || pos>length || len<0 || len>length - pos + 1)
	{
		return String("");
	}

	String s;
	s.ch = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		s.ch[i] = ch[pos - 1 + i];
	}

	s.ch[len] = '\0';
	s.length = len;

	return s;
}
//连接两个字符串
inline void Connect(String& S, String& s1, String& s2)//为什么一定要传引用啊，日了狗了
{

	S.ch = new char[s1.length + s2.length + 1];
	S.length = s1.length + s2.length;

	if (S.ch)
	{
		strcpy_s(S.ch, sizeof(char) * (S.length + 1), s1.ch);
		strcat_s(S.ch, sizeof(char) * (S.length + 1), s2.ch);
	}
}

//在pos之前插入字符串
inline void String::StrInsert(int pos, String T)
{
	if (pos<1 || pos>length)
		return;

	if (T.length)
	{
		int len = length + T.length;
		char* ccc = new char[len + 1];
		int i = 0;
		for (; i < pos-1; i++)
		{
			ccc[i] = ch[i];
		}

		for (char* r = T.ch; *r != '\0'; r++)
		{
			ccc[i] = *r;
			i++;
		}
		for (; i < len; i++)
		{
			ccc[i] = ch[i - T.length];
		}
		ccc[len] = '\0';

		ClearStr();
		ch = new char[len + 1];
		strcpy_s(ch, sizeof(char) * (len + 1), ccc);
		length = len;
	}
}
//求子串位置的定位函数
inline int String::Index(const String& T, int pos)
{
	//返回子串T在主串第pos个字符之后的位置，若不存在就返回0.
	int i = pos, j = 0;

	while (i < length && j < T.length)
	{
		if (ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= T.length) 
		return i - T.length+1;
	else 
		return 0;
}

void get_next(const String&T,int next[])
{
	int i = 0;
	next[i] = -1;
	int k = -1;

	while (i < T.length)
	{
		if (k == -1 || T.ch[i] == T.ch[k])
		{
			++i; ++k;
			if (T.ch[i] != T.ch[k])
				next[i] = k;
			else
				next[i] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

int String::KMP(const String& T)
{
	//返回子串T在主串的位置，若不存在就返回0.

	int i = 0, j = 0;
	int* next = new int[T.length];
	get_next(T, next);

	while (i < length && j < T.length)
	{
		if (j == -1 || ch[i] == T.ch[j])
		{
			++i; ++j;
		}
		else
		{
			j = next[j];
		}
	}
	if (j >= T.length)
	{
		return i - T.length + 1;
	}
	else
		return 0;
}

void Delete_str(String* S, const String& T)
{
	char* c = S->ch;
	
	while (1)
	{
		int i = S->KMP(T);
		if (i == 0)
			break;
		for (int j = i + T.length - 1; j < S->length; j++)
		{
			S->ch[j - T.length] = S->ch[j];
		}
		S->length -= T.length;
		S->ch[S->length] = '\0';
	}
}

void Instead_str(String* S, const String& T1, const String& T2)//T1表示被替换的字符串，T2表示替换的字符串
{
	if (!S->ch)
		return;
	
	while (1)
	{
		int n = S->KMP(T1);
		if (n == 0)
			break;
		else
		{
			if (T1.length > T2.length)
			{
				const int len = T1.length - T2.length;//需要挪动的距离
				//挪动操作
				int i = n + T1.length - 1;
				for (; S->ch[i] != '\0'; i++)
				{
					S->ch[i - len] = S->ch[i];
				}
				S->ch[i - len] = '\0';
				//赋值
				for (int j = 0; T2.ch[j] != '\0'; j++)
				{
					S->ch[j + n - 1] = T2.ch[j];
				}

				char* c = new char[S->length - len + 1];
				strcpy_s(c, sizeof(char) * (S->length - len + 1), S->ch);
				char* temp = S->ch;
				S->ch = c;
				delete[] temp;
				S->length -= len;
				S->ch[S->length] = '\0';
			}
			else if (T1.length == T2.length)
			{
				const int len = 0;//不需要移动

				for (int j = 0; T2.ch[j] != '\0'; j++)
				{
					S->ch[j + n - 1] = T2.ch[j];
				}
			}
			else if (T1.length < T2.length)
			{
				const int len = T2.length - T1.length;//需要挪动的距离
				char* c = new char[S->length + len + 1];
				strcpy_s(c, sizeof(char) * (S->length + len + 1), S->ch);
				char* temp = S->ch;
				S->ch = c;
				delete[] temp;

				int end = 0;
				for (; S->ch[end] != '\0'; end++);//找到最后一个字符串的下一个位置
				//挪动操作
				for (int i = end - 1; i != n + T1.length - 2; i--)
				{
					S->ch[i + len] = S->ch[i];
				}
				S->length += len;
				S->ch[S->length] = '\0';
				//赋值
				for (int j = 0; T2.ch[j] != '\0'; j++)
				{
					S->ch[j + n - 1] = T2.ch[j];
				}
			}
		}
	}
}


String Const_End("quit");

void Editor()
{
	vector<String> v;//存放每一行的字符串
	cout << "Please Input your Article:" << endl;
	//输入操作
	while (1)
	{
		char c[30];
		cin.getline(c, 30);
		String s(c);
		if (!StrCompare(c, Const_End.ch))//如果输入一行为quit则结束输入
			break;
		else
		{
			v.push_back(s);
		}
	}

	cout << "This is your Input:" << endl;
	for (auto b = v.begin(); b != v.end(); b++)
	{
		cout << (*b).ch << endl;
	}

	cout << endl;
	cout << "Please choose the following operation:" << endl;
	char ch;
	while (1)
	{
		cout << "1.Insert----2.Delete----3.Instead_Text----4.q to quit" << endl;
		cout << "Please Enter the Number:" << endl;
		cin >> ch;
		switch (ch)
		{
		case '1': 
		{
			cout << "请输入插入位置（第几行的第几个字符）:" << endl;
			int row;
			cin >> row;
			int col;
			cin >> col;
			char* cc = new char[30];
			cin >> cc;
			String temp(cc);

			v[row-1].StrInsert(col, temp);
			//显示输出
			for (auto b = v.begin(); b != v.end(); b++)
			{
				cout << (*b).ch << endl;
			}
			break;
		}
		case '2':
		{
			cout << "请输入要删除的字符串:" << endl;
			char* cc = new char[30];
			cin >> cc;
			String temp(cc);
			for (auto i = v.begin(); i != v.end(); i++)
			{
				Delete_str(&(*i), temp);
			}
			//显示输出
			for (auto b = v.begin(); b != v.end(); b++)
			{
				cout << (*b).ch << endl;
			}
			break;
		}
		case '3':
		{
			cout << "请输入需要被替换的文本:" << endl;
			char* c1 = new char[30];
			cin >> c1;
			String T1(c1);
			cout << "请输入替换文本:" << endl;
			char* c2 = new char[30];
			cin >> c2;
			String T2(c2);

			for (auto i = v.begin(); i != v.end(); i++)
			{
				Instead_str(&(*i), T1, T2);
			}
			//显示输出
			for (auto b = v.begin(); b != v.end(); b++)
			{
				cout << (*b).ch << endl;
			}
			break;
		}
		case '4':
			exit(0);
		default:
			cout << "Input is EEEErrrrror!!!,Please Enter again:" << endl;
			break;
		}
	}
}