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
//递归函数的调用和普通的函数并无区别
//
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
			return Search(T->left,key);
		}
		else if (key>T->key){
			father=T;
			return Search(T->right,key);
		}
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
	if ((T->BF<2)&&(T->BF>-2))
		return true;
	else
		return false;
}	

//T为父节点孩子指针的引用
void Rotate_right_right(BBSTree &T)
{
	BBSTree Tmp_right_left=(T->right)->left;
	BBSTree Tmp_Tmp=T;
	T=T->right;
	T->father=Tmp_Tmp->father;
	T->left=Tmp_Tmp;
	Tmp_Tmp->father=T;
	Tmp_Tmp->right=Tmp_right_left;
	if (Tmp_right_left!=NULL)
	{
		Tmp_right_left->father=Tmp_Tmp;
	}
}

//T为父节点孩子指针的引用
void Rotate_left_left(BBSTree &T)
{
	BBSTree Tmp_left_right=(T->left)->right;
	BBSTree Tmp_Tmp=T;
	T=T->left;
	T->father=Tmp_Tmp->father;
	T->right=Tmp_Tmp;
	Tmp_Tmp->father=T;
	Tmp_Tmp->left=Tmp_left_right;
	if (Tmp_left_right!=NULL)
	{
		Tmp_left_right->father=Tmp_Tmp;
	}

}

//T为父节点孩子指针的引用
void Rotate_right_left(BBSTree &T)
{
	Rotate_left_left(T->right);
	Rotate_right_right(T);
}

void Rotate_left_right(BBSTree &T)
{
	Rotate_right_right(T->left);
	Rotate_left_left(T);
}

BBSTree& IBNode(BBSTree &T,BBSTree &Tmp)
{
	if (T!=NULL)
	{
		if (!IsBalance(T))
			Tmp=T;
		Find_IBNode(T->left,Tmp);
		Find_IBNode(T->right,Tmp);
	}
}

BBSTree& Find_IBNode(BBSTree &T)
{
	BBSTree Tmp=NULL;
	IBNode(T,Tmp);
	return Tmp;
}

bool  Adjust(BBSTree &T)
{
	InOrder_Height(T);
	InOrder_BF(T);
	BBSTree &TmpIB=Find_IBNode(T);
	if (TmpIB==NULL)
		return true;
	else{
		int L_Height=Height(TmpIB->left);
		int R_Height=Height(TmpIB->right);
		if (L_Height<R_Height){
			BBSTree &TmpRight=TmpIB->right;
			int L_Height=Height(TmpRight->left);
			int R_Height=Height(TmpRight->right);
			if (L_Height<R_Height)
				Rotate_right_right(TmpIB);
			else
				Rotate_right_left(TmpIB);
		}
		else if (L_Height>R_Height)
		{
			BBSTree &TmpRight=TmpIB->right;
			int L_Height=Height(TmpRight->left);
			int R_Height=Height(TmpRight->right);
			if (L_Height<R_Height)
				Rotate_left_right(TmpIB);
			else
				Rotate_left_left(TmpIB);
		}
	}
}

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
		Tmp->left=Tmp->right=NULL;
		if (Tmp->father==NULL)
			//说明其本身就是根节点
			return true;
		else if ((Tmp->father)->father==NULL)
			//说明其父节点为根节点
			return true;
		else{
			Adjust(T);
		}
		return true;
	}
}

bool Remove(BBSTree &T,int &key)
{
	BBSTree &Tmp=Search(T,key);
	if (Tmp==NULL)
	{
		cout<<"don't exist"<<endl;
		return false;
	}
	else{
		if ((Tmp->left==NULL)||(Tmp->right==NULL))
		{
			BBSTree& left=Tmp->left;
			BBSTree& right=Tmp->right;
			Tmp=left;
			BBSTree& Tmp1=Search(Tmp,right->key);
			Tmp1=right;
			BBSTree &TmpIB=Find_IBNode(T);
			while(TmpIB!=NULL)
			{
				Adjust(T);
				TmpIB=Find_IBNode(T);
			}
		}
		else{
			BBSTree Tmp_succ=Tmp->successor;
			Tmp->key=Tmp_succ->key;
			if (Tmp_succ->right!=NULL)
			{
				//(Tmp_succ->right)->father=Tmp_succ->father;
				if ((Tmp_succ->father)->key=Tmp->key)
				{
					(Tmp_succ->father)->right=Tmp_succ->right;
				}
				else
					(Tmp_succ->father)->left=Tmp_succ->right;
				
			}
			Tmp_succ=Tmp_succ->right;
			BBSTree &TmpIB=Find_IBNode(T);
			while(TmpIB!=NULL)
			{
				Adjust(T);
				TmpIB=Find_IBNode(T);
			}
		}
	}
	return true;
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
		Create_InOrder_Thread(T);
	}
	BBSTree check=Find_IBNode(T);
	int k=3;
	//Remove(T,k);
	if (check==NULL)
	{
		cout<<"success"<<endl;
	}
	InOrder(T);
	system("pause");
	return 0;
}