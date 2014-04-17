#include "GraphTraverse.h"
#include <iostream>
using namespace std;

// 找到第一个v相邻的顶点，返回它的下标
int FirstAdjVex(ALGraph &AL, int v)
{
	ArcNode *p = NULL;
	p = AL.vertices[v].firstarc;
	if (p == NULL)
		return -1;
	else
		return p->adjvex;
}

// 找到下一个与v相邻的顶点，返回它的下标
int NextAdjVex(ALGraph &AL, int v, int w)
{
	ArcNode *p = NULL;
	p = AL.vertices[v].firstarc;
	while (p->adjvex != w) // 找到下标为w的结点
		p = p->nextarc;
	p = p->nextarc; // 指针指向下标为w的结点的后面一个结点
	if (p == NULL)
		return -1;
	else
		return p->adjvex;
}

// 深度优先搜索: 跟二叉树的前(根)序遍历相似
void DFSTraverse(ALGraph &AL)
{
	for (int v = 0; v < AL.vexnum; v++)
		Visited[v] = unvisited;
	for (int v = 0; v < AL.vexnum; v++)
		if (!Visited[v])
			DFS(AL, v);
}

// 从第v个顶点出发递归地深度优先遍历图AL
void DFS(ALGraph &AL, int v)
{
	Visited[v] = visited;
	VisitFunc(AL, v);
	for (int w = FirstAdjVex(AL, v); w >= 0; w = NextAdjVex(AL, v, w))
	if (!Visited[w])
		DFS(AL, w);
}

// 广度优先搜索: 跟二叉树的层序遍历相似
void BFSTraverse(ALGraph &AL)
{
	for (int v = 0; v < AL.vexnum; v++)
		Visited[v] = unvisited;
	LinkQueue Q;
	InitQueue(Q); // 初始化队列
	for (int v = 0; v < AL.vexnum; v++)
	{
		if (!Visited[v])
		{
			Visited[v] = visited;
			VisitFunc(AL, v); // 先显示完该结点，再入队
			EnQueue(Q, v);
			while (!QueueEmpty(Q))
			{
				QElemType u;
				DeQueue(Q, u); // 出队后，将出队元素的所有相邻的未访问过的结点入队
				for (int w = FirstAdjVex(AL, u); w >= 0; w = NextAdjVex(AL, u, w))
				{
					if (!Visited[w])
					{
						Visited[w] = visited;
						VisitFunc(AL, w); // 先显示完该结点，再入队
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}


// v为元素下标，显示下标为v的元素的数据
void VisitFunc(ALGraph &AL, int v)
{
	if (v < 0 || v >= AL.vexnum)
		return;

	cout << AL.vertices[v].data << " ";
}


int main()
{
	ALGraph AL; // 邻接表表示法
	UserInput(UDG); // 用户信息输入(无向图)
	CreateUDG_AL(AL);	// 创建无向图(邻接表表示法)
	
	cout << "深度优先遍历: ";
	DFSTraverse(AL); // 深度优先搜索
	cout << endl;

	cout << "广度优先遍历: ";
	BFSTraverse(AL); // 广度优先搜索
	cout << endl;
	return 0;
}
