#include "Graph.h"
#include <iomanip>
#include <iostream>
using namespace std;
/* 
 * 图或网的表示法的种类和可表示的类型:
 *
 *       ① 数组表示法: 1. 有向图
 *					    2. 有向网
 *					    3. 无向图
 *						4. 无向网
 *	     (以上四种皆可用数组表示)
 *
 *		 ② 邻接表表示法: 1. 有向图
 *					      2. 有向网
 *					      3. 无向图
 *						  4. 无向网
 *		 (以上四种皆可用邻接表表示)
 *
 *		 ③ 十字链表表示法: 1. 有向图
 *							2. 有向网
 *		 (以上两种皆可用十字链表表示,但它不能表示无向图和无向网)
 *
 *		 ④ 邻接多重表表示法: 1. 无向图
 *							  2. 无向网
 *		 (以上两种皆可用邻接多重表表示,但它不能表示有向图和有向网)
 *
 * 注意：因为时间紧迫，所以没有释放内存空间，出了事故不要找我。 - -！（不过一般情况下，没什么问题）
 */


/*数组表示法*/
// 构造有向图
Status CreateDG_M(MGraph &M)
{
	int incInfo;
	M.vexnum = Vexnum;
	M.arcnum = Arcnum;
	incInfo  = IncInfo;

	// 初始化
	for (int i = 0; i < M.vexnum; i++)
	{
		for (int j = 0; j < M.vexnum; j++)
		{
			M.arcs[i][j].adj  = 0; 
			M.arcs[i][j].info = NULL;
		}
	}

	// 用户输入顶点的名字
	for (int i = 0; i < M.vexnum; i++)
		strcpy(M.vexs[i],Vexs[i]);

	// 用户输入边(即顶点之间的关系)
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < M.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]); // v1 -> v2
		i = LocateVex_M(M, v1); // 找到下标
		j = LocateVex_M(M, v2); // 找到下标
		M.arcs[i][j].adj = 1; // 相关联
		if (incInfo)
		{
			M.arcs[i][j].info = new InfoType[MAX_INFO];
			strcpy(M.arcs[i][j].info,Info[k]);
		}
	}
	return OK;
}

// 构造有向网
Status CreateDN_M(MGraph &M)
{
	int incInfo;
	M.vexnum = Vexnum;
	M.arcnum = Arcnum;
	incInfo = IncInfo;

	// 初始化
	for (int i = 0; i < M.vexnum; i++)
	{
		for (int j = 0; j < M.vexnum; j++)
		{
			M.arcs[i][j].adj = INFINITY;
			M.arcs[i][j].info = NULL;
		}
	}

	// 用户输入顶点的名字
	for (int i = 0; i < M.vexnum; i++)
		strcpy(M.vexs[i], Vexs[i]);

	// 用户输入边(即顶点之间的关系)
	VertexType v1, v2;
	int i, j, w;
	for (int k = 0; k < M.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]); 
		w = W[k];			// v1 -> v2 (w为权值)
		i = LocateVex_M(M, v1); // 找到下标
		j = LocateVex_M(M, v2); // 找到下标
		M.arcs[i][j].adj = w; // 相关联
		if (incInfo)
		{
			M.arcs[i][j].info = new InfoType[MAX_INFO];
			strcpy(M.arcs[i][j].info,Info[k]);
		}
	}
	return OK;
}

// 构造无向图
Status CreateUDG_M(MGraph &M)
{
	int incInfo;
	M.vexnum = Vexnum;
	M.arcnum = Arcnum;
	incInfo = IncInfo;

	// 初始化
	for (int i = 0; i < M.vexnum; i++)
	{
		for (int j = 0; j < M.vexnum; j++)
		{
			M.arcs[i][j].adj = 0;
			M.arcs[i][j].info = NULL;
		}
	}

	// 用户输入顶点的名字
	for (int i = 0; i < M.vexnum; i++)
		strcpy(M.vexs[i], Vexs[i]);

	// 用户输入边(即顶点之间的关系)
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < M.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 -> v2
		i = LocateVex_M(M, v1); // 找到下标
		j = LocateVex_M(M, v2); // 找到下标
		M.arcs[i][j].adj = 1; // 相关联
		if (incInfo)
		{
			M.arcs[i][j].info = new InfoType[MAX_INFO];
			strcpy(M.arcs[i][j].info,Info[k]);
		}
		M.arcs[j][i] = M.arcs[i][j]; // 无向图对称
	}
	return OK;
	return OK;
}

