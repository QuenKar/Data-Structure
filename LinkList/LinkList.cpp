#include"Link_List.h"

int main()
{
	List La, Lb;
	La.create_List(6);
	Lb.create_List(5);
	cout << "LA:" ;
	La.output();
	cout << "LB:";
	Lb.output();

	cout << "After Insert 38 LA:" << '\n';
	La.insert_Node(3, 38);
	La.output();

	cout << "After Delete LB:" << '\n';
	Lb.delete_Node(4);
	Lb.output();

	cout << "Search Element in LA:" << '\n';
	La.search_Node(100);

	cout << "After Merge LA and LB:" << '\n';
	La.Merge_List(&Lb);
	La.output();

	cout<< "After reverse LA:"<<'\n';
	La.reverse_List();
	La.output();

	return 0;
}

/*
25 12 78 34 100 88
88 10 15 25 32
*/