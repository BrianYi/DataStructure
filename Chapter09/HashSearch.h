#pragma once

#define Empty -1

struct Node {
	Node() { data = Empty;  next = 0; }
	int data;
	Node* next;
};

int HashSearch1(int ht[], int m, int k); // 闭散列表(哈希表)查找算法
Node *HashSearch2(Node *ht[], int m, int k); // 开散列表(哈希表)查找算法
int H(int k, int m); // 计算散列地址

void display_HashSearch1(int ht[], int m); // 显示闭散列表
void display_HashSearch2(Node *ht[], int m); // 显示开散列表