// 构造无向网
Status CreateUDN_M(MGraph &M)
{
	int incInfo;
	M.vexnum = Vexnum;
	M.arcnum = Arcnum;
	incInfo = IncInfo;

	// 初始化
	for (int i = 0; i < M.vexnum; i++)
	{
		for (int j = 0; j < M.vexnum; j++)
		{
			M.arcs[i][j].adj = INFINITY;
			M.arcs[i][j].info = NULL;
		}
	}

	// 用户输入顶点的名字
	for (int i = 0; i < M.vexnum; i++)
		strcpy(M.vexs[i], Vexs[i]);

	// 用户输入边(即顶点之间的关系)
	VertexType v1, v2;
	int i, j, w;
	for (int k = 0; k < M.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]); 
		w = W[k];				// v1 -> v2 (w为权值)
		i = LocateVex_M(M, v1); // 找到下标
		j = LocateVex_M(M, v2); // 找到下标
		M.arcs[i][j].adj = w; // 相关联
		if (incInfo)
		{
			M.arcs[i][j].info = new InfoType[MAX_INFO];
			strcpy(M.arcs[i][j].info,Info[k]);
		}
		M.arcs[j][i] = M.arcs[i][j]; // 无向网对称
	}
	return OK;
}

// 数组表示法：显示有向图、有向网、无向图、无向网
void DisplayMGraph(MGraph &M, GraphKind kind)
{
	/* 显示图、网信息 */
	cout << endl;
	cout << "/*---数组表示法如下---*/" << endl;
	if (kind == DG || kind == UDG)
	{
		// 数组显示有向图、无向图
		for (int i = 0; i < M.vexnum; i++)
		{
			for (int j = 0; j < M.vexnum; j++)
			{
				cout << setiosflags(ios::left) << setw(5) << M.arcs[i][j].adj;
			}
			cout << endl;
		}
	}
	else if (kind == DN || kind == UDN)
	{
		// 数组显示有向网、无向网
		for (int i = 0; i < M.vexnum; i++)
		{
			for (int j = 0; j < M.vexnum; j++)
			{
				if (M.arcs[i][j].adj == INFINITY)
					cout << setiosflags(ios::left) << setw(5) << "∞";
				else
					cout << setiosflags(ios::left) << setw(5) << M.arcs[i][j].adj;
			}
			cout << endl;
		}
	}


	/* 显示边信息 */
	if (IncInfo)
		cout << "---边信息如下---" << endl;
	// 显示有向图、有向网边信息
	if (IncInfo && (kind == DG || kind == DN))
	{
		for (int i = 0; i < M.vexnum; i++)
		{
			for (int j = 0; j < M.vexnum; j++)
			{
				if (M.arcs[i][j].info != NULL)
					cout << M.vexs[i] << " -> " << M.vexs[j] << ": " << M.arcs[i][j].info << endl;
			}
		}
	}
	// 显示无向图、无向网边信息
	else if (IncInfo && (kind == UDG || kind == UDN)) 
	{
		// 去对角线元素即可
		for (int i = 0; i < M.vexnum; i++)
		{
			for (int j = 0; j < i+1; j++)
			{
				if (M.arcs[i][j].info != NULL)
					cout << M.vexs[i] << " -> " << M.vexs[j] << ": " << M.arcs[i][j].info << endl;
			}
		}
	}
}

// 寻找v在图中的下标
int LocateVex_M(MGraph &M, VertexType v)
{
	for (int i = 0; i < M.vexnum; i++)
	{
		if (strcmp(M.vexs[i],v) == 0)
			return i;
	}
	exit(0);
	return -1;
}



