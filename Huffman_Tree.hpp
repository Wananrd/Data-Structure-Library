#pragma once
#include<iostream>
using namespace std;

typedef char ElemName;

//哈夫曼编码思想：1.初始化
//				  2.选取与合并
//				  3.删除与插入
//				  4.重复2.3.

struct HuffmanTree
{
	ElemName data;									//数据
	int weight, parent, leftChild, rightChild;		//权值，父亲结点，左右孩子结点
};

class HuffmanCode
{
public:
	HuffmanCode();									//初始化
	void PrintHufCode();							//输出哈夫曼编码
	~HuffmanCode();
private:
	void Select(HuffmanTree *t[],int &m,int &n);		//选取与合并
	void Code();										//进行编码
	int nums;											//结点数
	HuffmanTree** tree;									//一维指针数组
	ElemName** code;									//一维指针数组
};

HuffmanCode::HuffmanCode()									//初始化,创建哈夫曼树
{
	cout << "请输入结点个数：";
	cin >> nums;
	cout << "请输入数据：";
	tree = new HuffmanTree * [2 * nums - 1];
	for (int i = 0; i < 2 * nums - 1; i++)
	{
		tree[i] = new HuffmanTree;
		tree[i]->parent = -1;
		tree[i]->leftChild = -1;
		tree[i]->rightChild = -1;
	}
	for (int i = 0; i <nums; i++)
	{
		tree[i]->weight = -1;
		cin >> tree[i]->data;
	}
	cout << "请输入权值：";
	for (int i = 0; i < nums; i++)
	{
		cin >> tree[i]->weight;
	}
	for (int i = nums; i < 2 * nums - 1; i++)
	{
		int min1 = 0, min2 = 1;
		Select(tree,min1, min2);
		tree[min1]->parent = i;
		tree[min2]->parent = i;
		tree[i]->leftChild = min1;
		tree[i]->rightChild = min2;
		tree[i]->weight = tree[min1]->weight + tree[min2]->weight;
	}
}

void HuffmanCode::Select(HuffmanTree *t[], int& m, int& n)							//选取两个最小值
{
	static int num = nums;
	int min1 = 1000, min2 = 1000;
	for (int i = 0; i < num ; i++)
	{
		if (min1 > t[i]->weight && t[i]->parent == -1)
		{
			m = i;
			min1 = t[i]->weight;
		}
	}
	for (int i = 0; i < num ; i++)
	{
		if (min2 > t[i]->weight && t[i]->parent == -1 && i != m)
		{
			n = i;
			min2 = t[i]->weight;
		}
	}
	num++;
}

//编码思路：从根结点往上走直到无双亲结点
//			编码从后往前编
void HuffmanCode::Code()									//进行编码
{
	code = new char* [nums];
	char* temp = new char[nums];
	temp[nums - 1] = '\0';
	for (int i = 0; i < nums; i++)							//进行nums次编码
	{
		int start = nums - 1;								//从后往前记录
		int work = i;										//work是当前正在处理的结点
		int prt = tree[work]->parent;
		while (prt != -1)
		{
			if (tree[prt]->leftChild == work)
			{
				temp[--start] = '0';
			}
			if (tree[prt]->rightChild == work)
			{
				temp[--start] = '1';
			}
			work = prt;
			prt = tree[work]->parent;
		}
		code[i] = new char[nums - start];
		for (int j = 0; j < nums - start; j++)
		{
			code[i][j] = temp[start + j];
		}
	}
	delete []temp;
}


void HuffmanCode::PrintHufCode()							//输出哈夫曼编码
{
	Code();
	for (int i = 0; i < nums; i++)
	{
		cout << tree[i]->data << ":";
		int j = 0;
		while (code[i][j] != '\0')
		{
			cout << code[i][j] << "";
			j++;
		}
		cout << endl;
	}
}

HuffmanCode::~HuffmanCode()
{
	for (int i = 0; i < nums; i++)
	{
		delete[]tree[i];
		tree[i] = NULL;
		delete[]code[i];
		code[i] = NULL;
	}
	delete[]tree;
	tree = NULL;
	delete[]code;
	code = NULL;
}
