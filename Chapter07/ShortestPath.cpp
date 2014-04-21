#include "ShortestPath.h"
#include <iostream>
using namespace std;

// Dijkstra最短路径算法
void Dijkstra(MGraph &M, int v)
{
	int *dist = new int[M.vexnum]; // 当前v点到各点的最短路径长度
	char(*path)[50] = new char[M.vexnum][50](); // 当前v点到各点的最短路径
	for (int i = 0; i < M.vexnum; i++)
	{
		dist[i] = M.arcs[v][i].adj;
		if (M.arcs[v][i].adj != INFINITY)
		{
			strcat(path[i], M.vexs[v]);
			strcat(path[i], "->");
			strcat(path[i], M.vexs[i]);
		}
		else
			strcpy(path[i], "");
	}
	
	dist[v] = 0; // 设置点v为起点，自己到自己的距离为0，入集合S
	int num = 1; // 计数，已入集合S中的点的个数
	int i, k;
	while (num < M.vexnum)
	{
		for (k = 0; !dist[k]; k++); // 找到第一个不在集合中的点
		// 找出当前能构成最短路径的不在集合S中的点
		for (i = 0; i < M.vexnum; i++)
		{
			if (dist[i] != 0)
			{
				if(dist[k] > dist[i])
					k = i;
			}
		}

		cout << M.vexs[v] << " -> " << M.vexs[k] << " ,最短路径 : " << path[k] << " ";
		if (dist[k] == INFINITY)
			cout << "∞" << endl;
		else
			cout << dist[k] << endl;
		num++;

		// 更新dist,让dist始终保存当前已知的v到所有顶点的最短路径长度
		for (i = 0; i < M.vexnum; i++)
		{
			if (dist[k] + M.arcs[k][i].adj < dist[i]) // 新路径与已有的最短路径想比较
			{
				dist[i] = dist[k] + M.arcs[k][i].adj; // 新路径比已有的最短路径要短，更新
				strcpy(path[i], "");
				strcat(path[i], path[k]); // 新路径
				strcat(path[i], "->");
				strcat(path[i], M.vexs[i]); 
			}
		}
		dist[k] = 0; // 点入集合
	}

	delete[] dist;
	delete[] path;
}

// Floyd最短路径算法
void Floyd(MGraph &M) 
{
	int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 当前v点到各点的最短路径长度
	char path[MAX_VERTEX_NUM][MAX_VERTEX_NUM][50]; // 当前v点到各点的最短路径
	// 初始化 dist,path
	for (int i = 0; i < M.vexnum; i++)
	{
		for (int j = 0; j < M.vexnum; j++)
		{
			dist[i][j] = M.arcs[i][j].adj;
			if (dist[i][j] != INFINITY)
			{
				strcpy(path[i][j], "");
				strcat(path[i][j], M.vexs[i]);
				strcat(path[i][j], "->");
				strcat(path[i][j], M.vexs[j]);
			}
			else
				strcpy(path[i][j], "");
		}
	}

	for (int k = 0; k < M.vexnum; k++) // 进行n次迭代
	{
		for (int i = 0; i < M.vexnum; i++) // 顶点i和j之间是否经过顶点k
		{
			for (int j = 0; j < M.vexnum; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					strcpy(path[i][j], "");
					strcat(path[i][j], path[i][k]);
					strcat(path[i][j], ",");
					strcat(path[i][j], path[k][j]);
				}
			}
		}
	}

	// 输出所有最短路径
	for (int i = 0; i < M.vexnum; i++)
	{
		cout << "起点 :" << M.vexs[i] << endl;
		for (int j = 0; j < M.vexnum; j++)
		{
			if (i != j)
			{
				cout << M.vexs[i] << "->" << M.vexs[j] << "，最短路径 : " << path[i][j] << " ";
				if (dist[i][j] == INFINITY)
					cout << "∞" << endl;
				else
					cout << dist[i][j] << endl;
			}
		}
	}
}

int main()
{
	MGraph M;
	UserInput(DN); // 有向网信息输入
	CreateDN_M(M); // 创建有向网

	cout << "Dijkstra最短路径算法 :" << endl;
	for (int i = 0; i < M.vexnum; i++)
	{
		cout << "起点为" << M.vexs[i] << " :" << endl;
		Dijkstra(M, i); // Dijkstra最短路径算法
	}
	cout << endl;
	cout << "Floyd最短路径算法 :" << endl;
	Floyd(M); // Floyd最短路径算法

	return 0;
}
