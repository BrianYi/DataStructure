#include "StaticSearchTable.h"
#include <iostream>
using namespace std;

// 构造一个含有n个数据元素的静态查找表
Status Create(SSTable &ST, int n)
{
	if (!(ST.elem = new SElemType[n + 1]))
		return ERROR;
	ST.length = n;
	cout << "请依次输入" << ST.length << "个元素:" << endl;
	for (int i = 1; i <= ST.length; i++)
		cin >> ST.elem[i].key;
	return OK;
}

// 销毁表ST
Status Destroy(SSTable &ST)
{
	if (ST.elem)
		delete[] ST.elem;
	ST.length = 0;
	return OK;
}

/* 顺序表查找——顺序查找 */
// 若找到，则返回表中的位置，否则返回0
int Search_Seq(SSTable &ST, KeyType key)
{
	ST.elem[0].key = key; // "哨兵"
	int i;
	for (i = ST.length; !EQ(ST.elem[i].key, key); i--); // 从后往前找
	return i; // 找不到时i为0
}

/* 有序表查找——折半查找 */
// 若找到，则返回表中的位置，否则返回0
int Search_Bin(SSTable &ST, KeyType key)
{
	int low = 1, high = ST.length, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (EQ(key, ST.elem[mid].key))
			return mid;
		else if (LT(key, ST.elem[mid].key))
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0; // 找不到时返回0
}

// 遍历顺序表
void Traverse(SSTable &ST, Status(*Visit)(SElemType &elem))
{
	for (int i = 1; i <= ST.length; i++)
		Visit(ST.elem[i]);
}

// Visit
Status Visit(SElemType &elem)
{
	cout << elem.key << " ";
	return OK;
}

// 选择排序(为折半查找准备的，由小到大排序)
void SelectSort(SSTable &ST)
{
	KeyType tmp;
	for (int i = 1; i <= ST.length - 1; i++)
	{
		for (int j = i + 1; j <= ST.length; j++)
		{
			if (ST.elem[i].key > ST.elem[j].key)
			{
				tmp = ST.elem[i].key;
				ST.elem[i].key = ST.elem[j].key;
				ST.elem[j].key = tmp;
			}
		}
	}
}



int main()
{
	SSTable ST;
	int len;
	cout << "您要创建的表中有多少数据元素？" << endl;
	cin >> len;
	if (!Create(ST, len))
		exit(0);
	cout << "当前表中的数据元素为: ";
	Traverse(ST, Visit);
	KeyType key;
	cout << "\n请输入您要查找的元素的key: ";
	cin >> key;

	int seqResult = Search_Seq(ST, key);
	cout << "顺序查找的结果为: ";
	if (!seqResult)
		cout << "没有该元素!" << endl;
	else
		cout << seqResult << endl;

	SelectSort(ST); // 从小到大排序，为折半查找做铺垫
	cout << "当前表中的数据元素为(排序后): ";
	Traverse(ST, Visit);
	int binResult = Search_Bin(ST, key);
	cout << "\n折半查找的结果为: ";
	if (!binResult)
		cout << "没有该元素!" << endl;
	else
		cout << binResult << endl;
	Destroy(ST);
	return 0;
}
