#pragma once
#include<iostream>
using namespace std;

#include"Link_Stack.hpp"
#include"BiTree.hpp"
							//二叉排序树的效率O(log2n)~O(n)
							//二叉排序树是完全二叉树的时候搜索的效率最高
							//需要构造二叉平衡树
template<class T>
class BiSortTree
{
public:
	BiSortTree();
	//~BiSortTree();
	void CreatBiSortTree();									//创建二叉排序树
	void InOrder();
	bool SearchVal(T val);
	bool DeleteVal(T key);									//删除结点
private:
	void InsertBSF(BiTreeNode<T>*& bt, T key);				//二叉树的插入
	BiTreeNode<T>* SearchVal(BiTreeNode<T>* bt, T key);		//二叉树的查找
	bool DeleteVal(BiTreeNode<T>*& bt, T key);				//删除结点
	void DeleteNode(BiTreeNode<T>*& bt);				//删除结点
	BiTreeNode<T>* root;
};

template<class T>
BiSortTree<T>::BiSortTree()
{
	root = NULL;
}

template<class T>
void BiSortTree<T>::CreatBiSortTree()				//创建二叉排序树
{
	int num;
	cout << "请输入结点数量：";
	cin >> num;
	T* arr = new T[num];
	cout << "请输入结点信息：";
	for (int i = 0; i < num; i++)
	{
		cin >> arr[i];
		InsertBSF(root, arr[i]);
	}
}

template<class T>
void BiSortTree<T>::InOrder()
{
	LinkStack<BiTreeNode<T>*> S;				//队列S初始化
	if (root == NULL)
	{
		return;
	}
	BiTreeNode<T>* q = root;
	while (q || !S.Is_Empty())
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

template<class T>
bool BiSortTree<T>::SearchVal(T val)
{
	if (SearchVal(root, val) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<class T>
bool BiSortTree<T>::DeleteVal(T key)									//删除结点
{
	if (DeleteVal(root, key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool BiSortTree<T>::DeleteVal(BiTreeNode<T>*& bt, T key)			//删除结点
{
	if (bt == NULL)
	{
		return false;
	}
	else
	{
		if (bt->data == key)
		{
			DeleteNode(bt);
		}
		else if (bt->data > key)
		{
			return DeleteVal(bt->leftChild, key);
		}
		else
		{
			return DeleteVal(bt->rightChild, key);
		}
	}
}

template<class T>
void BiSortTree<T>::InsertBSF(BiTreeNode<T>*& bt, T key)			//二叉树的插入
{
	if (bt == NULL)
	{
		bt = new BiTreeNode<T>;
		bt->data = key;
		bt->leftChild = NULL;
		bt->rightChild = NULL;
	}
	else
	{
		if (bt->data > key)
		{
			InsertBSF(bt->leftChild, key);
		}
		else
		{
			InsertBSF(bt->rightChild, key);
		}
	}
}

template<class T>
BiTreeNode<T>* BiSortTree<T>::SearchVal(BiTreeNode<T>* bt, T key)		//二叉树的查找
{
	if (bt == NULL)
	{
		return NULL;
	}
	else
	{
		if (bt->data == key)
		{
			return bt;
		}
		else if (bt->data > key)
		{
			SearchVal(bt->leftChild, key);
		}
		else
		{
			SearchVal(bt->rightChild, key);
		}
	}
}

template<class T>
void BiSortTree<T>::DeleteNode(BiTreeNode<T>*& bt)									//删除结点
{
	if (bt->leftChild == NULL && bt->rightChild == NULL)					//1.如果是根结点
	{
		BiTreeNode<T>* p = bt;
		delete bt;
		p = NULL;
	}
	else if (bt->leftChild == NULL)											//左子树为空
	{
		BiTreeNode<T>* p = bt;
		bt = bt->rightChild;
		delete p;
	}
	else if (bt->rightChild == NULL)										//右子树为空
	{
		BiTreeNode<T>* p = bt;
		bt = bt->leftChild;
		delete p;
	}
	else
	{
		BiTreeNode<T>* p = bt->leftChild;
		BiTreeNode<T>* parent = bt;
		while (p->rightChild)
		{
			parent = p;
			p = p->rightChild;
		}
		bt->data = p->data;
		if (parent != bt)
		{
			parent->rightChild = p->leftChild;
		}
		else
		{
			parent->leftChild = p->leftChild;
		}
	}
}
