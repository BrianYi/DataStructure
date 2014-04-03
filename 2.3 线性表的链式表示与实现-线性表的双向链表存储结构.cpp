#include <iostream>
using namespace std;

#include "LinkList.h"

int main()
{
	LinkList A, B;
	InitList(A);
	InitList(B);
	Link p = NULL, q = NULL, s = NULL;
	int m, n;
	cin >> m >> n;
	while (m--)
	{
		char tmp;
		cin >> tmp;
		MakeNode(p, tmp);
		Position ALast = GetLast(A);
		InsAfter(A, ALast, p);
	}

	while (n--)
	{
		char tmp;
		cin >> tmp;
		MakeNode(p, tmp);
		Position BLast = GetLast(B);
		InsAfter(B, BLast, p);
	}

	ListTraverse(A, visit);
	ListTraverse(B, visit);

	LinkList C;
	MergeList_L(A, B, C, compare);
	ListTraverse(C, visit);

	return 0;
}

// 分配由p指向的值为e的结点，并返回OK;若分配失败，则返回ERROR;
// PASS
Status MakeNode(Link &p, ElemType e)
{
	p = new LNode;
	if (!p)
		return ERROR;
	else
	{
		p->data = e;
		return OK;
	}
}

// 释放P所指的结点
// PASS
void FreeNode(Link &p)
{
	delete p;
	p = NULL;
}

// 构造一个空的线性链表
// PASS
Status InitList(LinkList &L)
{
	L.len = 0;
	L.head = new LNode;
	L.tail = L.head;
	return OK;
}


// 销毁线性链表L, L不再存在
// PASS
Status DestroyList(LinkList &L)
{
	Link p = L.head;
	Link q = p;
	cout << "DestroyList: " << endl;
	// 摧毁其他结点
	ClearList(L);
	// 摧毁头结点
	FreeNode(L.head);
	L.len = 0;
	
	return OK;
}


// 将线性链表L重置为空表，并释放原链表的结点空间
// PASS
Status ClearList(LinkList &L)
{
	Link p = L.head->next; // p指向后面一个结点
	Link q = p; // q指向当前结点
	L.head->next = NULL; 

	cout << "ClearList: " << endl;
	while (p != NULL)
	{
		p = p->next;
		cout << q->data << " ";
		FreeNode(q);
		q = p;
	}
	cout << endl;
	L.len = 0;
	return OK;
}

// 已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
// PASS
Status InsFirst(LinkList &L, Link h, Link s)
{
	// 头插法插入结点
	s->next = h->next;
	h->next = s;

	// 尾指针位置变化
	Link p = h;
	Link q = p;
	while (p != NULL)
	{
		q = p;
		p = p->next;
	}
	L.tail = q;

	// 长度变化
	L.len++;
	return OK;
}

// 已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
// PASS
Status DelFirst(LinkList &L, Link h, Link &q)
{
	// 脱离结点
	q = h->next;
	h->next = q->next;
	
	// 让结点完全脱离
	q->next = NULL;

	// 尾指针位置变化
	if (q == L.tail)
		L.tail = h;

	// 长度变化
	L.len--;
	return OK;
}


// 将指针s所指(彼此以指针相链)的一串结点链接在线性链表L的最后一个
// 结点之后，并改变链表L的尾指针指向新的尾结点
// PASS
Status Append(LinkList &L, Link s)
{
	Link p = L.head; // 指向当前结点
	Link q = p; // 指向前一个结点
	while (p != NULL)
	{
		q = p;
		p = p->next;
	}

	q->next = s;
	p = s;

	int i = 0;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		i++;
	}

	// 尾指针位置变化
	L.tail = q;

	// 长度变化
	L.len += i;

	return OK;
}

// 删除线性链表L中的尾结点并以q返回，改变链表L的为指针指向新的尾结点
// PASS
Status Remove(LinkList &L, Link &q)
{
	Link p = L.head; // 指向当前结点
	Link s = p; // 指向前一个结点
	p = s->next;
	while (p->next != NULL)
	{
		s = p; 
		p = p->next;
	}
	q = p; // 返回最后一个结点
	s->next = NULL; // 删除最后一个结点

	// 尾指针位置变化
	L.tail = s;

	// 长度变化
	L.len--;

	return OK;
}

// 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，
// 并修改指针p指向新插入的结点
// PASS
Status InsBefore(LinkList &L, Link &p, Link s)
{
	Link Lp = L.head;
	Link Lpre = Lp;
	Lp = Lpre->next;
	while (Lp != p && Lp != NULL)
	{
		Lpre = Lp;
		Lp = Lpre->next;
	}

	if (Lp == p)
	{
		// 插入s所指的结点
		s->next = Lpre->next;
		Lpre->next = s;
		L.len++;

		// 指针p指向新插入的结点
		p = s;

		return OK;
	} else
		return ERROR;
}

// 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，
// 并修改指针p指向新插入的结点
// PASS
Status InsAfter(LinkList &L, Link &p, Link s)
{
	// 找到结点位置
	Link Lp = L.head;
	while (Lp != p && Lp != NULL)
	{
		Lp = Lp->next;
	}

	if (Lp == p)
	{
		// 插入结点
		s->next = Lp->next;
		Lp->next = s;

		// 长度变化
		L.len++;
		
		// 尾指针变化
		if (s->next == NULL)
			L.tail = s;

		// 指针p指向新插入的结点
		p = s;

		return OK;
	}
	else
		return ERROR;

}

