#include "ForestTraverse.h"
#include <iostream>
using namespace std;

/*全局变量*/
extern bool Visited[MAX_VERTEX_NUM]; // 来自GraphTraverse.cpp

// 建立无向图AL的深度优先生成森林
void DFSForest(ALGraph &AL, CSTree &T)
{
	T = NULL;
	for (int v = 0; v < AL.vexnum; v++)
		Visited[v] = unvisited;

	CSNode *p = NULL, *q = NULL;
	for (int v = 0; v < AL.vexnum; v++)
	{
		if (!Visited[v])
		{
			p = new CSNode;
			strcpy(p->data, AL.vertices[v].data);
			p->firstchild = p->nextsibling = NULL;
			if (!T)
				T = p; // 让T保存第一棵树的根节点地址，由它可得知其他几棵生成树(通过T->nextsibling)
			else
				q->nextsibling = p;
			q = p;
			DFSTree(AL, v, p);
		}
	}
}

// 从第v个顶点出发深度优先遍历图AL,建立以T为根的生成树
void DFSTree(ALGraph &AL, int v, CSTree &T)
{
	Visited[v] = visited;
	bool first = TRUE;
	CSNode *p = NULL, *q = NULL;
	for (int w = FirstAdjVex(AL, v); w >= 0; w = NextAdjVex(AL, v, w))
	{
		if (!Visited[w])
		{
			p = new CSNode;
			strcpy(p->data, AL.vertices[w].data);
			p->firstchild = p->nextsibling = NULL;
			if (first)
			{
				T->firstchild = p;
				first = FALSE;
			}
			else
				q->nextsibling = p;
			q = p;
			DFSTree(AL, w, q);
		}
	}
}

// 深度优先遍历，显示生成森林
void DFSForestTraverse(CSTree p)
{
	if (p == NULL)
		return;
	while (p != NULL)
	{
		VisitForest(p);
		DFSForestTraverse(p->firstchild);
		p = p->nextsibling;
	}
}

// 广度优先遍历，显示生成森林
void BFSForestTraverse(ALGraph &AL, CSTree p)
{
	for (int v = 0; v < AL.vexnum; v++)
		Visited[v] = unvisited;
	LinkQueue Q;
	InitQueue(Q);
	while (p != NULL) // 每棵树的根结点依次入队
	{
		VisitForest(p);
		EnQueue(Q, p);
		p = p->nextsibling;
	}
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, p); // 结点出队
		p = p->firstchild;
		while (p != NULL) // 遍历该节点的所有孩子，并将孩子依次入队
		{
			VisitForest(p);
			EnQueue(Q, p);
			p = p->nextsibling;
		}
	}
}

void VisitForest(CSTree p)
{
	cout << p->data << " ";
}

int main()
{
	ALGraph AL; // 邻接表表示法
	UserInput(UDG); // 用户信息输入(无向图)
	CreateUDG_AL(AL);	// 创建无向图(邻接表表示法)
	CSTree T;
	DFSForest(AL, T);
	cout << "生成森林的深度优先遍历: ";
	DFSForestTraverse(T); // 深度优先搜索
	cout << endl;
	cout << "生成森林的广度优先遍历: ";
	BFSForestTraverse(AL, T); // 深度优先搜索
	cout << endl;
	return 0;
}
