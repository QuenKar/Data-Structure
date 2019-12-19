
#include <iostream>
using namespace std;
#include<math.h>
#define M 3
#define min_keynum  ceil(M/2.0)-1   


template<class T>
 struct BTNode{                //B-树结点类型 
    int keynum;                //结点关键字个数
    T key[M+1];                 //关键字数组，key[0]不使用 
    struct BTNode *parent;       //双亲结点指针
    struct BTNode *ptrs[M+1];    //孩子结点指针数组 
	 BTNode(){
		 parent=NULL; keynum=0;
         for (int i = 0; i <= M+1; ++i) {
            ptrs[i] = NULL; key[i]=-1;
        }
    }
};

template<class T>
struct Result{                     //B-树查找结果类型 
    BTNode<T> *pt;                 //指向找到的结点
    int i;                          //在结点中的关键字位置; 
    bool tag;                        //查找成功与否标志
};
template<class T>
class BTree
{
 public:
	BTree(){root=NULL;}
	~BTree(){if (root) Destory(root);}
	Result<T> SearchKey( T  key);
	void BTNode_InsertKey(BTNode<T>* &cur,T key,BTNode<T>* child);
	bool InsertKey(T key);
	BTNode<T>*  DivideNode(BTNode<T>* &cur);
	void _InOrder(BTNode<T>* root);
        bool leafnode(BTNode<T>* cur);
	bool  DeleteKey( T key);
	void  MergeNode(BTNode<T>* &cur,BTNode<T>* &par,int i,BTNode<T>* left,BTNode<T>* right);
	void BorrowFromRight(BTNode<T>* &par, int site, BTNode<T>* &cur, BTNode<T>* &right);
	void BorrowFromLeft(BTNode<T>* &par, int site, BTNode<T>* &cur, BTNode<T>* &left);
	void BTNode_Merge(BTNode<T>* & parent, int idx, BTNode<T>* & left, BTNode<T>* &cur);
	void Exchange(BTNode<T>* &cur,int &i);
	bool BTNode_DeleteKey(BTNode<T>* &cur,int rei);
	void InOrder(){ _InOrder(root);cout<<endl;}
	void Destory(BTNode<T>* &);

 private:
        BTNode<T>* root;
	
};
	 
template<class T>
void BTree<T>::Destory(BTNode<T>* &node){
	if(!node) return;
	for(int i=0; i<= node->keynum;++i)
		Destory(node->ptrs[i]);
 // delete node;
     node = NULL;
   return;
}





template<class T>
 Result<T> BTree<T>::SearchKey( T  key)
    {  
       BTNode<T>* parent = NULL;
       BTNode<T>* cur = root;
	   Result<T>ret;
	   
	   while (cur)
        {
            int i = 1;
            while(i <= cur->keynum && cur->key[i]< key)                           
                        ++i;
			if(i <= cur->keynum && cur->key[i]==key){
						 ret.i=i;
					     ret.tag=true;
					     ret.pt=cur;
                         return ret;
					 } 
			else {     
				parent=cur;
			    cur=cur->ptrs[i-1];
			    ret.i=i;
		   }
	   }
		ret.pt=parent;
		ret.tag=false;
		return ret; 	       
    
	}

