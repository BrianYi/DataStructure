#include "TopologicalSort.h"
#include <iostream>
using namespace std;


/*全局变量*/
int indegree[MAX_VERTEX_NUM];

// 拓扑排序
Status TopologicalSort(ALGraph &AL)
{
	// 1. 选出入度为0的点进栈(去点)
	// 2. 对于每一个点出栈，并输出,count++,并找出它的后继结点，令后继结点入度减1(消边)
	//    (1) 如果后继结点入度为0，则进栈
	//    (2) 否则，继续判断下一个与之相连的结点，循环直到消除所有以出栈的点为前驱的边为止
	// 3. 出栈的点的个数(即count)是否小于顶点总数
	//    (1) 是，则该图有回路
	//    (2) 不是，则该图无回路

	SqStack S;
	InitStack(S);
	FindInDegree(AL); // 初始化入度数据
	for (int i = 0; i < AL.vexnum; i++)
	{
		if (!indegree[i])
			Push(S, i); // 入度为0的顶点进栈
	}
	int count = 0; // 记录出栈顶点个数
	int i, k;
	ArcNode *p = NULL;
	while (!StackEmpty(S)) 
	{
		Pop(S, i);
		count++; // 出栈顶点数加1
		cout << AL.vertices[i].data << " ";
		for (p = AL.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			if (!(--indegree[k]))
				Push(S, k); // 后继结点入度为0的，入栈
		}
	}
	if (count < AL.vexnum)
		return ERROR; // 有回路
	return OK; // 无回路
}

// 初始化入度数据到indegree中
void FindInDegree(ALGraph &AL)
{
	int k;
	for (int i = 0; i < AL.vexnum; i++)
	{
		ArcNode *p = NULL;
		for (p = AL.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			indegree[k]++;
		}
	}
}


int main()
{
	ALGraph AL; 
	UserInput(DG); // 有向图信息输入
	CreateDG_AL(AL); // 创建有向图
	cout << "拓扑序列为(不唯一) :";
	bool result = TopologicalSort(AL); // 拓扑排序并输出
	if (result == ERROR)
		cout << "有回路,不能生成拓扑序列!" << endl;
	return 0;
}
