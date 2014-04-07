#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define ElemType char

typedef struct LNode {
	LNode() { data = 0; next = NULL; }
	ElemType		data;
	struct LNode	*next;
} *Link, *Position;

typedef struct {

	Link	head, tail;
	int		len;
} LinkList;


// 分配由p指向的值为e的结点，并返回OK;若分配失败，则返回ERROR;
Status MakeNode(Link &p, ElemType e);

// 释放P所指的结点
void FreeNode(Link &p);

// 构造一个空的线性链表
Status InitList(LinkList &L);

// 销毁线性链表L, L不再存在
Status DestroyList(LinkList &L);

// 将线性链表L重置为空表，并释放原链表的结点空间
Status ClearList(LinkList &L);

// 已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status InsFirst(LinkList &L, Link h, Link s);

// 已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status DelFirst(LinkList &L, Link h, Link &q);

// 将指针s所指(彼此以指针相链)的一串结点链接在线性链表L的最后一个
// 结点之后，并改变链表L的为指针指向新的尾结点
Status Append(LinkList &L, Link s);

// 删除线性链表L中的尾结点并以q返回，改变链表L的为指针指向新的尾结点
Status Remove(LinkList &L, Link &q);

// 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，
// 并修改指针p指向新插入的结点
Status InsBefore(LinkList &L, Link &p, Link s);

// 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，
// 并修改指针p指向新插入的结点
Status InsAfter(LinkList &L, Link &p, Link s);

// 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
Status SetCurElem(LinkList &L, Link &p, ElemType e);

// 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
ElemType GetCurElem(LinkList &L, Link p);

// 若线性链表L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty(LinkList L);

// 返回线性链表L中元素的个数
int ListLength(LinkList L);

// 返回线性链表L中头结点的位置
Position GetHead(LinkList L);

// 返回线性链表L中尾结点的位置
Position GetLast(LinkList L);

// 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，
// 若无前驱，则返回NULL
Position PriorPos(LinkList L, Link p);

// 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，
// 若无后继，则返回NULL
Position NextPos(LinkList L, Link p);

// 返回p指示线性链表L中第i个结点的位置并返回OK,i值不合法时返回ERROR
Status LocatePos(LinkList L, int i, Link &p);

// 返回线性链表L中第1个与e满足函数 compare() 判定关系的元素位置，
// 若不存在这样的元素，则返回NULL
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));

// 依次对L的每个元素调用函数 visit()。 一旦 visit()失败，则操作失败
Status ListTraverse(LinkList L, Status(*visit)(Link));

Status visit(Link);
Status compare(ElemType A, ElemType B);

Status ListInsert_L(LinkList &L, int i, ElemType e);
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc, int(*compare)(ElemType, ElemType));
