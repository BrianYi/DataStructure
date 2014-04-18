#pragma once

#include "Graph.h"

#define MAX(x, y) x > y ? x:y;
#define MIN(x, y) x < y ? x:y;

/*用于Prim算法的部分数据结构,图用MGraph数据结构表示*/
struct Closedge{
	VertexType  adjvex;
	VRType		lowcost;
};

void MiniSpanTree_PRIM(MGraph &M, VertexType v); // Prim最小生成树算法
int minimum(MGraph &M, Closedge *closedge); // 求出能构成最短边的下一个结点下标


/*用于Kruskal算法的图数据结构*/
struct EdgeType { 
	int from;  // 边的一个顶点
	int to;    // 边的另一个顶点
	int weight; // 边的权重
};

struct EdgeGraph{
	VertexType  vertex[MAX_VERTEX_NUM]; // 存放顶点名称
	EdgeType	edge[MAX_ARC_NUM]; // 存放边集数组
	int			parent[MAX_VERTEX_NUM]; // 存放父亲结点
	int			vexnum, edgenum; // 存放图的顶点数和边数
};

void MiniSpanTree_KRUSKAL(EdgeGraph &E); // Kruskal最小生成树算法
void CreateUDN_E(MGraph &M, EdgeGraph &E); // 创建无向网
void SortEdgeGraph(EdgeGraph &E); // 将边集数组排序
int FindRoot(EdgeGraph &E, int v); // 找到顶点下标为v的结点的最终根节点，并返回下标
int GetWeight(EdgeGraph &E, int vex1, int vex2); // 返回权值
