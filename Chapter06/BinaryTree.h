#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;
typedef char TElemType;

typedef struct BiTNode {
	TElemType		data;
	struct BiTNode	*lchild, *rchild;
	int flag; // 用来标记非递归后序遍历时，该元素第几次出现在栈顶
}BiTNode, *BiTree;

void InitBiTree(BiTree& T);
void DestroyBiTree(BiTree& T);
void CreateBiTree(BiTree& T);
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status PreOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e));
Status PostOrderTraverse_Stack(BiTree T, Status(*Visit)(TElemType e));
Status Visit(TElemType e);