/*邻接表表示法*/
// 构造有向图
Status CreateDG_AL(ALGraph &AL)
{
	int incInfo;
	AL.vexnum = Vexnum;
	AL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给头结点初始化
	for (int i = 0; i < AL.vexnum; i++)
	{
		strcpy(AL.vertices[i].data, Vexs[i]);
		AL.vertices[i].firstarc = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcNode *p = NULL, *s = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 -> v2
		i = LocateVex_AL(AL, v1); // 找到下标
		j = LocateVex_AL(AL, v2); // 找到下标
		s = new ArcNode;
		s->adjvex = j;
		s->nextarc = NULL;
		s->w = 1; 
		if (incInfo)
		{
			s->info = new InfoType[MAX_INFO];
			strcpy(s->info, Info[k]);
		}
		/* 将新结点s插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[i].firstarc;
		if (p == NULL)
			AL.vertices[i].firstarc = s;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s;
		}
	}
	return OK;
}

// 构造有向网
Status CreateDN_AL(ALGraph &AL)
{
	int incInfo;
	AL.vexnum = Vexnum;
	AL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给头结点初始化
	for (int i = 0; i < AL.vexnum; i++)
	{
		strcpy(AL.vertices[i].data, Vexs[i]);
		AL.vertices[i].firstarc = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcNode *p = NULL, *s = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 -> v2
		i = LocateVex_AL(AL, v1); // 找到下标
		j = LocateVex_AL(AL, v2); // 找到下标
		s = new ArcNode;
		s->adjvex = j;
		s->nextarc = NULL;
		s->w = W[k];
		if (incInfo)
		{
			s->info = new InfoType[MAX_INFO];
			strcpy(s->info, Info[k]);
		}
		/* 将新结点s插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[i].firstarc;
		if (p == NULL)
			AL.vertices[i].firstarc = s;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s;
		}
	}
	return OK;
}

// 构造无向图
Status CreateUDG_AL(ALGraph &AL)
{
	int incInfo;
	AL.vexnum = Vexnum;
	AL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给头结点初始化
	for (int i = 0; i < AL.vexnum; i++)
	{
		strcpy(AL.vertices[i].data, Vexs[i]);
		AL.vertices[i].firstarc = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcNode *p = NULL, *s1 = NULL, *s2 = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 <-> v2
		i = LocateVex_AL(AL, v1); // 找到下标
		j = LocateVex_AL(AL, v2); // 找到下标
		// s1: v1 -> v2
		s1 = new ArcNode;
		s1->adjvex = j;
		s1->nextarc = NULL;
		s1->w = 1;
		// s2: v2 -> v1
		s2 = new ArcNode;
		s2->adjvex = i;
		s2->nextarc = NULL;
		s2->w = 1;

		if (incInfo)
		{
			// s1: v1 -> v2
			s1->info = new InfoType[MAX_INFO];
			strcpy(s1->info, Info[k]);
			// s2: v2 -> v1
			s2->info = new InfoType[MAX_INFO];
			strcpy(s2->info, Info[k]);
		}
		/* 将新结点s1插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[i].firstarc;
		if (p == NULL)
			AL.vertices[i].firstarc = s1;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s1;
		}
		/* 将新结点s2插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[j].firstarc;
		if (p == NULL)
			AL.vertices[j].firstarc = s2;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s2;
		}
	}
	return OK;
}

// 构造无向网
Status CreateUDN_AL(ALGraph &AL)
{
	int incInfo;
	AL.vexnum = Vexnum;
	AL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给头结点初始化
	for (int i = 0; i < AL.vexnum; i++)
	{
		strcpy(AL.vertices[i].data, Vexs[i]);
		AL.vertices[i].firstarc = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcNode *p = NULL, *s1 = NULL, *s2 = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 <-> v2
		i = LocateVex_AL(AL, v1); // 找到下标
		j = LocateVex_AL(AL, v2); // 找到下标
		// s1: v1 -> v2
		s1 = new ArcNode;
		s1->adjvex = j;
		s1->nextarc = NULL;
		s1->w = W[k];
		// s2: v2 -> v1
		s2 = new ArcNode;
		s2->adjvex = i;
		s2->nextarc = NULL;
		s2->w = W[k];

		if (incInfo)
		{
			// s1: v1 -> v2
			s1->info = new InfoType[MAX_INFO];
			strcpy(s1->info, Info[k]);
			// s2: v2 -> v1
			s2->info = new InfoType[MAX_INFO];
			strcpy(s2->info, Info[k]);
		}
		/* 将新结点s1插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[i].firstarc;
		if (p == NULL)
			AL.vertices[i].firstarc = s1;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s1;
		}
		/* 将新结点s2插入到头结点所指向的表结点的最后一个 */
		p = AL.vertices[j].firstarc;
		if (p == NULL)
			AL.vertices[j].firstarc = s2;
		else
		{
			while (p->nextarc != NULL)
				p = p->nextarc;
			p->nextarc = s2;
		}
	}
	return OK;
}

