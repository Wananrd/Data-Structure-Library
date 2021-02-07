#pragma once
#include<iostream>
using namespace std;

#define MAXSIZE 128		//字符串的最大长度

class Astring
{
public:
	Astring();
	Astring(const char* init);
	Astring(const Astring& ob);					//复制构造函数
	~Astring();
	int Length()const;							//返回字符串的长度
	Astring operator()(int pos, int len);		//指出从pos-1开始到pos+len-1的字符串
	int operator==(Astring& ob);				//判断两串是否相等
	int operator!=(Astring& ob);				//判断两串是否不等
	Astring& operator=(Astring& ob);			//字符串赋值
	Astring operator+=(Astring& ob);			//把串ob接在串*this后面
	Astring operator+(Astring& ob);
	char& operator[](int i);					//取第i个字符
	int Find(Astring& pat)const;				//字符串匹配（BF算法）
	int find(Astring& pat)const;				//字符串匹配（KMP算法）
private:
	char* ch;									//串存放数组
	int charLen;								//串的实际长度
	int maxSize;								//存放数组的最大长度
};

ostream& operator<<(ostream& cout, Astring& ob);//左移运算
												//不会利用成员函数重载<<运算符，因为无法实现cout<<在左边
