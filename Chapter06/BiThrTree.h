#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;
typedef enum PointerTag { Link, Thread };
typedef char TElemType;

typedef struct BiThrNode {
	TElemType		 data;
	struct BiThrNode *lchild, *rchild;
	PointerTag		 LTag, RTag;
}BiThrNode, *BiThrTree;

BiThrTree pre = 0;

void InitBiThrTree(BiThrTree& T);// 构造空线索二叉树
void DestroyBiThrTree(BiThrTree& T);// 销毁线索二叉树--按后序遍历
void CreateBiThrTree(BiThrTree& T);// 构造线索二叉树, 按先(前)序遍历  （根左右）
Status PreOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e));// 先序遍历T，对每个结点调用函数Visit一次
Status InOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e));// 中序遍历T，对每个结点调用函数Visit一次
Status PostOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e));// 后序遍历T，对每个结点调用函数Visit一次
Status LevelOrderTraverse(BiThrTree T, Status(*Visit)(TElemType e));// 层序遍历T，对每个结点调用函数Visit一次
void PreOrderThreading(BiThrTree p); // 前序线索化
void InOrderThreading(BiThrTree p); // 中序线索化
void PostOrderThreading(BiThrTree p); // 后序线索化
void LevelOrderThreading(BiThrTree p); // 层序线索化
Status Visit(TElemType e);
