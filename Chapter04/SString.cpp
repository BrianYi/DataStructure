#include "SString.h"
#include<iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

// 在S串中pos的位置之前插入T串
// 算法 4.4
Status StrInsert(SString &S, int pos, SString T)
{
	if (pos < 1 || pos > S.length + 1)
		return ERROR;
	if (T.length)
	{
		if (!(S.ch = (char*)realloc(S.ch, (S.length + T.length) * sizeof(char) + 2)))
			exit(OVERFLOW);
		for (int i = S.length; i >= pos; i--) // 将S串（只取S原串的后pos个字符）后移T串的长度
			S.ch[i + T.length] = S.ch[i];
		memcpy(S.ch + pos, T.ch+1, T.length); // 将T串插入其中
		S.length += T.length;
		S[0] = S.length;
		S.ch[S.length + 1] = NULL;
	}
	return OK;
}


// 生成一个其值等于串常量chars的串T
Status StrAssign(SString &T, char *chars)
{
	if (T.ch)
		free(T.ch);
	char *p = chars;
	int i = 0;
	for (i = 0; *p; i++, p++);
	if (!i)
	{
		T.ch = NULL;
		T.length = 0;
	}
	else
	{
		if (!(T.ch = (char*)malloc(i * sizeof(chars) + 2)))
			exit(OVERFLOW);
		memcpy(T.ch+1, chars, i);
		T.length = i;
		T[0] = T.length;

		T.ch[T.length + 1] = NULL;
		
	}
	return OK;
}

// 返回S的元素个数，称为串的长度
int StrLength(SString S)
{
	return S.length;
}

// 若S > T, 则返回值 > 0; 若S = T, 则返回值 = 0; 若S < T, 则返回值 < 0 
int StrCompare(SString S, SString T)
{
	for (int i = 1; i <= S.length && i <= T.length; i++)
	{
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}

// 将S清为空串，并释放S所占空间
Status ClearString(SString &S)
{
	if (S.ch)
	{
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}

// 用T返回由S1和S2联接而成的新串
// 算法 4.2
Status Concat(SString &T, SString S1, SString S2)
{
	if (T.ch)
		free(T.ch);
	if (!(T.ch = (char*)malloc((S1.length + S2.length + 2)*sizeof(char))))
		exit(OVERFLOW);
	memcpy(T.ch+1, S1.ch+1, S1.length);
	memcpy(T.ch+1 + S1.length, S2.ch+1, S2.length);
	T.length = S1.length + S2.length;

	T.ch[T.length + 1] = NULL;
	
	return OK;
}

// 返回串S的第pos个字符起长度为len的字串
// 算法 4.3
Status SubString(SString &Sub, SString S, int pos, int len)
{
	if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
		return ERROR;
	if (Sub.ch)
		free(Sub.ch);
	if (!len)
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}
	else
	{
		Sub.ch = (char *)malloc(len * sizeof(char) + 2);
		memcpy(Sub.ch+1, S.ch + pos, len);
		Sub.length = len;

		Sub.ch[Sub.length + 1] = NULL;
	}
	return OK;
}


// 返回子串T在主串S中第pos个字符之后的位置（下标）。若不存在，则函数值为0。其中，T非空，1≤pos≤StrLength(S)
// 算法 4.5 
int Index(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	if (pos < 1 || pos > S.length)
		return 0;
	while (i <= S[0] && j <= T[0])
	{
		if (S[i] == T[j]) { ++i; ++j; }
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}

	if (j > T[0])
		return i - T[0];
	else
		return 0;
}


// 算法 4.6
int Index_KMP(SString S, SString T, int pos, int *next)
{
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j]) { ++i; ++j; }
		else
			j = next[j];
		
	}

	if (j > T[0])
		return i - T[0];
	else
		return 0; 
}


// 算法 4.7
void get_next(SString T, int *next)
{
	int i = 1, j = 0;
	next[1] = 0;
	
	while (i < T[0])
	{
		if (j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

// 算法 4.8
void get_nextval(SString T, int nextval[])
{
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < T[0])
	{
		if (j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			if (T[i] != T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}
/*
 * 显然，KMP算法比普通算法要快很多。
 * 不知道为什么，我发现KMP算法和改进后的KMP算法的时间消耗是一样的，可能字符串太短了吧。。。
 */
int main()
{
	while (true)
	{
		SString S;
		SString T;
		StrAssign(S, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
		StrAssign(T, "aaaab");

		cout << "S: " << S.ch + 1 << endl;
		cout << "T: " << T.ch + 1 << endl;

		// 普通算法
		long n = 1;
		clock_t start = clock(); //开始时间
		for (int i = 0; i < 1000; i++)
			Index(S, T, 1);
		clock_t finish = clock();   //结束时间
		double duration = (finish - start);
		printf("Time for algorithm(普通的算法匹配1000次): %lf s\n", duration / 1000);

		// KMP算法
		int *next = new int[T.length * sizeof(int)+1];
		get_next(T, next);
		start = clock(); //开始时间
		for (int i = 0; i < 1000; i++)
			Index_KMP(S, T, 1, next);
		finish = clock();   //结束时间
		duration = (finish - start);
		printf("Time for algorithm(KMP的算法匹配1000次): %lf s\n", duration / 1000);

		cout << "KMP-next: ";
		for (int i = 1; i <= T.length; i++)
			cout << next[i] << " ";
		cout << endl;

		// KMP改进算法
		get_nextval(T, next);
		start = clock(); //开始时间
		for (int i = 0; i < 1000; i++)
			Index_KMP(S, T, 1, next);
		finish = clock();   //结束时间
		duration = (finish - start);
		printf("Time for algorithm(KMP的算法改进后的匹配1000次): %lf s\n", duration / 1000);

		cout << "KMP-next(改进后的): ";
		for (int i = 1; i <= T.length; i++)
			cout << next[i] << " ";
		cout << endl;

		delete[] next;
		ClearString(S);
		ClearString(T);

		getchar(); // 按任意键继续显示
	}
	return 0;
}
