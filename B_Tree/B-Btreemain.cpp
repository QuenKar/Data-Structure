#include "head.h"
#include<fstream>

int main(){
	
	BTree<int> b_tree;
	fstream file("data.txt");
	//依次读入文件中数据并插入到B-树中
	int temp;
	while(!file.eof()){
		file>>temp;
		 b_tree.InsertKey(temp);
	}
	file.close();
	cout<<"当前b-树的中序遍历序列如下："<<endl;
	b_tree.InOrder();
	
	/*
	cout<<"输入要查找的关键字"<<endl;
	Result<int> rt;
	cin>>temp;
	rt=b_tree.SearchKey(temp);
	if(rt.tag)
	      cout<<"节点指针"<< rt.pt<<"   第"<<rt.i<<"关键字是"<<rt.pt->key[rt.i]<<endl;
	else cout<<"关键字"<<temp<<"不存在"<<endl;
	*/


	cout<<"输入要删除的关键字,0结束"<<endl;
	cin>>temp;
     while(temp){  //输入0查找结束
		   bool flag=b_tree.DeleteKey(temp);
		  if(flag){
		       cout<<"删除后的B树为："<<endl;
				b_tree.InOrder();
		     }
		   else cout<<"删除的关键字"<<temp<<"不存在"<<endl;
		   cout<<"输入要删除的关键字,0结束"<<endl;
	       cin>>temp;
		   

	 }
	 return 0;
   }
