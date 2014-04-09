#include "CrossList.h"
#include <iostream>
using namespace std;

// 将十字链表以稀疏矩阵的方式显示出来
void displayCrossList(CrossList &M)
{
	OLink *ptrRhead = M.rhead;
	
	for (int i = 1; i <= M.mu; i++)
	{
		for (int j = 1; j <= M.nu; j++)
		{
			if (ptrRhead[i] && ptrRhead[i]->j == j)
			{
				cout << ptrRhead[i]->e << "\t";
				ptrRhead[i] = ptrRhead[i]->right; // 移向下一个
			}
			else
				cout << "0\t";
		}
		cout << endl;
	}
}

// 判定十字链表是否为空表
bool isNoContent(CrossList &M)
{
	if (M.tu == 0)
		return true;
	else 
		return false;
}

// 摧毁十字链表,释放空间
void DestroyCrossList(CrossList &M)
{
	// 释放行空间
	for (int i = 1; i <= M.mu; i++)
	{
		if (M.rhead[i])
		{
			OLink p = M.rhead[i];
			OLink q = NULL;
			while (p)
			{
				q = p;
				p = p->right;
				free(q);
			}
		}
		M.rhead[i] = NULL;
	}
	// 释放列空间
	for (int j = 1; j <= M.nu; j++)
	{
		if (M.chead[j])
		{
			OLink p = M.chead[j];
			OLink q = NULL;
			while (p)
			{
				q = p;
				p = p->down;
				free(q);
			}
		}
		M.chead[j] = NULL;
	}
}

//算法 5.4 创建十字链表
Status CreateSMatrix_OL(CrossList &M)
{
	if (!isNoContent(M))
	{
		DestroyCrossList(M);
	}
	int m, n, t;
	cout << "请输入稀疏矩阵行数：";
	cin >> m;
	cout << "请输入稀疏矩阵列数: ";
	cin >> n;
	cout << "请输入稀疏矩阵非零元个数: ";
	cin >> t;
	M.mu = m;
	M.nu = n;
	M.tu = t;
	if (!(M.rhead = (OLink*)malloc((m + 1)*sizeof(OLink))))
		exit(OVERFLOW);
	if (!(M.chead = (OLink*)malloc((n + 1)*sizeof(OLink))))
		exit(OVERFLOW);

	for (int i = 1; i <= M.mu; i++)
		M.rhead[i] = NULL;
	for (int j = 1; j <= M.nu; j++)
		M.chead[j] = NULL;

	int i, j, e, count = 1;
	OLNode *p = NULL;
	OLNode *q = NULL;
	cout << "请依次输入 " << t << " 个非零元三元组: " << endl;
	for (; count <= t; count++)
	{
		cin >> i >> j >> e;

		if (!(p = (OLNode *)malloc(sizeof(OLNode))))
			exit(OVERFLOW);
		
		p->i = i;
		p->j = j;
		p->e = e;

		if (M.rhead[i] == NULL || M.rhead[i]->j > j)
		{
			p->right = M.rhead[i];
			M.rhead[i] = p;
		}
		else
		{
			for (q = M.rhead[i]; (q->right) && q->right->j < j; q = q->right);

			p->right = q->right;
			q->right = p;
		}

		if (M.chead[j] == NULL || M.chead[j]->i > i)
		{
			p->down = M.chead[j];
			M.chead[j] = p;
		}
		else
		{
			for (q = M.chead[j]; (q->down) && q->down->i < i; q = q->down);

			p->down = q->down;
			q->down = p;
		}
	}
	return OK;
}

/*
由于时间有限，加法运算以后再补上吧
*/
void CrossListAddition()
{

}

int main()
{
	CrossList M;
	CreateSMatrix_OL(M);
	cout << "稀疏矩阵如下: " << endl;
	displayCrossList(M);
	DestroyCrossList(M);
	return 0;
}
