#include"AVL.h"

int main()
{
	AVL_Tree A;
	const int a[7] = { 13 ,24, 37 ,90, 52, 99 ,61 };
	for (int i = 0; i < 7; i++)
		A.Insert(a[i]);
	A.Inorder();
	A.PreOrder();
	
	cout << "\nÉ¾³ý37\n";
	A.Delete(37);
	A.Inorder();
	A.PreOrder();

	cout << "\nÉ¾³ý52\n";
	A.Delete(52);
	A.Inorder();
	A.PreOrder();
	return 0;
}

//13 24 37 90 52 99 61