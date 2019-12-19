#include<iostream>
#include<vector>
using namespace std;

const int a[20] = { 17,8,21,19,31,33,22,25,42,37,40,52,61,78,73,55,94,88,79,85 };

//索引表的节点
struct Node
{
	int start;
	int data;
	int index;
	Node(int _start,int _data,int _index):start(_start),data(_data),index(_index){}
};
vector<Node> vn;//索引表

//构建索引表
void Create_index_list(const int a[], int len,int length)
{
	for (int i = 0; i < len; i+=length)
	{
		int max = 0; int index = 0;
		for (int j = 0; j < length; j++)
		{
			if (a[j + i] > max)
			{
				max = a[j + i];
				index = j + i;
			}
		}
		vn.push_back(Node(i, max, index));
	}
}

//折半查找索引表
int Binary_Search(vector<Node>& v, int elem)
{
	int low = 0, high = v.size() - 1;
	int mid = -1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (elem < v[mid].data)
		{
			high = mid - 1;
		}
		else if (elem > v[mid].data)
		{
			low = mid + 1;
		}
		else
			return vn[mid].start;
	}
	return vn[low].start;
}

//顺序查找块序列
int Sequence_Search(const int a[], int length, int elem)
{
	int start = Binary_Search(vn, elem);
	for (int i = start; i < start+length; i++)
	{
		if (a[i] == elem)
			return i + 1;
	}
	return 0;
}

int main()
{
	Create_index_list(a, 20, 4); 
	int index1 = Sequence_Search(a, 4, 19);
	int index2 = Sequence_Search(a, 4, 80);

	if (index1)
		cout << index1 << '\n';
	else
		cout << "Not Found\n";

	if (index2)
		cout << index2 << '\n';
	else
		cout << "Not Found\n";

	return 0;
}