// 邻接表表示法：显示有向图、有向网、无向图、无向网
void DisplayALGraph(ALGraph &AL, GraphKind kind)
{
	/* 显示图、网信息 */
	ArcNode *p = NULL;
	cout << endl;
	cout << "/*---邻接表表示法如下---*/" << endl;
	if (kind == DG || kind == UDG)
	{
		// 邻接表表示显示有向图、无向图
		for (int i = 0; i < AL.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << AL.vertices[i].data;
			p = AL.vertices[i].firstarc;
			while (p != NULL)
			{
				cout << " -> |" << p->adjvex << "|";
				p = p->nextarc;
			}
			cout << "∧|" << endl;
		}
	}
	else if (kind == DN || kind == UDN)
	{
		// 邻接表表示显示有向网、无向网
		for (int i = 0; i < AL.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << AL.vertices[i].data;
			p = AL.vertices[i].firstarc;
			while (p != NULL)
			{
				cout << " -> |" << p->adjvex << "|" << p->w << "|";
				p = p->nextarc;
			}
			cout << "∧|" << endl;
		}
	}


	/* 显示边信息 */
	if (IncInfo)
		cout << "---边信息如下---" << endl;
	// 显示有向图、有向网边信息 和 无向图、无向网边信息
	if (IncInfo)
	{
		for (int i = 0; i < AL.vexnum; i++)
		{
			p = AL.vertices[i].firstarc;
			int j;
			while (p != NULL)
			{
				j = p->adjvex;
				cout << AL.vertices[i].data << " -> " << AL.vertices[j].data << ": " << p->info << endl;
				p = p->nextarc;
			}
		}
	}
}

// 寻找v在图中的下标
int LocateVex_AL(ALGraph &AL, VertexType v)
{
	for (int i = 0; i < AL.vexnum; i++)
	{
		if (strcmp(AL.vertices[i].data, v) == 0)
			return i;
	}
	exit(0);
	return -1;
}


/*十字链表表示法*/
// 构造有向图
Status CreateDG_OL(OLGraph &OL)
{
	int incInfo;
	OL.vexnum = Vexnum;
	OL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给顶点结点初始化
	for (int i = 0; i < OL.vexnum; i++)
	{
		strcpy(OL.xlist[i].data, Vexs[i]);
		OL.xlist[i].firstin  = NULL;
		OL.xlist[i].firstout = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcBox *s = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < OL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 -> v2
		i = LocateVex_OL(OL, v1); // 找到下标
		j = LocateVex_OL(OL, v2); // 找到下标
		s = new ArcBox;
		s->tailvex = i; // 弧尾
		s->headvex = j; // 弧头
		s->hlink = OL.xlist[j].firstin;  // 插入(添加结点j一个入度)
		s->tlink = OL.xlist[i].firstout; // 插入(添加结点j一个出度)
		if (incInfo) // 用来存储权值以外的有关弧的信息
		{
			s->info = new InfoType[MAX_INFO];
			strcpy(s->info, Info[k]);
		}
		/* 将新结点s插入到顶点结点所指向的弧结点的第一个 */
		OL.xlist[j].firstin = OL.xlist[i].firstout = s; // 成功插入结点
	}
	return OK;
}

// 构造有向网
Status CreateDN_OL(OLGraph &OL)
{
	int incInfo;
	OL.vexnum = Vexnum;
	OL.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给顶点结点初始化
	for (int i = 0; i < OL.vexnum; i++)
	{
		strcpy(OL.xlist[i].data, Vexs[i]);
		OL.xlist[i].firstin = NULL;
		OL.xlist[i].firstout = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	ArcBox *s = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < OL.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 -> v2
		i = LocateVex_OL(OL, v1); // 找到下标
		j = LocateVex_OL(OL, v2); // 找到下标
		s = new ArcBox;
		s->tailvex = i; // 弧尾
		s->headvex = j; // 弧头
		s->hlink = OL.xlist[j].firstin;  // 插入(添加结点j一个入度)
		s->tlink = OL.xlist[i].firstout; // 插入(添加结点j一个出度)
		s->w = W[k];	// 权值
		if (incInfo) // 用来存储权值以外的有关弧的信息
		{
			s->info = new InfoType[MAX_INFO];
			strcpy(s->info, Info[k]);
		}
		/* 将新结点s插入到顶点结点所指向的弧结点的第一个 */
		OL.xlist[j].firstin = OL.xlist[i].firstout = s; // 成功插入结点
	}
	return OK;
}

