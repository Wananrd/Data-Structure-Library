#pragma once
#include<iostream>
using namespace std;

#include"Link_Queue.hpp"
#include"Link_Stack.hpp"

template<class T>
struct BiTreeNode
{
	T data;								//数据域
	BiTreeNode* leftChild;				//左子树
	BiTreeNode* rightChild;				//右子树
};

template<class T>
class BinaryTree
{
public:
	BinaryTree();						//构造函数
	BinaryTree(BinaryTree<T>& t);		//复制二叉树
	~BinaryTree();						//析构函数
	bool IsEmpty();						//判空
	int Height();						//返回树高度
	int Size();							//返回结点数
	BiTreeNode<T>* GetRoot()const;		//取根
	void PreOrder();					//前序遍历
	void InOrder();						//中序遍历
	void PostOrder();					//后序遍历
	void LevelOrder();					//层次遍历
	void Destory();						//销毁
private:
	BiTreeNode<T>* CreatBiTree(BiTreeNode<T>* bt);
	BiTreeNode<T>* BinaryTreeCopy(BiTreeNode<T>* bt);
	void PreOrder(BiTreeNode<T>* bt);
	int Size(BiTreeNode<T>* bt);			//返回结点数
	int Height(BiTreeNode<T>* bt);			//返回树高度
	void Destory(BiTreeNode<T>* bt);		//销毁
	BiTreeNode<T>*root;
};

template<class T>
BinaryTree<T>::BinaryTree()						//构造函数
{
	root = CreatBiTree(root);
}

template<class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& t)		//拷贝构造
{
	root = BinaryTreeCopy(t.root);
}

template<class T>
BinaryTree<T>::~BinaryTree()						//析构函数
{
	Destory(root);
}

template<class T>
BiTreeNode<T>*BinaryTree<T>::CreatBiTree(BiTreeNode<T>* bt)			//思路：遇#则结点空，创建新结点，左右递归创树
{
	T ch;
	cin >> ch;				//输入前序创建的信息
	if (ch == '#')
	{
		bt = NULL;			//如果是#，树为空
	}
	else
	{
		bt = new BiTreeNode<T>;	//创建新结点
		bt->data = ch;
		bt->leftChild = CreatBiTree(bt->leftChild);		//递归创建左子树
		bt->rightChild = CreatBiTree(bt->rightChild);	//递归创建右子树
	}
	return bt;
}

template<class T>
bool BinaryTree<T>::IsEmpty()						//判空
{
	return root == NULL ? true : false;
}

template<class T>
int BinaryTree<T>::Height()						//返回树高度
{
	return Height(root);
}

template<class T>
int BinaryTree<T>::Size()							//返回结点数
{
	return Size(root);
}

template<class T>
BiTreeNode<T>* BinaryTree<T>::GetRoot()const		//取根
{
	return root;
}

template<class T>
void BinaryTree<T>::PreOrder()					//前序遍历   思路：从顶部出发，访问后，先记录下右孩子，再记录左孩子，循环直至栈空
{
	LinkStack<BiTreeNode<T>*> S;				//队列S初始化
	if (root == NULL)
	{
		return;
	}
	S.Push(root);								//从顶部出发
	BiTreeNode<T>* q;
	while (!S.Is_Empty())
	{
		S.Pop(q);
		cout << q->data << " ";					//访问
		if (q->rightChild)						//先记录右孩子
		{
			S.Push(q->rightChild);
		}
		if (q->leftChild)						//再记录左孩子
		{
			S.Push(q->leftChild);
		}
	}
}

template<class T>
void BinaryTree<T>::InOrder()						//中序遍历		思路：记录顶点，从左走到底，退出并指向右边
{
	LinkStack<BiTreeNode<T>*> S;				//队列S初始化
	if (root == NULL)
	{
		return;
	}
	BiTreeNode<T>* q = root;
	while (q||!S.Is_Empty())
	{
		while (q)									//遍历指针未到左下的结点，不空
		{
			S.Push(q);								//该子树沿途结点进栈
			q = q->leftChild;						//遍历指针指向左结点
		}
		if (!S.Is_Empty())							//栈不空时退栈
		{
			S.Pop(q);								//退栈，访问根结点
			cout << q->data << " ";
			q = q->rightChild;						//遍历指针右结点
		}
	}
}