// 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
// PASS
Status SetCurElem(LinkList &L, Link &p, ElemType e)
{
	// 找到结点位置
	Link Lp = L.head;
	while (Lp != p && Lp != NULL)
	{
		Lp = Lp->next;
	}

	if (Lp == p)
	{
		// 改变值
		Lp->data = e;
		return OK;
	}
	else
		return ERROR;
}

// 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
// PASS
ElemType GetCurElem(LinkList &L, Link p)
{
	// 找到结点位置
	Link Lp = L.head;
	while (Lp != p && Lp != NULL)
	{
		Lp = Lp->next;
	}

	if (Lp == p)
	{
		// 返回值
		return Lp->data;
	}
	else
		return ERROR;
}

// 若线性链表L为空表，则返回TRUE，否则返回FALSE
// PASS
Status ListEmpty(LinkList L)
{
	return L.len == 0 ? TRUE : FALSE;
}

// 返回线性链表L中元素的个数
// PASS
int ListLength(LinkList L)
{
	return L.len;
}


// 返回线性链表L中头结点的位置
// PASS
Position GetHead(LinkList L)
{
	return L.head;
}

// 返回线性链表L中尾结点的位置
// PASS
Position GetLast(LinkList L)
{
	return L.tail;
}

// 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，
// 若无前驱，则返回NULL
// PASS
Position PriorPos(LinkList L, Link p)
{
	// 找到结点位置
	Link Lp = L.head; 
	Link Lpre = Lp; // 直接前驱
	while (Lp != p && Lp != NULL)
	{
		Lpre = Lp;
		Lp = Lp->next;
	}

	if (Lp == p)
	{
		// 返回值
		if (Lpre != NULL)
			return Lpre;
		else
			return NULL;
	}
	else
		return ERROR;
}

// 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，
// 若无后继，则返回NULL
// PASS
Position NextPos(LinkList L, Link p)
{
	// 找到结点位置
	Link Lp = L.head;
	while (Lp != p && Lp != NULL)
	{
		Lp = Lp->next;
	}

	if (Lp == p)
	{
		// 返回值
		if (Lp->next != NULL)
			return Lp->next;
		else
			return NULL;
	}
	else
		return ERROR;
}

// 返回p指示线性链表L中第i个结点的位置并返回OK,i值不合法时返回ERROR
// PASS
Status LocatePos(LinkList L, int i, Link &p)
{
	
	p = L.head;

	// 判定i是否合法
	if (i<1 || i>L.len)
		return ERROR;

	// 找到结点位置
	while (i != 0)
	{
		p = p->next;
		i--;
	}

	return OK;
}

// 返回线性链表L中第1个与e满足函数 compare() 判定关系的元素位置，
// 若不存在这样的元素，则返回NULL
// PASS
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	Link p = L.head->next;
	while (p != NULL)
	{
		if (compare(e, p->data) == OK)
			return p;
		p = p->next;
	}

	return NULL;
}

// 依次对L的每个元素调用函数 visit()。 一旦 visit()失败，则操作失败
// PASS
Status ListTraverse(LinkList L, Status(*visit)(Link))
{
	Link p = L.head->next;

	if (p == NULL)
		cout << "无任何元素" << endl;

	while (p != NULL)
	{
		if (visit(p) == ERROR)
			return ERROR;
		else
			p = p->next;
	}
	return OK;
}

// PASS
Status visit(Link p)
{
	if (p != NULL)
		cout << p->data;

	if (p->next != NULL)
		cout << "->";
	else
		cout << endl;
	return OK;
}

// PASS
Status compare(ElemType A, ElemType B)
{
	if (A == B)
		return 0;
	else if (A > B)
		return 1;
	else
		return -1;
}


// 算法2.20
// PASS
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	Link p = NULL, s = NULL;
	if (!LocatePos(L, i - 1, p))
		return ERROR;

	if (!MakeNode(s, e))
		return ERROR;

	InsFirst(L, p, s);
	return OK;
}

// 算法2.21
// PASS
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc, int(*compare)(ElemType, ElemType))
{
	if (!InitList(Lc))
		return ERROR;

	// ha 为 La 的头结点， pa 指向第一个元素
	// hb 为 Lb 的头结点， pb 指向第一个元素
	Link ha = GetHead(La), hb = GetHead(Lb), pa = NextPos(La, ha), pb = NextPos(Lb, hb);
	Link q = NULL;
	while (pa&&pb)
	{
		char a = GetCurElem(La, pa);
		char b = GetCurElem(Lb, pb);
		if ((*compare)(a, b) <= 0)
		{
			// a <= b
			DelFirst(La, ha, q); // 脱离La的第一个结点
			Append(Lc, q);		// 在Lc上添加一个结点
			pa = NextPos(La, ha); // pa现在的La的第一个结点
		}
		else
		{
			// a > b
			DelFirst(Lb, hb, q); // 脱离Lb的第一个结点
			Append(Lc, q);		// 在Lc上添加一个结点
			pb = NextPos(Lb, hb); // pb指向下一个元素
		}
	}

	if (pa) // 链接La中剩下的结点
		Append(Lc, pa);
	else    // 链接Lb中剩下的结点
		Append(Lc, pb);

	FreeNode(ha); // 释放La的头结点
	FreeNode(hb); // 释放Lb的头结点
	return OK;
}
