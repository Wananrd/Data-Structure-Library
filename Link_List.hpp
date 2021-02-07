#pragma once
#include<iostream>
using namespace std;

//构造结点
template<class T>
struct LinkNode
{
	T data;
	LinkNode* next;
};

//链表的基本操作
//该链表是头结点
template<class T>
class LinkList
{
private:
	LinkNode<T>* head;		//头指针
public:
	LinkList();
	~LinkList();
	void Head_Insert();								//头插法创建链表
	void Tail_Insert();								//尾插法创建链表
	int Is_Empty();									//链表是否为空
	int Insert_pos(int pos, T val);					//按位置插入
	int Delete_pos(int pos);						//按位置删除
	int Search_val(int pos, T &ser);				//查看链表的值
	int Is_Exist(T val);							//查看val是否在单链表中
	int Change_val(int pos, T val);					//修改链表的值
	void Show();									//输出链表
	int LinkList_length();							//获取链表的长度
	void Destory();									//销毁链表
};

//带头结点的链表
template<class T>
LinkList<T>::LinkList()
{
	head = new LinkNode<T>;
	head->next = NULL;
}

template<class T>
LinkList<T>::~LinkList()
{
	Destory();
}


template<class T>
void LinkList<T>::Head_Insert()				//头插法创建链表
{
	int n;
	cout << "请输入链表的长度：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		LinkNode* temp = new LinkNode;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		LinkNode* p = head->next;
		temp->next = p;
		head->next = temp;
	}
}

template<class T>
void LinkList<T>::Tail_Insert()				//尾插法创建链表
{
	int n;
	cout << "请输入链表的长度：";
	cin >> n;
	LinkNode<T>* p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	for (int i = 0; i < n; i++)
	{
		LinkNode<T>* temp = new LinkNode<T>;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		temp->next = NULL;
		p->next = temp;
		p = temp;
	}
}


template<class T>
int LinkList<T>::Is_Empty()					//链表是否为空
{
	return head->next == NULL ? 1 : 0;
}


template<class T>
int LinkList<T>::Insert_pos(int pos, T val)			//按位置插入
{
	LinkNode* p = head;
	int j = 0;
	while (p && j < pos - 1)//寻找第i-1个结点
	{
		p = p->next;
		++j;
	}
	if (!p || j > pos - 1)//i小于1或者大于表长+1
	{
		return 0;
	}
	LinkNode* temp = new LinkNode;//生成新结点
	temp->data = val;		//插入L中
	temp->next = p->next;
	p->next = temp;
	return 1;
}

template<class T>
int LinkList<T>::Delete_pos(int pos)				//删除链表的值
{
	LinkNode<T>* p = head;
	int j = 0;
	while (p->next && j < pos - 1)				//寻找到第pos个结点，并另p指向他的前趋
	{
		p = p->next;
		++j;
	}
	if (!p->next || j > pos - 1)				//删除位置不合理
	{
		return 0;
	}
	LinkNode<T>* pDel = p->next;						//删除并释放
	p->next = pDel->next;
	delete pDel;
	return 1;
}

template<class T>
int LinkList<T>::Search_val(int pos, T& ser)				//查看链表的值
{
	LinkNode<T>* p = head->next;				//初始化，p指向第一个结点
	int j = 1;							//j为计数器
	while (p && j < pos)				//顺指针向后查找，直到p指向第i个元素或p为空
	{
		p = p->next;
		j++;
	}
	if (!p || j > pos)					//第i个元素不存在
	{
		return 0;
	}
	ser = p->data;						//取第i个元素
	return 1;
}

template<class T>
int LinkList<T>::Is_Exist(T val)						//查看val是否在单链表中，在的话，返回第几个，不在的话，返回0
{
	int pos = 0;
	if (!Is_Empty())
	{
		LinkNode* p = head;
		while (p)
		{
			if (p->data == val)
			{
				return pos;
			}
			p = p->next;
			pos++;
		}
		return 0;
	}
	else
	{
		return pos;
	}
}

template<class T>
int LinkList<T>::Change_val(int pos, T val)				//修改链表的值
{
	LinkNode* p = head->next;
	int j = 0;
	while (p && j < pos - 1)
	{
		j++;
		p = p->next;
	}
	if (!p || j > pos - 1)//位置不合理
	{
		return 0;
	}
	p->data = val;
	return 1;
}

template<class T>
void LinkList<T>::Show()					//输出链表
{
	if (Is_Empty())
	{
		cout << "链表为空" << endl;
		return;
	}
	LinkNode<T>* p = head->next;
	while (p != NULL)
	{
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}

template<class T>
int LinkList<T>::LinkList_length()			//获取链表的长度
{
	int length = 0;
	LinkNode<T>* p = head->next;
	while (p != NULL)
	{
		length++;
		p = p->next;
	}
	return length;
}

template<class T>
void LinkList<T>::Destory()					//销毁链表
{
	while (!Is_Empty())
	{
		Delete_pos(1);
	}
}
