#include "HashSearch.h"
#include <iostream>
using namespace std;

// 闭散列表(哈希表)查找算法
int HashSearch1(int ht[], int m, int k)
{
	/* 直接定址法 */
	int j = H(k, m); // 计算散列地址
	if (ht[j] == k) // 没有发生冲突，一次便查找成功
		return j; 
	else if (ht[j] == Empty) // ht[j]为空，插入k(查找不成功)
	{
		ht[j] = k;
		return -1;
	}

	/* 处理冲突：线性探测法 */
	int i = (j + 1) % m; // 设置下一个探测的起始下标
	while (ht[i] != Empty && i != j)
	{
		if (ht[i] == k) // 比较若干次，查找成功
			return i;
		else
			i = (i + 1) % m; // 向后探测一个位置
	}

	if (i == j) //类似循环队列的原理，又到起点了
	{
		cout << "溢出!" << endl;
		exit(0);
	}
	else if (ht[i] == Empty) // ht[i]为空，插入k(查找不成功)
	{
		ht[i] = k;
		return -1;
	}
}

// 开散列表(哈希表)查找算法
Node *HashSearch2(Node *ht[], int m, int k)
{
	/* 直接定址法 */
	int j = H(k, m);
	Node *p = ht[j];
	while ((p != NULL) && (p->data != k))
		p = p->next;
	if (p != NULL && p->data == k) // 查找成功返回p
		return p;
	else // 查找不成功，插入k到表的表头(头插法)
	{
		/* 处理冲突：拉链法 */
		Node *s = new Node;
		s->data = k;
		s->next = ht[j];
		ht[j] = s;
		return NULL; // 返回空，代表查找不成功
	}
}

// 显示闭散列表
void display_HashSearch1(int ht[], int m)
{
	for (int i = 0; i < m; i++)
	{
		cout << "下标: " << i << ", 值: ";
		if (ht[i] != Empty)
			cout << ht[i] << endl;
		else
			cout << "空" << endl;
	}
}

// 显示开散列表
void display_HashSearch2(Node *ht[], int m)
{
	Node *p = NULL;
	for (int i = 0; i < m; i++)
	{
		cout << "下标: " << i << ", 值: ";
		p = ht[i];
		if (p == NULL)
			cout << "空" << endl;
		else
		{
			while (p != NULL)
			{
				cout << p->data;
				p = p->next;
				if (p != NULL)
					cout << " -> ";
			}
			cout << endl;
		}
	}
}

// 计算散列地址
int H(int k, int m)
{
	return k % m;
}

int main()
{
	int m;
	cout << "您要输入多少个数字?" << endl;
	cin >> m;
	int *ht = new int[m];
	Node **ht2 = new Node*[m];
	for (int i = 0; i < m; i++)
	{
		ht[i] = Empty;
		ht2[i] = NULL;
	}
	int len = m;
	while (len--)
	{
		cout << "请输入您要查找的数: ";
		int k;
		cin >> k;
		int result = HashSearch1(ht, m, k);
		Node *result2 = HashSearch2(ht2, m, k);

		if (result == Empty)
			cout << "在闭散列表中没有这个数，已经成功插入到表中。" << endl;
		else
			cout << k << "在闭散列表中的下标为" << result << endl;

		if (result2 == NULL)
			cout << "在开散列表中没有这个数，已经成功插入到表中。" << endl;
		else
			cout << k << "在开散列表中的下标为" << H(k, m) << endl;
	}
	cout << "\n闭散列表中的数据如下: " << endl;
	display_HashSearch1(ht, m);
	cout << "\n开散列表中的数据如下: " << endl;
	display_HashSearch2(ht2, m);

	delete[] ht;
	for (int i = 0; i < m; i++)
		delete [] ht2[i];
	delete[] ht2;
	return 0;
}
