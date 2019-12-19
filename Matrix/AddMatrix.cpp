#include"¾ØÕó.h"
int main()
{
	TSMatrix A,B;
	A.CreateMatrix();
	B.CreateMatrix();
	cout << "\n\n";
	cout << "A\n";
	A.Print();
	cout << "B\n";
	B.Print();
	
	TSMatrix C(A.mu, A.nu, A.tu + B.tu);
	AddMatrix(C, A, B);
	cout << "C\n";
	C.Print();
	return 0;
}

/*
4 4 5
1 1 12
1 4 -1
2 2 3
3 3 2
4 3 10

4 4 5
1 2 7
2 2 3
3 3 -2
4 1 9
4 4 8
*/