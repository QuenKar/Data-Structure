#include "head.h"
#include<fstream>

int main(){
	
	BTree<int> b_tree;
	fstream file("data.txt");
	//���ζ����ļ������ݲ����뵽B-����
	int temp;
	while(!file.eof()){
		file>>temp;
		 b_tree.InsertKey(temp);
	}
	file.close();
	cout<<"��ǰb-������������������£�"<<endl;
	b_tree.InOrder();
	
	/*
	cout<<"����Ҫ���ҵĹؼ���"<<endl;
	Result<int> rt;
	cin>>temp;
	rt=b_tree.SearchKey(temp);
	if(rt.tag)
	      cout<<"�ڵ�ָ��"<< rt.pt<<"   ��"<<rt.i<<"�ؼ�����"<<rt.pt->key[rt.i]<<endl;
	else cout<<"�ؼ���"<<temp<<"������"<<endl;
	*/


	cout<<"����Ҫɾ���Ĺؼ���,0����"<<endl;
	cin>>temp;
     while(temp){  //����0���ҽ���
		   bool flag=b_tree.DeleteKey(temp);
		  if(flag){
		       cout<<"ɾ�����B��Ϊ��"<<endl;
				b_tree.InOrder();
		     }
		   else cout<<"ɾ���Ĺؼ���"<<temp<<"������"<<endl;
		   cout<<"����Ҫɾ���Ĺؼ���,0����"<<endl;
	       cin>>temp;
		   

	 }
	 return 0;
   }