template<class T>
 bool BTree<T>::InsertKey(T key)
    {
        if (root == NULL)
        {
           root = new BTNode<T>;
		   root->key[1] =key;
           root->keynum = 1;
		   
		   return true;
        }
		Result<T> ret=SearchKey(key);

       
        if (ret.tag == true)
        {
            return false;
        }

       BTNode<T>* cur = ret.pt;  // 将key,ptr插入节点cur
	   BTNode<T>* ptr = NULL;
       while (cur) {
			BTNode_InsertKey(cur,key,ptr); 

		   if (cur->keynum < M) {
                return true;
            }
             // 分裂当前节点cur
				
				int mid=ceil(M/2.0);
				T midkey=cur->key[mid];
				BTNode<T>* newnode = DivideNode(cur);
				if (cur == root) {//对根节点分裂进行特殊处理
				   root = new BTNode<T>;
                   root->key[1]=midkey;
                   root->keynum = 1;
				   root->ptrs[0] = cur;
                   root->ptrs[1] = newnode;
                   cur->parent = root;
                   newnode->parent =root;
				   cur->keynum=mid-1;
		           newnode->keynum=mid-1;
				   return true;                     
                }
				key=midkey;
				cur=cur->parent;
				ptr=newnode;
			   }
	   return true;
      }

  //分裂结点函数
 template<class T>
 BTNode<T>* BTree<T>:: DivideNode(BTNode<T>* &cur)
    {
        BTNode<T>* newnode = new BTNode<T>;
		int mid = ceil(M/2.0);
		int i=mid+1,j=1;
        for (; i <=cur->keynum; ++i)
        {
            //分裂节点cur,产生cur和newNode
            newnode->key[j] = cur->key[i];
            
			newnode->ptrs[j-1] = cur->ptrs[i-1];
            if(newnode->ptrs[j-1])
                newnode->ptrs[j-1]->parent = newnode;
            j++;
        }
		newnode->ptrs[j-1] = cur->ptrs[i-1];
		if(newnode->ptrs[j-1])
                newnode->ptrs[j-1]->parent = newnode;
        cur->keynum=mid-1;
		newnode->keynum=mid-1;
		return newnode;
    }

 //在当前节点中插入一个关键字和右孩子指针
  template<class T>
  void  BTree<T>::BTNode_InsertKey(BTNode<T>* &cur,T key,BTNode<T>* child)
    {
        int end = cur->keynum;
        while (end >= 1 && cur->key[end]>key)
        {
                cur->key[end+1] = cur->key[end];
                cur->ptrs[end+1] = cur->ptrs[end];
                --end;
      		}
		cur->key[end+1] = key;
        cur->ptrs[end+1] = child;
        if(child)
            child->parent = cur;
        cur->keynum++;
    }

   //在B-树上删除关键字key
 template<class T>
 bool  BTree<T>::DeleteKey( T key){

     Result<T> ret=SearchKey(key);	   //查找关键字key,用ret返回    
     if (ret.tag == false){
            return false;
        }
	 BTNode<T>* cur=ret.pt; 
	 int rei=ret.i;
	 if(!leafnode(cur)){
		Exchange(cur,rei);
		 }
	BTNode_DeleteKey(cur,rei);	
	return true;

 }  
 
template<class T>
void BTree<T>::BorrowFromRight(BTNode<T>* &par, int site, BTNode<T>* &cur, BTNode<T>* &right){

 	    cur->key[cur->keynum + 1] = par->key[site + 1];
        cur->ptrs[cur->keynum + 1] = right->ptrs[0];	
        if (cur->ptrs[cur->keynum + 1])		
                cur->ptrs[cur->keynum + 1]->parent = cur;	
        right->ptrs[0] = NULL;
		++cur->keynum; 	
 
 	   par->key[site + 1] = right->key[1];	
       for (int i = 0; i <= right->keynum; ++i) {	
             right->key[i] = right->key[i + 1];		
             right->ptrs[i] = right->ptrs[i + 1];	
			 }
 //end for	
       right->key[0] = 0;	
       --right->keynum;
	   } 

template<class T>
void BTree<T>::BorrowFromLeft(BTNode<T>* &par, int site, BTNode<T>* &cur, BTNode<T>* &left){
	for(int i= cur->keynum; i >= 0; --i) {	
                cur->key[i+1]=cur->key[i];		
                cur->ptrs[i+1]=cur->ptrs[i];
		   }   
    cur->key[1]=par->key[site];
    cur->ptrs[0] = left->ptrs[left->keynum];	
    if (cur->ptrs[0])	
          cur->ptrs[0]->parent = cur;	
    left->ptrs[left->keynum] = NULL;	
    ++cur->keynum; 	
 
    par->key[site] =left->key[left->keynum];	
    left->key[left->keynum]=-1; 	
     --left->keynum;
} 


