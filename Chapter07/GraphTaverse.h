#pragma once
#include "Graph.h" // 将有关图、网构建的头文件加入进来
#include "Queue.h" // 将队列操作的头文件加入进来(为了实现广度优先搜索)

int FirstAdjVex(ALGraph &AL, int v); // 找到第一个与v相邻的顶点，返回它的下标
int NextAdjVex(ALGraph &AL, int v, int w); // 找到下一个与v相邻的顶点，返回它的下标
void DFSTraverse(ALGraph &AL); // 深度优先搜索
void DFS(ALGraph &AL, int v); // 从第v个顶点出发递归地深度优先遍历图AL
void BFSTraverse(ALGraph &AL); // 广度优先搜索
void VisitFunc(ALGraph &AL, int v); // v为元素下标，显示下标为v的元素的数据