// 十字链表表示法：显示有向图、有向网
void DisplayOLGraph(OLGraph &OL, GraphKind kind)
{
	/* 显示图、网信息 */
	ArcBox *p = NULL;
	cout << endl;
	cout << "/*---十字链表表示法如下---*/" << endl;
	if (kind == DG)
	{
		// 十字链表表示法显示有向图
		for (int i = 0; i < OL.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << OL.xlist[i].data << endl;
			
			// 入度
			p = OL.xlist[i].firstin;
			cout << "indegree  :";
			while (p != NULL)
			{
				cout << "|" << OL.xlist[p->tailvex].data << "| -> |" << OL.xlist[p->headvex].data << "|";
				p = p->hlink;
				if (p != NULL)
					cout << "  ";
			}
			cout << "∧|" << endl;
			
			// 出度
			p = OL.xlist[i].firstout;
			cout << "outdegree :";
			while (p != NULL)
			{
				cout << "|" << OL.xlist[p->tailvex].data << "| -> |" << OL.xlist[p->headvex].data << "|";
				p = p->tlink;
				if (p != NULL)
					cout << "  ";
			}
			cout << "∧|" << endl;
		}
	}
	else if (kind == DN)
	{
		// 十字链表表示法显示有向网
		for (int i = 0; i < OL.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << OL.xlist[i].data << endl;

			// 入度
			p = OL.xlist[i].firstin;
			cout << "indegree  :";
			while (p != NULL)
			{
				cout << "|" << OL.xlist[p->tailvex].data << "| -> |" << OL.xlist[p->headvex].data << "|" << p->w << "|";
				p = p->hlink;
				if (p != NULL)
					cout << "  ";
			}
			cout << "∧|" << endl;

			// 出度
			p = OL.xlist[i].firstout;
			cout << "outdegree :";
			while (p != NULL)
			{
				cout << "|" << OL.xlist[p->tailvex].data << "| -> |" << OL.xlist[p->headvex].data << "|" << p->w << "|";
				p = p->tlink;
				if (p != NULL)
					cout << "  ";
			}
			cout << "∧|" << endl;
		}
	}


	/* 显示边信息 */
	if (IncInfo)
		cout << "---边信息如下---" << endl;
	// 显示有向图、有向网边信息
	if (IncInfo)
	{
		for (int i = 0; i < OL.vexnum; i++)
		{
			p = OL.xlist[i].firstout;
			int j;
			while (p != NULL)
			{
				j = p->headvex;
				cout << OL.xlist[i].data << " -> " << OL.xlist[j].data << ": " << p->info << endl;
				p = p->tlink;
			}
		}
	}
}

// 寻找v在图中的下标
int LocateVex_OL(OLGraph &OL, VertexType v)
{
	for (int i = 0; i < OL.vexnum; i++)
	{
		if (strcmp(OL.xlist[i].data, v) == 0)
			return i;
	}
	exit(0);
	return -1;
}




/*邻接多重表表示法*/
// 构造无向图
Status CreateUDG_AML(AMLGraph &AML)
{
	int incInfo;
	AML.vexnum = Vexnum;
	AML.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给顶点结点初始化
	for (int i = 0; i < AML.vexnum; i++)
	{
		strcpy(AML.adjmulist[i].data, Vexs[i]);
		AML.adjmulist[i].firstedge = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	EBox *s1 = NULL, *s2 = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AML.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 <-> v2
		i = LocateVex_AML(AML, v1); // 找到下标
		j = LocateVex_AML(AML, v2); // 找到下标
		// s1
		s1 = new EBox;
		s1->ivex = i; 
		s1->jvex = j;
		s1->ilink = AML.adjmulist[i].firstedge; // 插入
		s1->jlink = AML.adjmulist[j].firstedge; // 插入
		// s2
		s2 = new EBox;
		s2->ivex = j;
		s2->jvex = i;
		s2->ilink = AML.adjmulist[j].firstedge; // 插入
		s2->jlink = AML.adjmulist[i].firstedge; // 插入
		if (incInfo) // 用来存储权值以外的有关弧的信息
		{
			// s1
			s1->info = new InfoType[MAX_INFO];
			strcpy(s1->info, Info[k]);
			// s2
			s2->info = new InfoType[MAX_INFO];
			strcpy(s2->info, Info[k]);
		}
		/* 将新结点s1插入到顶点结点所指向的弧结点的第一个 */
		AML.adjmulist[i].firstedge = s1; // 成功插入结点s1
		/* 将新结点s2插入到顶点结点所指向的弧结点的第一个 */
		AML.adjmulist[j].firstedge = s2; // 成功插入结点s2
	}
	return OK;
}

