#pragma once
#include<iostream>
using namespace std;

#include"Link_list.hpp"

template<class T>
class LinkQueue
{
public:
	LinkQueue();
	~LinkQueue();
	bool EnQueue(T& x);		//入队
	bool DeQueue(T& x);				//出队
	bool GetFront(T& x)const;		//查看队头元素的值
	void Make_Empty();				//置空队列
	bool Is_Empty();				//判空
	int Get_Size();					//获取长度
private:
	LinkNode<T>* front;
	LinkNode<T>* rear;
};

template<class T>
LinkQueue<T>::LinkQueue()
{
	front = NULL;
	rear = front;
}

template<class T>
LinkQueue<T>::~LinkQueue()
{
	Make_Empty();
}

template<class T>
bool LinkQueue<T>::EnQueue(T &x)		//入队
{
	LinkNode<T>* p = new LinkNode<T>;
	p->data = x;
	p->next = NULL;
	if (front == NULL)
	{
		front = p;
		rear = p;
	}
	else
	{
		rear->next = p;
		rear = p;
	}
	return true;
}

template<class T>
bool LinkQueue<T>::DeQueue(T& x)				//出队
{
	if (Is_Empty())
	{
		return false;
	}
	LinkNode<T>* p = front;
	x = p->data;
	front = front->next;
	delete p;
	return true;
}

template<class T>
bool LinkQueue<T>::GetFront(T& x)const			//查看队头元素的值
{
	if (Is_Empty())
	{
		return fasle;
	}
	x = rear->data;
	return true;
}

template<class T>
void LinkQueue<T>::Make_Empty()								//置空队列
{
	LinkNode<T>* p;
	while (front!=NULL)
	{
		p = front;
		front = front->next;
		delete p;
	}
}

template<class T>
bool LinkQueue<T>::Is_Empty()				//判空
{
	return front == NULL ? true : false;
}

template<class T>
int LinkQueue<T>::Get_Size()					//获取长度
{
	int len = 0;
	LinkNode<T>* p = front;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}
