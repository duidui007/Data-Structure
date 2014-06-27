//v1.1 理解引用 去除SearchFather
//在写代码的过程中，最大的问题就是变量作用域以及引用变量被干扰
//v1.2 不必删除直接替代即可,根据二叉搜索树的性质
//要理解引用 自动解引用的指针 会改变变量的内容 却不会改变量的地址
#include <iostream>

using namespace std;

typedef struct Node
{
	/* data */
	int  data;
	int key;
	struct Node *left;
	struct Node *right;
}BSTNode,*BSTree;


BSTree father=NULL;

void InitBSTree(BSTree &T)
{
	T=NULL;
}

//哨兵
//返回的其实是父节点右子树的引用
//即存储父节点的右子树的地址
BSTree& Search(BSTree &T,int &key)
{
	if (T==NULL){
		cout<<"not found"<<endl;
		return T;
	}
	else{
		if (key==T->key){
			cout<<"found"<<endl;
			return T;
		}
		else if (key<T->key){
			father=T;
			Search(T->left,key);
		}
		else if (key>T->key){
			father=T;
			Search(T->right,key);
		}
	}
}

/*
BSTree& SearchFather(BSTree &T,int &key)
{
	if (T==NULL)
	{
		return father;
	}
	else{
		if (key==T->key)
		{
			return father;
		}
		else if (key<T->key)
		{	
			father=T;
			T=T->left;
			SearchFather(T,key);
		}
		else if (key>T->key)
		{
			father=T;
			T=T->right;
			SearchFather(T,key);
		}
	}
}
*/

bool Insert(BSTree &T,int &key,int data)
{
	BSTree &newnode=Search(T,key);
	if (newnode!=NULL)
		return false;
	newnode=new BSTNode;
	newnode->key=key;
	newnode->data=data;
	newnode->left=NULL;
	newnode->right=NULL;
	return true;
}

void InOrder(BSTree &T)
{
	if(T!=NULL)
	{
		InOrder(T->left);
		//while(T!=NULL)
		cout<<T->data<<' ';
		InOrder(T->right);
	}
}

/*
bool Remove_1.0(BSTree &T,int &key)
{
	BSTree &Tmp=Search(T,key);
	if (Tmp==NULL)
	{
		return false;
	}
	else{
		if ((Tmp->left==NULL)&&(Tmp->right==NULL))
		{
			Tmp=NULL;
		}
		else if ((Tmp->left!=NULL)&&(Tmp->right!=NULL))
		{
			BSTree &Tmpfather=SearchFather(T,key);
			BSTree left=Tmp->left;
			BSTree right=Tmp->right;
			Tmp=NULL;
			int keyleft=left->key;
			int keyright=right->key;
			BSTree &tmp1=Search(Tmpfather,keyleft);
			tmp1=left;
			BSTree &tmp2=Search(Tmpfather,keyright);
			tmp2=right;
		}
		else if ((Tmp->left==NULL)&&(Tmp->right!=NULL))
		{
			BSTree &Tmpfather=SearchFather(T,key);
			BSTree right=Tmp->right;
			Tmp=NULL;
			int keyright=right->key;
			BSTree &tmp2=Search(Tmpfather,keyright);
			tmp2=right;
		}
		else if ((Tmp->left!=NULL)&&(Tmp->right==NULL))
		{
			BSTree &Tmpfather=SearchFather(T,key);
			BSTree left=Tmp->left;
			Tmp=NULL;
			int &keyleft=left->key;
			BSTree &tmp1=Search(Tmpfather,keyleft);
			tmp1=left;
		}
	}
}
*/

/*
bool Remove_1.1(BSTree &T,int &key)
{
	father=NULL;
	BSTree &Tmp=Search(T,key);
	BSTree left,right;
	if (Tmp==NULL)
	{
		cout<<"key isn't exist";
		return true;
	}
	else{
		if (father==NULL)
		{
			
			if ((Tmp->left==NULL)&&(Tmp->right==NULL))
			{
				Tmp=NULL;
			}
			else if (((left=Tmp->left)!=NULL)&&((right=Tmp)->right!=NULL))
			{
				Tmp=left;
				BSTree& T=Search(left,right->key);
				T=right;
			}
			else if (((left=Tmp->left)==NULL)&&((right=Tmp->right)!=NULL))
			{
				Tmp=right;
			}
			else if (((left=Tmp->left)!=NULL)&&((right=Tmp->right)==NULL))
			{
				Tmp=left;
			}
			T=Tmp;
		}
		else
		{
			if ((Tmp->left==NULL)&&(Tmp->right==NULL))
			{
				Tmp=NULL;
			}
			else if (((left=Tmp->left)!=NULL)&&((right=Tmp)->right!=NULL))
			{
				Tmp=NULL;
				BSTree &tmp1=Search(father,left->key);
				tmp1=left;
				BSTree &tmp2=Search(father,right->key);
				tmp2=right;
			}
			else if (((left=Tmp->left)==NULL)&&((right=Tmp->right)!=NULL))
			{
				Tmp=NULL;
				BSTree &tmp2=Search(father,right->key);
				tmp2=right;
			}
			else if (((left=Tmp->left)!=NULL)&&((right=Tmp->right)==NULL))
			{
				Tmp=NULL;
				BSTree &tmp1=Search(father,left->key);
				tmp1=left;
			}
		}
		
	}
}
*/

bool Remove(BSTree &T,int &key)
{
	BSTree &Tmp=Search(T,key);
	if (Tmp==NULL){
		cout<<"key isn't exist";
		return true;
	}
	else{
		BSTree& left=Tmp->left;
		BSTree& right=Tmp->right;
		Tmp=left;
		BSTree& Tmp1=Search(Tmp,right->key);
		Tmp1=right;
	}
	return true;
}

int main()
{
	BSTree T=NULL;
	BSTree tmp;
	int key,data;
	while(cin>>key>>data)
	{
		Insert(T,key,data);
	}
	InOrder(T);
	key=3;
	Remove(T,key);
	InOrder(T);
	system("pause");
	return 0;
}