// 构造无向网
Status CreateUDN_AML(AMLGraph &AML)
{
	int incInfo;
	AML.vexnum = Vexnum;
	AML.arcnum = Arcnum;
	incInfo = IncInfo;

	// 用户输入顶点的名字,并给顶点结点初始化
	for (int i = 0; i < AML.vexnum; i++)
	{
		strcpy(AML.adjmulist[i].data, Vexs[i]);
		AML.adjmulist[i].firstedge = NULL;
	}

	// 用户输入边(即顶点之间的关系)
	EBox *s1 = NULL, *s2 = NULL;
	VertexType v1, v2;
	int i, j;
	for (int k = 0; k < AML.arcnum; k++)
	{
		strcpy(v1, V1[k]);
		strcpy(v2, V2[k]);  // v1 <-> v2
		i = LocateVex_AML(AML, v1); // 找到下标
		j = LocateVex_AML(AML, v2); // 找到下标
		// s1
		s1 = new EBox;
		s1->ivex = i;
		s1->jvex = j;
		s1->ilink = AML.adjmulist[i].firstedge; // 插入
		s1->jlink = AML.adjmulist[j].firstedge; // 插入
		s1->w = W[k]; // 权值
		// s2
		s2 = new EBox;
		s2->ivex = j; // s2与s1的j、i调换
		s2->jvex = i;
		s2->ilink = AML.adjmulist[j].firstedge; // 插入 // s2与s1的j、i调换
		s2->jlink = AML.adjmulist[i].firstedge; // 插入
		s2->w = W[k]; // 权值
		if (incInfo) // 用来存储权值以外的有关弧的信息
		{
			// s1
			s1->info = new InfoType[MAX_INFO];
			strcpy(s1->info, Info[k]);
			// s2
			s2->info = new InfoType[MAX_INFO];
			strcpy(s2->info, Info[k]);
		}
		/* 将新结点s1插入到顶点结点所指向的弧结点的第一个 */
		AML.adjmulist[i].firstedge  = s1; // 成功插入结点s1
		/* 将新结点s2插入到顶点结点所指向的弧结点的第一个 */
		AML.adjmulist[j].firstedge  = s2; // 成功插入结点s2
	}
	return OK;
}

// 邻接多重表表示法：显示无向图、无向网
void DisplayAMLGraph(AMLGraph &AML, GraphKind kind)
{
	/* 显示图、网信息 */
	EBox *p = NULL;
	cout << endl;
	cout << "/*---邻接多重表表示法如下---*/" << endl;
	if (kind == UDG)
	{
		// 邻接多重表表示法显示无向图
		for (int i = 0; i < AML.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << AML.adjmulist[i].data;
			p = AML.adjmulist[i].firstedge;
			while (p != NULL)
			{
				cout << " -> |" << p->ivex << "|" << p->jvex << "|";
				p = p->ilink;
			}
			cout << "∧|" << endl;
		}
	}
	else if (kind == UDN)
	{
		// 邻接多重表表示法显示无向网
		for (int i = 0; i < AML.vexnum; i++)
		{
			cout << setiosflags(ios::left) << setw(2) << i << setw(5) << AML.adjmulist[i].data;
			p = AML.adjmulist[i].firstedge;
			while (p != NULL)
			{
				cout << " -> |" << p->ivex << "|" << p->jvex << "|" << p->w << "|";
				p = p->ilink;
			}
			cout << "∧|" << endl;
		}
	}


	/* 显示边信息 */
	if (IncInfo)
		cout << "---边信息如下---" << endl;
	// 显示无向图、无向网边信息
	if (IncInfo)
	{
		for (int i = 0; i < AML.vexnum; i++)
		{
			p = AML.adjmulist[i].firstedge;
			int j;
			while (p != NULL)
			{
				j = p->jvex;
				cout << AML.adjmulist[i].data << " -> " << AML.adjmulist[j].data << ": " << p->info << endl;
				p = p->ilink;
			}
		}
	}
}

