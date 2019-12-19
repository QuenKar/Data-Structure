#pragma once

#include<iostream>
#include<cstdio>

using namespace std;
typedef int Elemtype;

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
//1.数制转换
void conversion()
{
	stack s;
	Initstack(&s);
	Elemtype n,i;//n为数，i为要转换的数制
	cin >> n;
	cin >> i;
	while (n)
	{
		Push(&s, n % i);
		n /= i;
	}
	while (!stack_Empty(&s))
	{
		Elemtype e;
		e = Pop(&s);
		cout << e;
	}
}