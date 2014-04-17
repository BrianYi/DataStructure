#pragma once
#include <LIMITS>

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define INFINITY INT_MAX // 无穷大
#define MAX_VERTEX_NUM 20 // 限制顶点最大数值为20个
#define MAX_ARC_NUM  MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) // 由n个顶点，最多可以确定n(n-2)/2条直线,有向图为2倍
#define MAX_INFO 20 // 用户输入的弧信息，最多20个字符

/*数组表示法*/
typedef int		VRType;
typedef char	InfoType;
typedef char	VertexType[5];
typedef enum	{DG, DN, UDG, UDN} GraphKind; 

typedef struct ArcCell {
	VRType adj;
	InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType	vexs[MAX_VERTEX_NUM];
	AdjMatrix	arcs;
	int			vexnum, arcnum;
}MGraph;

Status CreateDG_M(MGraph &M); // 构造有向图
Status CreateDN_M(MGraph &M); // 构造有向网
Status CreateUDG_M(MGraph &M); // 构造无向图
Status CreateUDN_M(MGraph &M); // 构造无向网
// 数组表示法：显示有向图、有向网、无向图、无向网
void DisplayMGraph(MGraph &M, GraphKind kind); 
int LocateVex_M(MGraph &M, VertexType v); // 寻找v在图中的下标



/*邻接表表示法*/
typedef struct ArcNode {
	int				adjvex;
	int				w; // 存储权值，书中的程序没有表示权值的数据成员(书中说用info来存储权值，但是上面的程序又是单独用的adj存权值，为了一致性，info还是用来存储其他信息算了)
	struct ArcNode	*nextarc;
	InfoType		*info; // 用来存储权值以外的有关弧的信息
}ArcNode;

typedef struct VNode {
	VertexType	data;
	ArcNode		*firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList		vertices;
	int			vexnum, arcnum;
	int			kind;
}ALGraph;

Status CreateDG_AL(ALGraph &AL); // 构造有向图
Status CreateDN_AL(ALGraph &AL); // 构造有向网
Status CreateUDG_AL(ALGraph &AL); // 构造无向图
Status CreateUDN_AL(ALGraph &AL); // 构造无向网
// 邻接表表示法：显示有向图、有向网、无向图、无向网
void DisplayALGraph(ALGraph &AL, GraphKind kind);
int LocateVex_AL(ALGraph &AL, VertexType v); // 寻找v在图中的下标


/*十字链表表示法*/
typedef struct ArcBox {
	int				tailvex, headvex;
	struct ArcBox	*hlink, *tlink;
	int				w; // 存储权值，书中的程序没有表示权值的数据成员(书中说用info来存储权值，但是上面的程序又是单独用的adj存权值，为了一致性，info还是用来存储其他信息算了)
	InfoType		*info; // 用来存储权值以外的有关弧的信息
}ArcBox;

typedef struct VexNode {
	VertexType		data;
	ArcBox			*firstin, *firstout;
}VexNode;

typedef struct {
	VexNode		xlist[MAX_VERTEX_NUM];
	int			vexnum, arcnum;
}OLGraph;

Status CreateDG_OL(OLGraph &OL); // 构造有向图
Status CreateDN_OL(OLGraph &OL); // 构造有向网
// 十字链表表示法：显示有向图、有向网
void DisplayOLGraph(OLGraph &OL, GraphKind kind); 
int LocateVex_OL(OLGraph &OL, VertexType v); // 寻找v在图中的下标



/*邻接多重表表示法*/
typedef enum { unvisited, visited } VisitIf;
typedef struct EBox {
	VisitIf		mark;
	int			ivex, jvex;
	struct EBox	*ilink, *jlink;
	int			w; // 存储权值，书中的程序没有表示权值的数据成员(书中说用info来存储权值，但是上面的程序又是单独用的adj存权值，为了一致性，info还是用来存储其他信息算了)
	InfoType	*info;
}EBox;

typedef struct VexBox {
	VertexType	data;
	EBox		*firstedge;
}VexBox;

typedef struct {
	VexBox		adjmulist[MAX_VERTEX_NUM];
	int			vexnum, arcnum;
}AMLGraph;

Status CreateUDG_AML(AMLGraph &AML); // 构造无向图
Status CreateUDN_AML(AMLGraph &AML); // 构造无向网
// 邻接多重表表示法：显示无向图、无向网
void DisplayAMLGraph(AMLGraph &AML, GraphKind kind);
int LocateVex_AML(AMLGraph &AML, VertexType v); // 寻找v在图中的下标


/*全局变量*/
int			Vexnum, Arcnum, IncInfo; // 存储用户输入的顶点数，边数，弧是否含有相关信息
VertexType	Vexs[MAX_VERTEX_NUM]; // 存储用户输入的顶点名字
VertexType  V1[MAX_ARC_NUM], V2[MAX_ARC_NUM];// 存入用户输入的顶点
int			W[MAX_ARC_NUM];// 存入用户输入的权值
InfoType	*Info[MAX_ARC_NUM]; // 存入用户输入的弧信息

/*公用函数*/
void UserInput(GraphKind kind); // 用户输入信息
