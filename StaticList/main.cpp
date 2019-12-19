#include"staticList.h"
#include<fstream>
int main()
{
	fstream file("test.txt");
	
	int len;
	file >> len;
	int* a = new int[len];
	int data;
	int i = 0;
	while (!file.eof())
	{
		file >> data;
		a[i] = data;
		i++;
	}
	StaticList SL(a,len);
	SL.StaticList_Insert_Sort();
	SL.Display();
	cout << '\n';

	StaticList SLR(a, len);
	SLR.Radix_Sort();
	SLR.Display();
	return 0;
}