#pragma once

#include "typedefine.h"


// 表
typedef struct {
	SElemType *elem;
	int		  length;
}SSTable; 

// 构造一个含有n个数据元素的静态查找表
Status Create(SSTable &ST, int n);

// 销毁表ST
Status Destroy(SSTable &ST);

/* 顺序表查找——顺序查找 */
// 若找到，则返回表中的位置，否则返回0
int Search_Seq(SSTable &ST, KeyType key);

/* 有序表查找——折半查找 */
// 若找到，则返回表中的位置，否则返回0
int Search_Bin(SSTable &ST, KeyType key);

// 遍历顺序表
void Traverse(SSTable &ST, Status(*Visit)(SElemType &elem));

// Visit
Status Visit(SElemType &elem);

// 选择排序(为折半查找准备的，由小到大排序)
void SelectSort(SSTable &ST);


/* 静态树表的查找——静态最优查找树(以后有时间补上)、次优查找树(以后有时间补上) */
