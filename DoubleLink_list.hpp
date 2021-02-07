#pragma once
#include<iostream>
using namespace std;

template<class T>
struct DblNode
{
	DblNode<T>* lLink;		//左指针
	T data;		//数据
	DblNode<T>* rLink;		//右指针
};

template<class T>
class DblList
{
public:
	DblList();
	~DblList();
	void Head_Insert();								//头插法创建链表
	void Tail_Insert();								//尾插法创建链表
	int Is_Empty();									//链表是否为空
	int Insert_pos(int pos, T val);					//按位置插入
	int Delete_pos(int pos);						//按位置删除
	int Search_val(int pos, T& ser);				//查看链表的值
	int Is_Exist(T val);							//查看val是否在单链表中
	int Change_val(int pos, T val);					//修改链表的值
	void Show();									//输出链表
	int LinkList_length();							//获取链表的长度
	void Destory();									//销毁链表
private:
	DblNode<T>* first;
};

template<class T>
DblList<T>::DblList()
{
	first = new DblNode<T>;
	first->lLink = first;
	first->rLink = first;
}

template<class T>
DblList<T>::~DblList()
{
	while (first->rLink != first)
	{
		DblNode<T>* p = first->rLink;
		first->rLink = p->rLink;
		delete p;
	}
	delete first;
}

template<class T>
void DblList<T>::Head_Insert()								//头插法创建链表
{
	int n;
	cout << "请输入双向循环链表长度：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		DblNode<T>* temp = new DblNode<T>;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		temp->rLink = first->rLink;
		temp->lLink = first;
		first->rLink = temp;
		if (i == 0)
		{
			first->lLink = temp;
		}
	}
}

template<class T>
void DblList<T>::Tail_Insert()								//尾插法创建链表
{
	int n;
	cout << "请输入双向循环链表长度：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		DblNode<T>* temp = new DblNode<T>;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		temp->rLink = first;
		temp->lLink = first->lLink;
		first->lLink->rLink = temp;
		first->lLink = temp;
	}
}

template<class T>
int DblList<T>::Is_Empty()									//链表是否为空
{
	return first->rLink == first ? 1 : 0;
}

template<class T>
int DblList<T>::Insert_pos(int pos, T val)			//按位置插入
{
	if (pos > LinkList_length() + 1)
	{
		return 0;
	}
	int j = 0;
	DblNode<T>* p = first;
	while (p->rLink != first && j < pos - 1)
	{
		j++;
		p = p->rLink;
	}
	DblNode<T>* temp = new DblNode<T>;
	temp->data = val;
	temp->rLink = p->rLink;
	temp->lLink = p;
	temp->rLink->lLink = temp;
	p->rLink = temp;
	return 1;
}

template<class T>
int DblList<T>::Delete_pos(int pos)						//按位置删除
{
	if (pos > LinkList_length())
	{
		return 0;
	}
	int j = 0;
	DblNode<T>* p = first;
	while (p->rLink != first && j < pos - 1)
	{
		j++;
		p = p->rLink;
	}
	DblNode<T>* pDelete = p->rLink;
	p->rLink = p->rLink->rLink;
	p->rLink->rLink->lLink = p;
	delete pDelete;
	return 1;
}

template<class T>
int DblList<T>::Search_val(int pos, T& ser)			//查看链表的值
{
	if (pos > LinkList_length())
	{
		return 0;
	}
	int j = 1;
	DblNode<T>* p = first->rLink;
	while (p != first && j < pos)
	{
		j++;
		p = p->rLink;
	}
	ser = p->data;
	return 1;
}

template<class T>
int DblList<T>::Is_Exist(T val)						//查看val是否在单链表中
{
	DblNode<T>* p = first->rLink;
	while (p != first)
	{
		if (p->data == val)
		{
			return 1;
		}
		p = p->rLink;
	}
	return 0;
}

template<class T>
int DblList<T>::Change_val(int pos, T val)			//修改链表的值
{
	if (pos > LinkList_length())
	{
		return 0;
	}
	int j = 1;
	DblNode<T>* p = first->rLink;
	while (p != first && j < pos)
	{
		j++;
		p = p->rLink;
	}
	p->data = val;
	return 1;
}

template<class T>
void DblList<T>::Show()									//输出链表
{
	DblNode<T>* p = first->rLink;
	if (p == first)
	{
		cout << "双向循环链表为空" << endl;
	}
	while (p != first)
	{
		cout << p->data << "\t";
		p = p->rLink;
	}
}

template<class T>
int DblList<T>::LinkList_length()							//获取链表的长度
{
	if (first->rLink == first)
	{
		return 0;
	}
	int len = 1;
	DblNode<T>* p = first->rLink;
	while (p->rLink != first)
	{
		len++;
		p = p->rLink;
	}
	return len;
}

template<class T>
void DblList<T>::Destory()									//销毁链表
{
	while (!Is_Empty())
	{
		Delete_pos(1);
	}
}
