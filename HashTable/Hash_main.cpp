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
	cout << "\n����̽��\n";
	h.display();
	cout << "\n���ҳɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", sum_succeed_1 * 1.0 / 7);
	cout << endl;
	cout << "���Ҳ��ɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", h.search_fail_rate());
	
	HashTable_twice ht;
	for (int i = 0; i < 7; i++)ht.insert(a[i]);
	for (int i = 0; i < 7; i++)ht.search(a[i]);
	cout << "\n����̽��\n";
	ht.display();
	cout << "\n���ҳɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", sum_succeed_2 * 1.0 / 7);
	cout << endl;
	cout << "���Ҳ��ɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", ht.search_fail_rate());

	HashTable_list hh;
	for (int i = 0; i < 7; i++)hh.insert(a[i]);
	for (int i = 0; i < 7; i++)hh.search(a[i]);
	cout << "\n����ַ\n";
	hh.display();
	cout << "\n���ҳɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", sum_succeed * 1.0 / 7);
	cout << endl;
	cout << "���Ҳ��ɹ���ƽ�����ҳ���Ϊ��";
	printf("%.1f", hh.search_fail_rate());


	puts("\n����������ҵ�ֵ");
	while (scanf_s("%d", &key) == 1)
	{
		node* pos = hh.search(key);
		if (!pos || hh.get(pos) != key)
			puts("������");
		else
		{
			printf("����,������ַΪ%d\n", pos);
		}
	}

	return 0;
}