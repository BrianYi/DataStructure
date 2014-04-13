#include "BinaryTree.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
using namespace std;

// 构造空二叉树
void InitBiTree(BiTree& T) 
{
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		exit(OVERFLOW);
}

// 销毁二叉树--按后序遍历
void DestroyBiTree(BiTree& T)
{
	if (T == NULL)
		return;
	else
	{
		DestroyBiTree(T->lchild); // 左
		DestroyBiTree(T->rchild); // 右
		cout << T->data << " ";
		delete T;
	}
}

// 构造二叉树, 按先(前)序遍历  （根左右）
void CreateBiTree(BiTree& T)
{
	TElemType data;
	cin >> data;
	if (data == '#')
	{
		T = NULL;
		return;
	}
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		exit(OVERFLOW);
	else
	{
		T->data = data; // 根
		CreateBiTree(T->lchild); // 左
		CreateBiTree(T->rchild); // 右
	}
}

/*----------------------------递归方法 遍历二叉树-----------------------------*/
// 先序遍历T，对每个结点调用函数Visit一次
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T == NULL)
		return ERROR;
	else
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
	return OK;
}

// 中序遍历T，对每个结点调用函数Visit一次
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T == NULL)
		return ERROR;
	else
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild, Visit);
	}
	return OK;
}

// 后序遍历T，对每个结点调用函数Visit一次
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	if (T == NULL)
		return ERROR;
	else
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T->data);
	}
	return OK;
}

// 层序遍历T，对每个结点调用函数Visit一次
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	LinkQueue Q;
	InitQueue(Q);
	BiTree p = T;
	QElemType e = NULL;
	while (p != NULL || !QueueEmpty(Q))
	{
		Visit(p->data);
		if (p->lchild != NULL)
			EnQueue(Q, p->lchild);
		if (p->rchild != NULL)
			EnQueue(Q, p->rchild);
		if (!QueueEmpty(Q))
			DeQueue(Q, p);
		else
			break;
	}

	return OK;
}
/*--------------------------------------------------------------------------*/


/*----------------------------栈方法 遍历二叉树-----------------------------*/
// 先序遍历T，对每个结点调用函数Visit一次(非递归算法)
Status PreOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S;
	InitStack(S);

	BiTNode *p = T;
	while (p != NULL || !StackEmpty(S))
	{
		while (p != NULL)
		{
			Visit(p->data);
			Push(S, p);
			p = p->lchild;
		}
		if (!StackEmpty(S))
		{
			Pop(S, p);
			p = p->rchild;
		}
	}


	DestroyStack(S);
	return OK;
}

// 中序遍历T，对每个结点调用函数Visit一次(非递归算法)
Status InOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S;
	InitStack(S);

	BiTNode *p = T;
	while (p != NULL || !StackEmpty(S))
	{
		while (p != NULL)
		{
			Push(S, p);
			p = p->lchild;
		}

		if (!StackEmpty(S))
		{
			Pop(S, p);
			Visit(p->data);
			p = p->rchild;
		}
	}

	DestroyStack(S);
	return OK;
}

// 后序遍历T，对每个结点调用函数Visit一次(非递归算法)
Status PostOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e))
{
	SqStack S;
	InitStack(S);

	BiTNode *p = T;
	while (p != NULL || !StackEmpty(S))
	{
		while (p != NULL)
		{
			p->flag = 1;
			Push(S, p);
			p = p->lchild;
		}

		while (!StackEmpty(S))
		{
			Pop(S, p);
			if (p->flag == 2)
			{
				Visit(p->data);
				p = NULL;
			}
			else
			{
				Push(S, p);
				break;
			}
		}
		
		if (!StackEmpty(S))
		{
			GetTop(S, p);
			p->flag = 2;
			p = p->rchild;
		}
	}

	DestroyStack(S);
	return OK;
}

/*--------------------------------------------------------------------------*/


// Visit
Status Visit(TElemType e)
{
	cout << e << " ";
	return OK;
}

int main()
{
	BiTree T = NULL;
	CreateBiTree(T);
	cout << "/*-------------------递归方法 遍历二叉树--------------------*/" << endl;
	cout << "PreOrderTraverse :";
	PreOrderTraverse(T, Visit);
	cout << endl;

	cout << "InOrderTraverse :";
	InOrderTraverse(T, Visit);
	cout << endl;

	cout << "PostOrderTraverse :";
	PostOrderTraverse(T, Visit);
	cout << endl;

	cout << "LevelOrderTraverse :";
	LevelOrderTraverse(T, Visit);
	cout << endl;

	cout << "/*---------------------栈方法 遍历二叉树----------------------*/" << endl;
	cout << "PreOrderTraverse :";
	PreOrderTraverse_Stack(T, Visit);
	cout << endl;

	cout << "InOrderTraverse :";
	InOrderTraverse_Stack(T, Visit);
	cout << endl;

	cout << "PostOrderTraverse :";
	PostOrderTraverse_Stack(T, Visit);
	cout << endl;

	cout << "DestroyBiTree :";
	DestroyBiTree(T);
	cout << endl;
	return 0;
}
