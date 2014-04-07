#include <iostream>
using namespace std;

#define SLinkList Node*
#define MAXSIZE 20

struct Node
{
	Node() { data = 0; cur = 0; }
	char data;
	int cur;
};

// 初始化备用空间函数
// 算法: 2.14
void InitSpace_SL(SLinkList space)
{
	for (int i = 0; i < MAXSIZE - 1; i++)
		space[i].cur = i + 1;
}

// 分配备用空间函数
// 算法: 2.15
int Malloc_SL(SLinkList space)
{
	int i = space[0].cur;
	space[0].cur = space[i].cur;
	return i;
}

// 收回备用空间函数
// 算法: 2.16
void Free_SL(SLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

// 差集函数
// 算法: 2.17
void difference(SLinkList space, int &S)
{
	// 初始化备用空间
	InitSpace_SL(space);

	// 分配头结点、头指针、尾指针
	S = Malloc_SL(space);
	int p = S;
	int r = S;

	// 输入集合A、B的元素个数
	int m = 0, n = 0;
	cout << "A = "; cin >> m; 
	cout << "B = "; cin >> n; 

	// 建立A链表(在备用空间上，根据备用空间分配函数分配)
	for (int i = 0; i < m; i++)
	{
		r = Malloc_SL(space);
		cout << "A集合，第" << i + 1 << "个元素为"; cin >> space[r].data;
	}
	space[r].cur = 0;

	// 在A链表的基础上建立B链表，依次输入B的元素
	for (int i = 0; i < n; i++)
	{
		char B = 0;
		cout << "B集合，第" << i + 1 << "个元素为"; cin >> B;

		p = S; // p指向k的前一个节点(当前为头结点)
		int k = space[p].cur; // k指向第一个结点
		while (k != space[r].cur && space[k].data != B)
		{
			p = k;
			k = space[k].cur;
		}

		// i.  不在当前表中，则插入
		if (k == space[r].cur)
		{
			space[p].cur = Malloc_SL(space);
			k = space[p].cur;
			space[k].data = B;
			space[k].cur = 0;
			r = k;
		}
		else 	
		{
		 // ii. 在当前表中，则删除
			space[p].cur = space[k].cur;
			Free_SL(space, k);
		}
		
	}
}

// 输出集合
void output(SLinkList difference_AB, int &S)
{
	int p = 0;
	p = S;
	cout << "(A-B)U(B-A) : ";
	while (difference_AB[p].cur)
	{
		p = difference_AB[p].cur;
		cout << difference_AB[p].data << " ";
	}
	cout << endl;
}

int main()
{
	while (true) 
	{
		Node space[MAXSIZE];
		int S = 0;
		difference(space, S);
		output(space, S);
	}
	return 0;
}
