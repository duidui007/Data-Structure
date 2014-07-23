#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Node
{
	/* data */
	int BF;//平衡因子
	int Height;//树高
	int data;
	int key;
	struct Node * left;
	struct Node * right;
	struct Node * father;
	struct Node * precursor;//中序直接前驱
	struct Node * successor;//中序直接后继
}BBSTNode,*BBSTree;

BBSTree father;

void InitBBSTree(BBSTree &T)
{
	T=NULL;
}

int Height(BBSTree &T)
{
	if (T==NULL)
	{
		return 0;		
	}
	else{
		int i=Height(T->left);
		int j=Height(T->right);
		int k=max(i,j);
		return k+1;
	}
}

int BF(BBSTree &T)
{
	int k=Height(T->left)-Height(T->right);
	if (k>=0)
		return k;
	else 
		return -k;
}

//哨兵
//返回的其实是父节点右子树的引用
//即存储父节点的右子树的地址
BBSTree& Search(BBSTree &T,int &key)
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

//如何判断各种插入的情况
//需要知道其父节点，祖父节点？
//将节点插入一颗平衡二叉搜索树中
bool Insert(BBSTree &T,int &key)
{
	BBSTree &Tmp=Search(T,key);
	if (Tmp!=NULL){
		cout<<"Node exist"<<endl;
		return false;
	}
	else{
		Tmp=new BBSTNode;
		Tmp->key=key;
		Tmp->father=father;
		Tmp->left=NULL;
		Tmp->right=NULL;
		if (Tmp->father==NULL)
			//说明其本身就是根节点
			return true;
		else if ((Tmp->father)->father==NULL)
			//说明其父节点为根节点
			return true;
		else{
			if (((Tmp->father)->father)->BF==0)
				return true;
			else{
				if ((Tmp->key<((Tmp->father)->father)->key)&&(Tmp->key<(Tmp->father)->key)){
					(Tmp->father)->right=(Tmp->father)->father;
					BBSTree Tmp1=(Tmp->father)->father;
					((Tmp->father)->father)->father=Tmp->father;
					((Tmp->father)->father)->left=NULL;
					(Tmp->father)->father=Tmp1->father;
				}
				else if ((Tmp->key<((Tmp->father)->father)->key)&&(Tmp->key>(Tmp->father)->key)){
					BBSTree Tmp1=(Tmp->father);
					BBSTree Tmp2=(Tmp->father)->father;
					Tmp->father=((Tmp->father)->father)->father;
					Tmp->left=Tmp1;
					Tmp1->father=Tmp;
					Tmp1->right=NULL;
					Tmp->right=Tmp2;
					Tmp2->father=Tmp;
					Tmp2->left=NULL;
				}
				else if ((Tmp->key>((Tmp->father)->father)->key)&&(Tmp->key<(Tmp->father)->key)){
					BBSTree Tmp1=(Tmp->father);
					BBSTree Tmp2=(Tmp->father)->father;
					Tmp->father=((Tmp->father)->father)->father;
					Tmp->left=Tmp2;
					Tmp2->father=Tmp;
					Tmp2->right=NULL;
					Tmp->right=Tmp1;
					Tmp1->father=Tmp;
					Tmp2->left=NULL;
				}
				else if ((Tmp->key>((Tmp->father)->father)->key)&&(Tmp->key>(Tmp->father)->key)){
					int n=((Tmp->father)->father)->key;
					BBSTree &Tmp1=Search(T,n);
					Tmp1=Tmp->father;
					Tmp->father=((Tmp->father)->father)->father;
					(Tmp->father)->left=((Tmp->father)->father)->father;
					((Tmp->father)->father)->right=NULL;
				}
			}
		}
		return true;
	}
}

void InOrder(BBSTree &T)
{
	if(T!=NULL)
	{
		cout<<T->key<<' ';
		InOrder(T->left);
		//while(T!=NULL)
		InOrder(T->right);
	}
}

void InOrder_BF(BBSTree &T)
{
	if(T!=NULL){
		T->BF=BF(T);
		InOrder_BF(T->left);
		InOrder_BF(T->right);
	}
}

void InOrder_Height(BBSTree &T)
{
	if(T!=NULL){
		T->Height=Height(T);
		InOrder_Height(T->left);
		InOrder_Height(T->right);
	}
}

