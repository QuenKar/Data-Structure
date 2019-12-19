#pragma once
#include"HashTable3.h"
#include"HashTable.h"
#include"HashTable2.h"
int main()
{
	HashTable_linear h;
	const int a[7] = { 7,8,30,11,18,9,14 };
	int key;
	for (int i = 0; i < 7; i++)h.insert(a[i]);
	for (int i = 0; i < 7; i++)h.search(a[i]);
	cout << "\n线性探测\n";
	h.display();
	cout << "\n查找成功的平均查找长度为：";
	printf("%.1f", sum_succeed_1 * 1.0 / 7);
	cout << endl;
	cout << "查找不成功的平均查找长度为：";
	printf("%.1f", h.search_fail_rate());
	
	HashTable_twice ht;
	for (int i = 0; i < 7; i++)ht.insert(a[i]);
	for (int i = 0; i < 7; i++)ht.search(a[i]);
	cout << "\n二次探测\n";
	ht.display();
	cout << "\n查找成功的平均查找长度为：";
	printf("%.1f", sum_succeed_2 * 1.0 / 7);
	cout << endl;
	cout << "查找不成功的平均查找长度为：";
	printf("%.1f", ht.search_fail_rate());

	HashTable_list hh;
	for (int i = 0; i < 7; i++)hh.insert(a[i]);
	for (int i = 0; i < 7; i++)hh.search(a[i]);
	cout << "\n链地址\n";
	hh.display();
	cout << "\n查找成功的平均查找长度为：";
	printf("%.1f", sum_succeed * 1.0 / 7);
	cout << endl;
	cout << "查找不成功的平均查找长度为：";
	printf("%.1f", hh.search_fail_rate());


	puts("\n输入你想查找的值");
	while (scanf_s("%d", &key) == 1)
	{
		node* pos = hh.search(key);
		if (!pos || hh.get(pos) != key)
			puts("不存在");
		else
		{
			printf("存在,索引地址为%d\n", pos);
		}
	}

	return 0;
}