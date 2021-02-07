#pragma once
#include<iostream>
using namespace std;

template<class T>
struct CircLinkNode
{
	T data;
	CircLinkNode<T>* next;
};

template<class T>
class CircLinkList
{
public:
	CircLinkList();										//构造函数
	~CircLinkList();									//析构函数
	void Head_Insert();								//头插法创建链表
	void Tail_Insert();								//尾插法创建链表
	int Is_Empty();									//链表是否为空
	int Insert_pos(int pos, T val);			//按位置插入
	int Delete_pos(int pos);						//按位置删除
	int Search_val(int pos, T& ser);			//查看链表的值
	int Is_Exist(T val);						//查看val是否在单链表中
	int Change_val(int pos, T val);			//修改链表的值
	void Show();									//输出链表
	int LinkList_length();							//获取链表的长度
	void Destory();									//销毁链表
private:
	CircLinkNode<T>* first;
	CircLinkNode<T>* last;
};

template<class T>
CircLinkList<T>::CircLinkList()
{
	first = new CircLinkNode<T>;
	last = first;
	first->next = first;
}

template<class T>
CircLinkList<T>::~CircLinkList()
{
	while (first != last)
	{
		CircLinkNode<T>* p = first;
		last->next = first->next;
		first = first->next;
		delete p;
	}
}

template<class T>
void CircLinkList<T>::Head_Insert()								//头插法创建链表
{
	int n;
	cout << "请输入循环链表长度：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		CircLinkNode<T>* temp = new CircLinkNode<T>;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		temp->next = first->next;
		first->next = temp;
		if (first == last)
		{
			last = temp;
		}
	}
}

template<class T>
void CircLinkList<T>::Tail_Insert()			//尾插法创建链表
{
	int n;
	cout << "请输入循环链表的长度：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		CircLinkNode<T>* temp = new CircLinkNode<T>;
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> temp->data;
		temp->next = first;
		last->next = temp;
		last = temp;
	}
}

template<class T>
int CircLinkList<T>::Is_Empty()									//链表是否为空
{
	return first == last ? 1 : 0;
}

template<class T>
int CircLinkList<T>::Insert_pos(int pos, T val)			//按位置插入
{
	if (pos > LinkList_length() + 1)		//位置不合适
	{
		return 0;
	}
	int j = 0;
	CircLinkNode<T>* p = first;
	while (p->next != first && j < pos - 1)		//找到前一个
	{
		p = p->next;
		j++;
	}
	CircLinkNode<T>* temp = new CircLinkNode<T>;
	temp->data = val;
	temp->next = p->next;
	p->next = temp;
	if (p == last)			//在链尾的时候处理与前面不太一样
	{
		temp = last;
	}
	return 1;
}

template<class T>
int CircLinkList<T>::Delete_pos(int pos)						//按位置删除
{
	if (pos > LinkList_length())		//位置不合适
	{
		return 0;
	}
	int j = 0;
	CircLinkNode<T>* p = first;
	while (p->next != first && j < pos - 1)
	{
		p = p->next;
		j++;
	}
	CircLinkNode<T>* t = p->next;
	p->next = p->next->next;
	delete t;

	if (p->next == first)
	{
		last = p;
	}
	return 1;
}

template<class T>
int CircLinkList<T>::Search_val(int pos, T& ser)			//查看链表的值
{
	if (pos > LinkList_length())		//位置不合适
	{
		return 0;
	}
	int j = 1;
	CircLinkNode<T>* p = first->next;
	while (p->next != first && j < pos)
	{
		p = p->next;
		j++;
	}
	ser = p->data;
	return 1;
}

template<class T>
int CircLinkList<T>::Is_Exist(T val)						//查看val是否在单链表中
{
	int flag = 0;
	CircLinkNode<T>* p = first->next;
	while (p != first)
	{
		if (p->data == val)
		{
			flag = 1;
			break;
		}
		p = p->next;
	}
	return flag;
}

template<class T>
int CircLinkList<T>::Change_val(int pos, T val)			//修改链表的值
{
	if (pos > LinkList_length())		//位置不合适
	{
		return 0;
	}
	int j = 1;
	CircLinkNode<T>* p = first->next;
	while (p->next != first && j < pos)
	{
		p = p->next;
		j++;
	}
	p->data = val;
	return 1;
}

template<class T>
void CircLinkList<T>::Show()									//输出链表
{
	if (first == last)
	{
		cout << "循环链表为空" << endl;
	}
	CircLinkNode<T>* p = first->next;
	while (p != first)
	{
		cout << p->data << "\t";
		p = p->next;
	}
}

template<class T>
int CircLinkList<T>::LinkList_length()							//获取链表的长度
{
	int len = 0;
	CircLinkNode<T>* p = first->next;
	while (p != first)
	{
		len++;
		p = p->next;
	}
	return len;
}

template<class T>
void CircLinkList<T>::Destory()									//销毁链表
{
	while (!Is_Empty())
	{
		Delete_pos(1);
	}
}
