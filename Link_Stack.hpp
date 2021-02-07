#pragma once
#include<iostream>
using namespace std;

#include"Link_list.hpp"

template<class T>
class LinkStack
{
public:
	LinkStack();						//构造函数		置空栈
	~LinkStack();						//析构函数
	void Push(const T& val);		//压栈
	bool Pop(T& val);			//出栈
	bool Get_Top(T& val);		//获取栈顶元素
	bool Is_Empty();					//判空
	int Get_Size();						//求栈元素个数
	void Make_Empty();					//清空
private:
	LinkNode<T>* top;
};


template<class T>
LinkStack<T>::LinkStack()						//构造函数		置空栈
{
	top = NULL;
}

template<class T>
LinkStack<T>::~LinkStack()						//析构函数
{
	Make_Empty();
}

template<class T>
void LinkStack<T>::Push(const T& val)		//压栈
{
	LinkNode<T>* p = new LinkNode<T>;
	p->data = val;
	p->next = top;
	top = p;
}

template<class T>
bool LinkStack<T>::Pop(T& val)				//出栈
{
	if (Is_Empty())
	{
		return false;
	}
	LinkNode<T>* p = top;
	val = p->data;
	top = top->next;
	delete p;
	return true;
}

template<class T>
bool LinkStack<T>::Get_Top(T& val)		//获取栈顶元素
{
	if (Is_Empty())
	{
		return false;
	}
	val = top->data;
	return true;
}

template<class T>
bool LinkStack<T>::Is_Empty()					//判空
{
	if (top == NULL)
	{
		return true;
	}
	return false;
}

template<class T>
int LinkStack<T>::Get_Size()						//求栈元素个数
{
	int len = 0;
	LinkNode<T>* p = top;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

template<class T>
void LinkStack<T>::Make_Empty()					//清空
{
	LinkNode<T>* p;
	while (top != NULL)
	{
		p = top;
		top = top->next;
		delete p;
	}
}