/*
template<class T>
void BinaryTree<T>::PostOrder()					//后序遍历
{												//思路1：用两个栈来实现，我们知道先序遍历是根--左--右，在代码的基础上可以实现根--右--左，如果逆序输出，就是左--根--右
	LinkStack<BiTreeNode<T>*>S;
	LinkStack<BiTreeNode<T>*>S2;
	if (root == NULL)
	{
		return;
	}
	S.Push(root);
	BiTreeNode<T>* q = root;
	while (!S.Is_Empty())
	{
		S.Pop(q);
		S2.Push(q);
		if (q->leftChild)
		{
			S.Push(q->leftChild);
		}
		if (q->rightChild)
		{
			S.Push(q->rightChild);
		}
	}
	while (!S2.Is_Empty())
	{
		S2.Pop(q);
		cout << q->data << " ";
	}
}
*/

template<class T>
void BinaryTree<T>::PostOrder()					//后序遍历
{												//思路2：因为是后序遍历，所以需要在左右孩子都访问完之后，再访问父亲结点
	LinkStack<BiTreeNode<T>*>S;
	BiTreeNode<T>* pre = root;							//记录上一次访问的结点
	BiTreeNode<T>* p = root;							//记录当前访问结点
	while (p || !S.Is_Empty())
	{
		if (p != NULL && pre != p->leftChild && pre != p->rightChild)		//结点不空且左右孩子未被访问
		{
			S.Push(p);
			p = p->leftChild;
		}
		else
		{
			S.Get_Top(p);
			if (p->rightChild != NULL && pre != p->rightChild)		//右子树不空且没被访问，入栈右孩子
			{
				p = p->rightChild;
			}
			else													//访问到最后的右子树的结点后，退栈
			{
				S.Pop(pre);
				cout << pre->data << " ";
				if (!S.Get_Top(p))
				{
					p = NULL;
				}
			}
		}
	}
}

template<class T>
void BinaryTree<T>::LevelOrder()					//层次遍历		思路：入队顶点，当队不空，出队输出，并依次入队左孩子，右孩子
{
	LinkQueue<BiTreeNode<T>*> Q;			//队列Q初始化
	if (root == NULL)
	{
		return;
	}
	Q.EnQueue(root);
	BiTreeNode<T> *q;
	while (!Q.Is_Empty())
	{
		Q.DeQueue(q);
		cout << q->data << " ";
		if (q->leftChild)
		{
			Q.EnQueue(q->leftChild);
		}
		if (q->rightChild)
		{
			Q.EnQueue(q->rightChild);
		}
	}
}

template<class T>
void BinaryTree<T>::Destory()						//销毁
{
	Destory(root);
}

template<class T>
void BinaryTree<T>::PreOrder(BiTreeNode<T>* bt)
{
	if (bt)
	{
		cout << bt->data << " ";
		PreOrder(bt->leftChild);
		PreOrder(bt->rightChild);
	}
}

template<class T>
BiTreeNode<T>* BinaryTree<T>::BinaryTreeCopy(BiTreeNode<T>* bt)
{
	BiTreeNode<T>* temp = NULL;
	if (bt)
	{
		temp = new BiTreeNode<T>;
		temp->data = bt->data;
		temp->leftChild = BinaryTreeCopy(bt->leftChild);
		temp->rightChild = BinaryTreeCopy(bt->rightChild);
	}
	else
	{
		temp = NULL;
	}
	return temp;
}

template<class T>
int BinaryTree<T>::Size(BiTreeNode<T>* bt)			//返回结点数
{
	static int node_num = 0;
	if (bt)
	{
		node_num++;
		Size(bt->leftChild);
		Size(bt->rightChild);
	}
	return node_num;
}

template<class T>
int BinaryTree<T>::Height(BiTreeNode<T>* bt)			//返回树高度
{
	if (bt == NULL)
	{
		return 0;
	}
	int m = Height(bt->leftChild);
	int n = Height(bt->rightChild);
	return m > n ? ++m : ++n;
}

template<class T>
void BinaryTree<T>::Destory(BiTreeNode<T>* bt)		//销毁
{
	if (bt)
	{
		Destory(bt->leftChild);
		Destory(bt->rightChild);
		delete bt;
	}
}