template<class T>
 void BTree<T>::BTNode_Merge(BTNode<T>* & parent, int site, BTNode<T>* & left, BTNode<T>* &cur) {	 // combine lsilb and cur to lsilb
       
	   left->key[left->keynum+1] = parent->key[site];   //复制父节点site位置的关键字
	   left->ptrs[left->keynum+1]=cur->ptrs[0];
	   if (left->ptrs[left->keynum+1])	
               left->ptrs[left->keynum+1]->parent=left;
	   for (int i=1; i<=cur->keynum; ++i) {
            left->key[left->keynum+1+i]=cur->key[i];
            left->ptrs[left->keynum+1+i]=cur->ptrs[i];	
            if (left->ptrs[left->keynum+1+i])	
                left->ptrs[left->keynum+1+i]->parent=left; 
		}//endfor
      for (int i = site; i <= parent->keynum; ++i) {	
              parent->key[i] = parent->key[i + 1];	
              parent->ptrs[i] = parent->ptrs[i + 1];	
	     }
     --parent->keynum;
     left->keynum+=cur->keynum + 1; 
	 // delete cur;
	 cur=NULL;	
	 }

 //在当前节点上删除关键字key
template<class T>
bool BTree<T>::BTNode_DeleteKey(BTNode<T>* &cur,int rei){
	 for(int j=rei+1;j<=cur->keynum;j++){//删除cur中rei位置的关键字
		   cur->key[j-1]=cur->key[j];	   
		 }
	 cur->keynum--;
	 if(cur->keynum>=min_keynum){    //关键字数大于最小值，直接返回
	      return true;
	 }
    // 需要调整平衡使其满足B-树的条件	 

	
    while (cur!=root && cur->keynum<min_keynum) {
		BTNode<T>* par=cur->parent;
        BTNode<T>* left,*right;
        int site=0;
        while( par->ptrs[site]!=cur)
	         site++;  	                //找到关键删除关键字key所在节点指针在父节点中的指针位置site
        if(site>0)
             left=par->ptrs[site-1];
        else
	        left=NULL;
	    if(site<par->keynum)
            right=par->ptrs[site+1];
	    else 
		    right=NULL;
		if (right && right->keynum > min_keynum) {	//从右分支借	
             BorrowFromRight(par, site, cur, right);
              break;	
			  }	
        else if (left && left->keynum > min_keynum) { //从左分支借
             BorrowFromLeft(par, site, cur, left);
            break;	
			}
	   else {	//左右分支都不能借，右分支向左合并
           if (left)		
                BTNode_Merge(par, site, left, cur);	
          else	
                BTNode_Merge(par, site+1, cur, right);
		   cur=par;
	       par=cur->parent;
	    		
	 }//end else
   }//endwhile 
     if (cur->keynum == 0) {	 // 处理根root.	
        root= cur->ptrs[0];
		cur=NULL;
      //  delete cur;	
		} 
    return true;
}
//判断cur是否是叶子节点   
template<class T>
 bool BTree<T>::leafnode(BTNode<T>* cur){
	for (int i=0;i<=cur->keynum;i++)
		 if(cur->ptrs[i])return false;
    return true;
 }

//为cur找到合适的替换叶子节点   
template<class T>
 void BTree<T>::Exchange(BTNode<T>* &cur,int &i){
	 
	
	while(cur &&!(leafnode(cur))){
		BTNode<T>*left=cur->ptrs[i-1],*right=cur->ptrs[i];
	    BTNode<T>*temp;
	    if(left->keynum>right->keynum){
			cur->key[i]=left->key[left->keynum];
			cur=left;
			i=left->keynum;
	      }
  	else {
		cur->key[i]=right->key[1];
		cur=right;
		i=1;
	}
 }

		

			


	/*
    while(temp && !(leafnode(temp))){
		if(temp->keynum>)

	     temp=temp->ptrs[i]; 
	 }
	 cur->key[i]=temp->key[1];
	 cur=temp;
	 i=1;
	 */
 }
   

  //中序遍历
 template<class T>
 void BTree<T>::_InOrder(BTNode<T>* root)
   {
        if (root == NULL)
            return;

        BTNode<T>* cur = root;
       int i=1;
        for (; i <=cur->keynum; ++i)
        {
            _InOrder(cur->ptrs[i-1]);
            cout<<cur->key[i]<<" ";
		
        }
		 _InOrder(cur->ptrs[i-1]);
   	}