/*
void InOrder_Thread_v1.0(BBSTree &T)
{
	int tmp=-1;
	if (T!=NULL){
		InOrder_Thread(T->left);
		//cout<<T->data<<' ';
		BBSTree &Tmp=Search(T,tmp);
		T->precursor=Tmp;
		if (Tmp!=NULL)
			Tmp->successor=T;
		tmp=T->key;
		InOrder_Thread(T->right);
	}
}
*/

void InOrder_Thread(BBSTree &T,BBSTree &precursor)
{
	if (T!=NULL){
		InOrder_Thread(T->left,precursor);
		//cout<<T->data<<' ';
		T->precursor=precursor;
		if (precursor!=NULL)
			precursor->successor=T;
		precursor=T;
		InOrder_Thread(T->right,precursor);
	}
}

//思路是相同的，只是直接保持前序节点的指针即可，而非值
//如此则不用search一次了
void Create_InOrder_Thread(BBSTree &T)
{
	if (T!=NULL)
	{
			BBSTree precursor=NULL;
			InOrder_Thread(T,precursor);
			//处理最后一个节点
			precursor->successor=NULL;
	}
}

bool IsBalance(BBSTree &T)
{
	if ((T->BF<2)&&(T->BF>-2)
		return true;
	else
		return false;
}	
·
}

BBSTree& Rotate_right_a(BBSTree &T,int &key)
{
	BBSTree &Tmp=Search(T,key);
	BBSTree Tmp_left_right=(Tmp->left)->right;
	BBSTree Tmp_Tmp=Tmp;
	Tmp=Tmp->left;
	Tmp->father=Tmp_Tmp->father;
	Tmp_Tmp->father=Tmp;
	Tmp_Tmp->right=Tmp_left_right;
	Tmp_right_left->father=Tmp_Tmp;
	Tmp->right=Tmp_Tmp;
	return Tmp;
}

bool Remove(BBSTree &T,int &key)
{
	BBSTree &Tmp=Search(T,key);
	if (Tmp==NULL)
	{
		cout<<"don't exist"<<endl;
		return false;
	}
	else
	{
		if (Tmp->father==NULL)
		{
			//说明为根节点
			T=NULL;
			return true
		}
		else
		{
			if ((Tmp->father)->BF==0)
			{
				/* code */
				if ((Tmp->left)==NULL)&&(Tmp->right)==NULL))
				{
					/* code */
					Tmp=NULL;
					return true;
				}
				else if ((Tmp->left)==NULL)&&(Tmp->right)!=NULL))
				{
					/* code */
					Tmp=Tmp->right;
					return true;
				}
				else if ((Tmp->left)!=NULL)&&(Tmp->right)==NULL))
				{
					/* code */
					Tmp=Tmp->left;
					return true;
				}
				else if ((Tmp->left)!=NULL)&&(Tmp->right)!=NULL))
				{
					/*
					if (Tmp->BF==0)
					{
						BBSTree &Tmp1=(Tmp->father)->successor;
						Tmp=(Tmp->father)->successor;
						Tmp1=NULL;
					}
					else
					{
						BBSTree &Tmp1=(Tmp->father)->successor;
						int n=Tmp1->key;
						BBSTree &Tmp2=Search(T,n);
					*/
						BBSTree &Tmp1=(Tmp->father)->successor;
						int n=(Tmp1->father)->key;
						Tmp->key=Tmp1->key;
						BBSTree &Tmp2=Search(T,n);
						Tmp2->left=NULL;
						int tmp_Height=Tmp2->Height;
						InOrder_Height(T);
						InOrder_BF(T);
						if ((Tmp2->Height==tmp_Height)&&(Tmp2->BF<2)&&(Tmp2->BF>-2))
						{
							/* code */
							return true;
						}
						else if (Tmp2->Height==tmp_Height)&&(Tmp2->BF<2)&&(Tmp2->BF>-2))
						{
							/* code */
						}

					}
				}
			}
		}
	}
}




int main()
{
	BBSTree T=NULL;
	int key;
	while(cin>>key)
	{
		Insert(T,key);
		InOrder_Height(T);
		InOrder_BF(T);
		InOrder_Thread(T);
	}
	InOrder(T);
	system("pause");
	return 0;
}