// 寻找v在图中的下标
int LocateVex_AML(AMLGraph &AML, VertexType v) 
{
	for (int i = 0; i < AML.vexnum; i++)
	{
		if (strcmp(AML.adjmulist[i].data, v) == 0)
			return i;
	}
	exit(0);
	return -1;
}



// 用户输入信息
void UserInput(GraphKind kind)
{
	int i;
	switch (kind)
	{
	case DG:
		cout << "--请依次输入关于有向图的信息--" << endl;
		cout << "顶点数 :";
		cin >> Vexnum;
		cout << "边数 :";
		cin >> Arcnum;
		cout << "每条弧是否有相关信息?(1是/0否) :";
		cin >> IncInfo;
		cout << "请依次输入" << Vexnum << "个顶点的名字" << endl;
		for (i = 0; i < Vexnum; i++)
		{
			cout << "顶点" << i+1 << "的名字 :";
			cin >> Vexs[i];
		}
		for (i = 0; i < Arcnum; i++)
		{
			cout << "<第" << i + 1 << "条边>" << endl;
			cout << "弧尾名字 :";
			cin >> V1[i];
			cout << "弧头名字 :";
			cin >> V2[i];
			if (IncInfo)
			{
				cout << "弧相关信息 :";
				Info[i] = new InfoType[MAX_INFO];
				cin >> Info[i];
			}
		}
		break;

	case DN:
		cout << "--请依次输入关于有向网的信息--" << endl;
		cout << "顶点数 :";
		cin >> Vexnum;
		cout << "边数 :";
		cin >> Arcnum;
		cout << "每条弧是否有相关信息?(1是/0否) :";
		cin >> IncInfo;
		cout << "请依次输入" << Vexnum << "个顶点的名字" << endl;
		for (i = 0; i < Vexnum; i++)
		{
			cout << "顶点" << i + 1 << "的名字 :";
			cin >> Vexs[i];
		}
		for (i = 0; i < Arcnum; i++)
		{
			cout << "<第" << i + 1 << "条边>" << endl;
			cout << "弧尾名字 :";
			cin >> V1[i];
			cout << "弧头名字 :";
			cin >> V2[i];
			cout << "权值 :";
			cin >> W[i];
			if (IncInfo)
			{
				cout << "弧相关信息 :";
				Info[i] = new InfoType[MAX_INFO];
				cin >> Info[i];
			}
		}
		break;

	case UDG:
		cout << "--请依次输入关于无向图的信息--" << endl;
		cout << "顶点数 :";
		cin >> Vexnum;
		cout << "边数 :";
		cin >> Arcnum;
		cout << "每条弧是否有相关信息?(1是/0否) :";
		cin >> IncInfo;
		cout << "请依次输入" << Vexnum << "个顶点的名字" << endl;
		for (i = 0; i < Vexnum; i++)
		{
			cout << "顶点" << i + 1 << "的名字 :";
			cin >> Vexs[i];
		}
		for (i = 0; i < Arcnum; i++)
		{
			cout << "<第" << i + 1 << "条边>" << endl;
			cout << "顶点A为 :";
			cin >> V1[i];
			cout << "顶点B为 :";
			cin >> V2[i];
			if (IncInfo)
			{
				cout << "弧相关信息 :";
				Info[i] = new InfoType[MAX_INFO];
				cin >> Info[i];
			}
		}
		break;

	case UDN:
		cout << "--请依次输入关于无向网的信息--" << endl;
		cout << "顶点数 :";
		cin >> Vexnum;
		cout << "边数 :";
		cin >> Arcnum;
		cout << "每条弧是否有相关信息?(1是/0否) :";
		cin >> IncInfo;
		cout << "请依次输入" << Vexnum << "个顶点的名字" << endl;
		for (i = 0; i < Vexnum; i++)
		{
			cout << "顶点" << i + 1 << "的名字 :";
			cin >> Vexs[i];
		}
		for (i = 0; i < Arcnum; i++)
		{
			cout << "<第" << i + 1 << "条边>" << endl;
			cout << "顶点A为 :";
			cin >> V1[i];
			cout << "顶点B为 :";
			cin >> V2[i];
			cout << "权值 :";
			cin >> W[i];
			if (IncInfo)
			{
				cout << "弧相关信息 :";
				Info[i] = new InfoType[MAX_INFO];
				cin >> Info[i];
			}
		}
		break;
	default:
		break;
	}

}


