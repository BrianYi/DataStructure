#pragma once
#include "GraphTraverse.h"

typedef VertexType ElemType; // 每个元素最多存储5个字符

/*树的二叉链表孩子兄弟表示法*/
typedef struct CSNode {
ElemType		data;
struct CSNode	*firstchild, *nextsibling;
}CSNode, *CSTree;

void DFSForest(ALGraph &AL, CSTree &T); // 建立无向图AL的深度优先生成森林
void DFSTree(ALGraph &AL, int v, CSTree &T); // 从第v个顶点出发深度优先遍历图AL,建立以T为根的生成树
void DFSForestTraverse(CSTree p); // 深度优先遍历，显示生成森林
void BFSForestTraverse(ALGraph &AL, CSTree p); // 广度优先遍历，显示生成森林
void VisitForest(CSTree p);
