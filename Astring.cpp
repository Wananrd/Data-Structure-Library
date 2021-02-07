#include"Astring.h"

Astring::Astring()
{
	charLen = 0;
	maxSize = MAXSIZE;
	ch = new char[maxSize + 1];
}


Astring::Astring(const char* init)
{
	int len = 0;
	while (init[len] != '\0')
	{
		len++;
	}
	maxSize = (len > MAXSIZE) ? len : MAXSIZE;
	ch = new char[maxSize + 1];
	if (ch == NULL)
	{
		cerr << "分配失败！" << endl;
		exit(1);
	}
	charLen = len;
	for (int i = 0; i < len; i++)
	{
		ch[i] = init[i];
	}
	ch[len] = '\0';
}

Astring::Astring(const Astring& ob)					//复制构造函数
{
	maxSize = (ob.charLen > MAXSIZE) ? ob.charLen : MAXSIZE;
	charLen = ob.charLen;
	ch = new char[maxSize + 1];
	for (int i = 0; i < ob.charLen; i++)
	{
		ch[i] = ob.ch[i];
	}
	ch[charLen] = '\0';
}

Astring::~Astring()
{
	delete[]ch;
}

int Astring::Length()const							//返回字符串的长度
{
	return charLen;
}

Astring Astring::operator()(int pos, int len)		//指出从pos开始到pos+len的字符串
{
	Astring p;
	if (pos < 0 || pos + len - 1 >= maxSize || len < 0)
	{
		p.ch[0] = '\0';
		p.charLen = 0;
	}
	else
	{
		if (pos + len - 1 >= charLen)
		{
			len = charLen - pos;
		}
		p.charLen = len;
		for (int i = 0; i < len; i++)
		{
			p.ch[i] = this->ch[i + pos];
		}
		p.ch[len] = '\0';
	}
	return p;
}

int Astring::operator==(Astring& ob)				//判断两串是否相等
{
	if (this->charLen == ob.charLen)
	{
		int flag = 1;
		for (int i = 0; i < charLen; i++)
		{
			if (this->ch[i] != ob.ch[i])
			{
				flag = 0;
				break;
			}
		}
		return flag;
	}
	return 0;
}

int Astring::operator!=(Astring& ob)				//判断两串是否不等
{
	if (this == &ob)
	{
		return 0;
	}
	return 1;
}

Astring& Astring::operator=(Astring& ob)			//字符串赋值
{
	if (this != &ob)
	{
		delete[]ch;
		maxSize = (ob.charLen > MAXSIZE) ? ob.charLen : MAXSIZE;
		charLen = ob.charLen; 
		ch = new char[maxSize + 1];
		if (ch == NULL)
		{
			cerr << "存储分配失败！\n";
			exit(1);
		}
		for (int i = 0; i < charLen; i++)
		{
			ch[i] = ob.ch[i];
		}
		ch[charLen] = '\0';
	}
	else
	{
		cout << "字符串自身赋值出错！\n";
	}
	return *this;
}

Astring Astring::operator+=(Astring& ob)			//把串ob接在串*this后面
{
	if (this->charLen + ob.charLen <= this->maxSize)
	{
		for (int i = 0; i < ob.charLen; i++)
		{
			this->ch[i + charLen] = ob.ch[i];
		}
		this->charLen += ob.charLen;
		this->ch[this->charLen] = '\0';
	}
	else
	{
		this->maxSize += ob.maxSize;
		for (int i = 0; i < ob.charLen; i++)
		{
			this->ch[i + charLen] = ob.ch[i];
		}
		this->charLen += ob.charLen;
		this->ch[this->charLen] = '\0';
	}
	return *this;
}

Astring Astring::operator+(Astring& ob)			//把串ob接在串*this后面
{
	if (this->charLen + ob.charLen <= this->maxSize)
	{
		for (int i = 0; i < ob.charLen; i++)
		{
			this->ch[i + charLen] = ob.ch[i];
		}
		this->charLen += ob.charLen;
		this->ch[this->charLen] = '\0';
	}
	else
	{
		this->maxSize += ob.maxSize;
		for (int i = 0; i < ob.charLen; i++)
		{
			this->ch[i + charLen] = ob.ch[i];
		}
		this->charLen += ob.charLen;
		this->ch[this->charLen] = '\0';
	}
	return *this;
}

char& Astring::operator[](int i)					//取第i个字符
{
	return this->ch[i];
}

int Astring::Find(Astring& pat)const				//字符串匹配（BF算法）
{
	int i = 0, j = 0;
	while (this->ch[i] != '\0' && pat.ch[j] != '\0')
	{
		if (this->ch[i] == pat.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (pat.ch[j] == '\0')
	{
		return (i - j);
	}
	else
	{
		return -1;
	}
}

void getNext(char *T, int* next,int len)
{
	int j = -1;				//j前缀
	int i = 0;				//i后缀
	next[0] = -1;
	while (i < len)
	{
		if (j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

int Astring::find(Astring& pat)const						//字符串匹配（KMP算法）
{
	int i = 0, j = 0;										//1.在串S和串T中分别设比较的起始下标i和j
	int lenS = this->charLen;
	int lenT = pat.charLen;
	int* next = new int[lenT + 1];
	getNext(pat.ch, next,pat.charLen);
	while (i < lenS && j < lenT)							//2.循环直到S或T的所有字符均未比较完
	{
		if (j==-1||this->ch[i] == pat.ch[j])					//2.1如果S[i]==T[i]，继续比较S和T的下一个字符
		{														//2.3如果 j=-1 ，则将i和j分别加1，准备下一趟比较
			i++;
			j++;
		}
		else													//2.2否则将j向右滑动到next[j]位置，即 j=next[j]
		{
			j = next[j];
		}
	}
	if (j == lenT)									//3.如果T中所有字符均比较完毕，则返回匹配的起始下标（i - T串长）
	{
		return (i - j);
	}
	else													//否则返回-1
	{
		return -1;
	}
}

ostream& operator<<(ostream& cout, Astring& ob)
{
	for (int i = 0; i < ob.Length(); i++)
	{
		cout << ob[i];
	}
	return cout;
}
