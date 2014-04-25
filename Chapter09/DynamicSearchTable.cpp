#include "DynamicSearchTable.h"
#include <iostream>
using namespace std;

// 查找
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p)
{
	// 在根指针T所指的二叉排序树中递归的查找其关键字等于key的数据元素
	// ① 若查找成功，则指针p指向该数据元素结点，并返回TRUE
	// ② 否则，则指针p指向查找路径上访问的最后一个结点并返回FALSE,指针f指向T的双亲，初始调用值为NULL
	if (!T) // 查找不成功
	{
		p = f;
		return FALSE;
	}
	else if (EQ(key, T->data.key)) // 查找成功
	{
		p = T;
		return TRUE;
	}
	else if (LT(key, T->data.key)) // key值小于当前结点的值，到左子树中继续查找
		return SearchBST(T->lchild, key, T, p);
	else // key值大于当前结点的值，到右子树中继续查找
		return SearchBST(T->rchild, key, T, p);
}

// 插入
Status InsertBST(BiTree &T, SElemType e)
{
	// 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE
	// 否则返回FALSE
	BiTree p = NULL;
	BiTNode *s = NULL;
	if (!SearchBST(T, e.key, NULL, p))
	{
		s = new BiTNode; // 创建结点
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p) // T为空树
			T = s;
		else if (LT(e.key, p->data.key)) // e.key值小于当前结点的值
			p->lchild = s; // 插入左孩子
		else // e.key值大于当前结点的值
			p->rchild = s; // 插入右孩子
		return TRUE;
	}
	return FALSE;
}

// 删除
Status DeleteBST(BiTree &T, KeyType key)
{
	// 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点
	// 并返回TRUE；否则返回FALSE
	if (!T) // 空树
		return FALSE;
	else if (EQ(key, T->data.key)) // 找到关键字等于key的数据元素
		return Delete(T);
	else if (LT(key, T->data.key)) // 未找到，并且key的值小于当前结点的值
		return DeleteBST(T->lchild, key); // 继续探索左子树
	else // 未找到，并且key的值大于当前结点的值
		return DeleteBST(T->rchild, key); // 继续探索右子树
}

// 删除(子函数)
Status Delete(BiTree &p)
{
	// 从二叉排序树中删除结点p，并重接它的左或右子树
	BiTNode *q = NULL, *h = NULL, *pre = NULL;
	if (!p->rchild) // 右子树为空，则重接左子树即可
	{
		q = p;
		p = p->lchild;
		delete q;
	}
	else if (!p->lchild) // 左子树为空，则重接右子树即可
	{
		q = p;
		p = p->rchild;
		delete q;
	}
	else // 左右子树均不空(这里不好理解的话，看一下视频)
	{
		h = p; // h指向被删结点
		pre = h;
		p = h->lchild;
		while (p->rchild) // 转左，然后向右到尽头
		{
			pre = p;
			p = p->rchild;
		}
		h->data = p->data; // p指向被删结点的“前驱”
		q = p;
		if (pre != h) // 被删结点的“前驱”不是左孩子
			pre->rchild = p->lchild; // 重接*pre的右子树
		else // 被删结点的“前驱”就是左孩子
			pre->lchild = p->lchild; // 重接*pre的左子树
		delete q;
	}
	return TRUE;
}

// 下图为二叉排序树的一个例子
//           H
//      D	     J
//   B    F	  #		#
//  # #  # #
// 输入：HDB##E##J##
int main()
{
	while (true) {
		// 输入
		BiTree T;
		cout << "请按先(前)序遍历输入二叉排序树('#'表示空): ";
		CreateBiTree(T);
		KeyType key;

		// 查找元素
		cout << "请输入要查找的元素的key: ";
		cin >> key;
		BiTree p = NULL;
		int result = SearchBST(T, key, NULL, p);
		if (result == OK)
			cout << "元素为: " << p->data.key << endl;
		else
			cout << "没有该元素！" << endl;
		cout << "当前二叉排序树前序遍历为: ";
		PreOrderTraverse(T, Visit);
		cout << endl;

		// 插入元素
		cout << "请输入要插入的元素key: ";
		cin >> key;
		SElemType e;
		e.key = key;
		result = InsertBST(T, e);
		if (result == OK)
			cout << "插入成功!" << endl;
		else
			cout << "已有该元素！" << endl;
		cout << "当前二叉排序树前序遍历为: ";
		PreOrderTraverse(T, Visit);
		cout << endl;

		// 删除元素
		cout << "请输入要删除的元素key: ";
		cin >> key;
		result = DeleteBST(T, key);
		if (result == OK)
			cout << "删除成功!" << endl;
		else
			cout << "没有该元素!" << endl;
		cout << "当前二叉排序树前序遍历为: ";
		PreOrderTraverse(T, Visit);
		cout << endl;

		DestroyBiTree(T);
	}
	return 0;
}
