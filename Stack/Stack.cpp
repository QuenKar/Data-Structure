#include"Stack.h"

int main()
{
	Infix_change_Prefix();//中缀转前缀
	Infix_change_suffix();//中缀转后缀

	cout << '\n';
		
	return 0;
}

//a+b*c-d/e
//a+((b+c)*d)-e

//a+(b-c)*d+e/f
//a-b-c+d