int main()
{
	MGraph M;  // 数组表示法
	ALGraph AL; // 邻接表表示法
	OLGraph OL; // 十字链表表示法
	AMLGraph AML; // 邻接多重表表示法
	int choice;
	cout << "您要创建的图是? 0.有向图 1.有向网 2.无向图 3.无向网(请输入数字，并按下回车)" << endl;
	cout << "选择 :";
	cin >> choice;
	switch (choice)
	{
	case DG:
		cout << "(注意: 邻接多重表无法表示有向图)" << endl;
		UserInput(GraphKind(choice)); // 用户进行输入，有向图有关的信息
		CreateDG_M(M);		// 创建有向图(数组表示法)
		CreateDG_AL(AL);	// 创建有向图(邻接表表示法)
		CreateDG_OL(OL);	// 创建有向图(十字链表表示法)
		//CreateDG_AML(AML);
		DisplayMGraph(M, GraphKind(choice));	// 显示有向图(数组表示法)
		DisplayALGraph(AL, GraphKind(choice));	// 显示有向图(邻接表表示法)
		DisplayOLGraph(OL, GraphKind(choice));	// 显示有向图(十字链表表示法)
		//DisplayAMLGraph(AML, GraphKind(choice));
		break;

	case DN:
		cout << "(注意: 邻接多重表无法表示有向网)" << endl;
		UserInput(GraphKind(choice)); // 用户进行输入，有向网有关的信息
		CreateDN_M(M);		// 创建有向网(数组表示法)
		CreateDN_AL(AL);	// 创建有向网(邻接表表示法)
		CreateDN_OL(OL);	// 创建有向网(十字链表表示法)
		//CreateDN_AML(AML);
		DisplayMGraph(M, GraphKind(choice));	// 显示有向网(数组表示法)
		DisplayALGraph(AL, GraphKind(choice));	// 显示有向网(邻接表表示法)
		DisplayOLGraph(OL, GraphKind(choice));	// 显示有向网(十字链表表示法)
		//DisplayAMLGraph(AML, GraphKind(choice));
		break;

	case UDG:
		cout << "(注意: 十字链表无法表示无向图)" << endl;
		UserInput(GraphKind(choice)); // 用户进行输入，无向图有关的信息
		CreateUDG_M(M);		// 创建无向图(数组表示法)
		CreateUDG_AL(AL);	// 创建无向图(邻接表表示法)
		//CreateUDG_OL(OL);
		CreateUDG_AML(AML);	// 创建无向图(邻接多重表表示法)
		DisplayMGraph(M, GraphKind(choice));	// 显示无向图(数组表示法)
		DisplayALGraph(AL, GraphKind(choice));	// 显示无向图(邻接表表示法)
		//DisplayOLGraph(OL, GraphKind(choice));
		DisplayAMLGraph(AML, GraphKind(choice));// 显示无向图(邻接多重表表示法)
		break;

	case UDN:
		cout << "(注意: 十字链表无法表示无向网)" << endl;
		UserInput(GraphKind(choice)); // 用户进行输入，无向网有关的信息
		CreateUDN_M(M);		// 创建无向网(数组表示法)
		CreateUDN_AL(AL);	// 创建无向网(邻接表表示法)
		//CreateUDN_OL(OL);
		CreateUDN_AML(AML);	// 创建无向网(邻接多重表表示法)
		DisplayMGraph(M, GraphKind(choice));	// 显示无向网(数组表示法)
		DisplayALGraph(AL, GraphKind(choice));	// 显示无向网(邻接表表示法)
		//DisplayOLGraph(OL, GraphKind(choice));
		DisplayAMLGraph(AML, GraphKind(choice));// 显示无向网(邻接多重表表示法)
		break;

	default:
		break;
	}

	return 0;
}
