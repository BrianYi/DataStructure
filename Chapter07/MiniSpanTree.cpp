#include "MiniSpanTree.h"
#include <iostream>
using namespace std;
/*
* Prim算法需要用到的全局变量
*/
Closedge closedge[MAX_VERTEX_NUM];

/*
 * Prim算法需要用到的函数
 */

// Prim最小生成树算法
void MiniSpanTree_PRIM(MGraph &M, VertexType v)
{
	int k = LocateVex_M(M, v); 
	for (int i = 0; i < M.vexnum; i++) // 求出所有结点与k的距离(即权值),存放到closedge中
	{
		if (i != k)
		{
			strcpy(closedge[i].adjvex, v); // 顶点名字
			closedge[i].lowcost = M.arcs[k][i].adj; // 权值
		}
	}
	closedge[k].lowcost = 0; // k进入集合U中

	for (int i = 1; i < M.vexnum; i++)
	{
		k = minimum(M, closedge); // 求出下一个要加入集合U的结点(即与U中的某个结点能构成最小权值的集合U外的结点)
		cout << closedge[k].adjvex << " - " << M.vexs[k] << " " << closedge[k].lowcost << endl;
		closedge[k].lowcost = 0; // 将该节点加入集合U中

		// 更新最小边
		for (int j = 0; j < M.vexnum; j++)
		{
			if (M.arcs[k][j].adj < closedge[j].lowcost)
			{
				strcpy(closedge[j].adjvex, M.vexs[k]); // 更新最小边一端顶点的名字
				closedge[j].lowcost = M.arcs[k][j].adj; // 更新最小边的权值
			}
		}
	}
}

// 求出能构成最短边的下一个结点下标
int minimum(MGraph &M, Closedge *closedge)
{
	int minValue = INFINITY;
	int index = -1;
	for (int i = 0; i < M.vexnum; i++)
	{
		// 权值为0代表该点已经在集合U中，所有我们不需要再找集合U中的点
		if (closedge[i].lowcost != 0 && minValue >= closedge[i].lowcost)
		{
			minValue = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}


/*
 * Kruskal算法需要用到的函数
 */

// Kruskal最小生成树算法
void MiniSpanTree_KRUSKAL(EdgeGraph &E)
{
	// E中边集数组排序
	SortEdgeGraph(E);

	// 将E中的parent初始化
	for (int i = 0; i < E.vexnum; i++)
		E.parent[i] = -1; // 无父亲结点

	int vex1, vex2, from, to;
	for (int i = 0, num = 0; i < E.edgenum; i++)
	{
		vex1 = FindRoot(E, E.edge[i].from); // 找到E.edge[i].from的父结点
		vex2 = FindRoot(E, E.edge[i].to);   // 找到E.edge[i].to的父结点
		// 两个父结点不相同，则合并为一个父结点，即合并成一棵树
		if (vex1 != vex2)
		{
			from = E.edge[i].from;
			to = E.edge[i].to;
			cout << E.vertex[from] << " - " << E.vertex[to] << " " << GetWeight(E, from, to) << endl;
			E.parent[vex2] = vex1; // 合并成一棵树
			num++;
			if (num == E.vexnum - 1)
				return;
		}
	}
}

// 创建无向网
void CreateUDN_E(MGraph &M, EdgeGraph &E)
{
	// 边数目，顶点数目，顶点名字赋值
	E.edgenum = M.arcnum;
	E.vexnum = M.vexnum;
	for (int i = 0; i < M.vexnum; i++)
		strcpy(E.vertex[i], M.vexs[i]);

	// 只取上三角
	for (int i = 0, num = 0; i < M.vexnum; i++)
	{
		for (int j = i; j < M.vexnum; j++)
		{
			if (M.arcs[i][j].adj != INFINITY)
			{
				E.edge[num].from = i;
				E.edge[num].to = j;
				E.edge[num].weight = M.arcs[i][j].adj;
				num++;
			}
		}
	}
}


// 将边集数组排序
void SortEdgeGraph(EdgeGraph &E)
{
	EdgeType tmp;
	for (int i = 0; i < E.edgenum - 1; i++)
	{
		for (int j = i + 1; j < E.edgenum; j++)
		{
			if (E.edge[i].weight > E.edge[j].weight)
			{
				tmp = E.edge[i];
				E.edge[i] = E.edge[j];
				E.edge[j] = tmp;
			}
		}
	}
}

// 找到顶点下标为v的结点的最终根节点，并返回下标
int FindRoot(EdgeGraph &E, int v)
{
	while (E.parent[v] > -1)
		v = E.parent[v];
	return v;
}

// 返回权值
int GetWeight(EdgeGraph &E, int vex1, int vex2)
{
	for (int i = 0; i < E.edgenum; i++)
	{
		if ((E.edge[i].from == vex1 && E.edge[i].to == vex2) ||
			(E.edge[i].from == vex2 && E.edge[i].to == vex1))
			return E.edge[i].weight;
	}
	exit(0); // 错误
	return -1;
}

int main()
{
	MGraph M;
	UserInput(UDN);
	CreateUDN_M(M);
	cout << "最小生成树Prim算法 :" << endl;
	MiniSpanTree_PRIM(M, M.vexs[0]);

	EdgeGraph E;
	CreateUDN_E(M, E);
	cout << "最小生成树Kruskal算法 :" << endl;
	MiniSpanTree_KRUSKAL(E);
	return 0;
}
