#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define MAXSTRLEN 1000
typedef struct SString{
	char *ch;
	int length;
	SString() { ch = 0; length = 0; }
	char& operator [](int pos)
	{
		if (pos > this->length || ch == 0)
			throw;
		else
			return ch[pos];
	}
};


Status StrInsert(SString &S, int pos, SString T); // 在S串中pos的位置之前插入T串
Status StrAssign(SString &T, char *chars);  // 生成一个其值等于串常量chars的串T
int StrLength(SString S); // 返回S的元素个数，称为串的长度
int StrCompare(SString S, SString T); // 若S > T, 则返回值 > 0; 若S = T, 则返回值 = 0; 若S < T, 则返回值 < 0 
Status ClearString(SString &S); // 将S清为空串，并释放S所占空间
Status Concat(SString &T, SString S1, SString S2); // 用T返回由S1和S2联接而成的新串
SString SubString(SString S, int pos, int len); // 返回串S的第pos个字符起长度为len的字串
