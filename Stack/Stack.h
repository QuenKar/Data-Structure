#pragma once
#pragma once
#include<iostream>
#include<string>
#include<cstdio>
#include <map>
using namespace std;

typedef char Elemtype;

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

class stack
{
public:
	Elemtype* base;
	Elemtype* top;
	int stacksize;

	stack() { base = nullptr; top = nullptr; stacksize = 0; }
};

bool Initstack(stack* s)
{
	s->base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (!s->base)
		return false;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return true;
}

bool GetTop(stack* s, Elemtype& e)
{
	if (s->top != s->base)
	{
		e = *(s->top - 1);
		return true;
	}
	else
		return false;
}

bool Push(stack * s, Elemtype e)
{
	if (s->top - s->base >= s->stacksize)
	{
		s->base = (Elemtype*)realloc(s->base, (s->stacksize + STACK_INCREMENT) * sizeof(Elemtype));
		if (!s->base)
			return false;
		s->top = s->base + s->stacksize;
		s->stacksize += STACK_INCREMENT;
	}
	*(s->top)++ = e;
	return true;
}

Elemtype Pop(stack * s)
{
	Elemtype e;
	if (s->base == s->top)
		return false;
	--s->top;
	e = *(s->top);
	return e;
}

//???
void stack_Destroy(stack * s)
{
	free(s);
}

bool stack_Empty(stack * s)
{
	if (s->base == s->top)
		return true;
	else
		return false;
}

void output(stack * s)
{
	Elemtype* r = s->base;
	while (r != s->top)
	{
		cout << r;
		r++;
	}
}

void stack_Clear(stack * s)
{
	s->top = s->base;
}

//栈的应用
void Infix_change_Prefix()
{
	string s;  
	cin >> s;

	//定义运算符优先级。9为最高级运算符，1为最低级
	map< char, int> operators;
	operators.clear();
	operators['('] = 9;
	operators[')'] = 0;
	operators['+'] = 1;
	operators['-'] = 1;
	operators['*'] = 2;
	operators['/'] = 2;

	stack s1;//保存运算数
	Initstack(&s1);

	stack s2;//保存运算符
	Initstack(&s2);

	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (s[i]>='a'&&s[i]<='z')
		{
			Push(&s1, s[i]);
		}
		else
		{
			if (stack_Empty(&s1))
				Push(&s1, s[i]);
			else
			{
				if (s[i] == ')')
					Push(&s2, s[i]);
				else if(s[i]=='(')
				{
					while (!stack_Empty(&s2))
					{
						if (*(s2.top-1) == ')')
						{
							Pop(&s2);
							break;
						}
						else
						{
							Push(&s1, Pop(&s2));
						}
					}
				}
				else
				{
					while (!stack_Empty(&s2))
					{
						if (operators[*(s2.top - 1)] <= operators[s[i]])
						{
							break;
						}
						else
						{
							Push(&s1, Pop(&s2));
						}
					}
					Push(&s2, s[i]);
				}
			}
		}
	}
	while (!stack_Empty(&s2))
	{
		Push(&s1, Pop(&s2));
	}

	while (!stack_Empty(&s1))
	{
		Elemtype e=Pop(&s1);
		cout << e << ' ';
	}
}

//a+b*c-d/e

void Infix_change_suffix()
{
	string s;
	cin >> s;

	map< char, int> operators;
	operators.clear();
	operators['('] = 0;
	operators[')'] = 9;
	operators['+'] = 1;
	operators['-'] = 1;
	operators['*'] = 2;
	operators['/'] = 2;

	stack s1;//保存运算数
	Initstack(&s1);
	
	stack s2;//保存运算符
	Initstack(&s2);

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			Push(&s1, s[i]);
		}
		else
		{
			if (stack_Empty(&s2) && s[i] != '(')//!!!
			{
				Push(&s2, s[i]);
				continue;
			}

			if (s[i] == '(')
			{
				Push(&s2, s[i]);
				continue;
			}
			if (s[i] == ')')
			{
				while (!stack_Empty(&s2))
				{
					if (*(s2.top - 1) == '(')
					{
						Pop(&s2);
						break;
					}
					else
					{
						Push(&s1, Pop(&s2));
					}
				}	
			}

			else
			{
				while (!stack_Empty(&s2))
				{
					if (operators[s[i]] > operators[*(s2.top - 1)])
					{
						break;
					}
					else
					{
						Push(&s1, Pop(&s2));
					}
				}
				Push(&s2, s[i]);
			}
		}
		
	}
	while (!stack_Empty(&s2))
	{
		Push(&s1, Pop(&s2));
	}

	for (Elemtype* r = s1.base; r != s1.top; r++)
	{
		cout << *r << ' ';
	}
}

