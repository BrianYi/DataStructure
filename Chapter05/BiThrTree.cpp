#include "BiThrTree.h"
#include <iostream>
using namespace std;

/*这个线索二叉树程序我没有按原书的程序写，把头结点给去掉了*/

// 构造空线索二叉树
void InitBiThrTree(BiThrTree& T)
{
	T = (BiThrNode*)malloc(sizeof(BiThrNode));
}

// 销毁线索二叉树--按中序遍历
void DestroyBiThrTree(BiThrTree& T)
{
	BiThrNode *p = T;
	BiThrNode *q = NULL;
	while (p != NULL)
	{
		while (p->LTag == Link)
			p = p->lchild;
		q = p;
		while (p->RTag == Thread && p->rchild != NULL)
		{
			p = p->rchild;
			Visit(q->data);
			delete q;
			q = p;
		}
		p = p->rchild;
		Visit(q->data);
		delete q;
		q = p;
	}
}

// 构造线索二叉树, 按先(前)序遍历  （根左右）
void CreateBiThrTree(BiThrTree& T)
{
	TElemType ch;
	cin >> ch;
	if (ch == '#')
		T = NULL;
	else
	{
		T = (BiThrNode*)malloc(sizeof(BiThrNode));
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);
		CreateBiThrTree(T->rchild);
	}
}

// 先序遍历T，并将其中序线索化，对每个结点调用函数Visit一次
Status PreOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e))
{
	/*有时间再补上*/
	return OK;
}

// 中序遍历T，并将其中序线索化，对每个结点调用函数Visit一次
Status InOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e))
{
	BiThrNode *p = T;
	while (p != NULL)
	{
		while (p->LTag == Link)
			p = p->lchild;
		Visit(p->data);
		while (p->RTag == Thread && p->rchild != NULL)
		{
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}

// 后序遍历T，并将其中序线索化，对每个结点调用函数Visit一次
Status PostOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e))
{
	/*有时间再补上*/
	return OK;
}

// 层序遍历T，并将其中序线索化，对每个结点调用函数Visit一次
Status LevelOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e))
{
	/*有时间再补上*/
	return OK;
}

// 先序线索化
void PreOrderThreading(BiThrTree p)
{
	/*有时间再补上*/
}

// 中序线索化
void InOrderThreading(BiThrTree p)
{
	if (p)
	{
		InOrderThreading(p->lchild);
		if (p->lchild == NULL) // 当前，只能知道当前的结点的前驱是pre
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (pre != NULL && pre->rchild == NULL) // 当前，只能知道前驱的后继是当前的结点p
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InOrderThreading(p->rchild);
	}
}

// 后序线索化
void PostOrderThreading(BiThrTree p)
{
	/*有时间再补上*/
}

// 层序线索化
void LevelOrderThreading(BiThrTree p)
{
	/*有时间再补上*/
}

Status Visit(TElemType e)
{
	cout << e << " ";
	return OK;
}

int main()
{
	BiThrTree T;
	CreateBiThrTree(T);
	InOrderThreading(T);

	cout << "InOrderTraverse :";
	InOrderTraverse(T, Visit);
	cout << endl;

	cout << "DestroyBiThrTree :";
	DestroyBiThrTree(T);
	cout << endl;
	return 0;
}
