/*
只是简单的做了下测试，里面可能还有很多BUG，希望大家能够纠正并给予指出，谢谢。
 */
#include <iostream>
#include "Stack2.h"
using namespace std;

// 构造一个空栈S
// PASS
Status InitStack(SqStack &S) 
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}; 

// 销毁栈S, S不再存在
// PASS
Status DestroyStack(SqStack &S)
{
	free(S.base);
	S.top = S.base = NULL;
	S.stacksize = 0;
	
	return OK;
};

// 把S置为空栈
// PASS
Status ClearStack(SqStack &S)
{
	SElemType e;
	while (!StackEmpty(S))
		Pop(S, e);
	return OK;
};

// 若栈S为空栈，则返回TRUE，否则返回FALSE
// PASS
Status StackEmpty(SqStack &S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
};

// 返回S的元素个数，即栈的长度
// PASS
int StackLength(SqStack S)
{
	return S.top - S.base;
};

// 若栈不空，则用e返回S的栈顶元素，并返回OK;否则返回ERROR
// PASS
Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	else
	{
		e = *(S.top - 1);
		return OK;
	}
};

// 插入元素e为新的栈顶元素
// PASS
Status Push(SqStack &S, SElemType e)
{
	// 栈满 ? 追加存储空间 : 不追加存储空间;
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	// 将元素e放入栈顶
	*S.top++ = e;

	return OK;
};

// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
// PASS
Status Pop(SqStack &S, SElemType &e)
{
	// 栈空? 返回ERROR : 删除栈顶元素，并e返回值
	if (StackEmpty(S))
		return ERROR;
	else
	{
		// 将元素e抛出栈顶
		e = *(--S.top);
		// cout << "POP: " << StackLength(S) << " " << e << endl;
		return OK;
	}
};

// 从栈底到栈顶依次对栈中每个元素调用函数 visit()。一旦visit()失败，则操作失败
// PASS
Status StackTraverse(SqStack S, Status(*visit)(SElemType &))
{
	SElemType e;
	SElemType *buttom = S.base;

	while (buttom != S.top)
	{
		e = *buttom;
		visit(e);
		buttom++;
	}

	return OK;
};

/*自己加的函数*/
// 栈内内容全部颠倒
// PASS
Status transfer(SqStack &S)
{
	SElemType *pBase = (SElemType *)malloc(StackLength(S) * sizeof(SElemType)), *pTop = NULL, *p = NULL;
	SElemType e;

	pTop = pBase;
	p = pBase;

	while (!StackEmpty(S))
	{
		Pop(S, e);
		*pTop++ = e;
	}
	while (p != pTop)
	{
		Push(S, *p++);
	}

	free(pBase);
	return OK;
}

// PASS
Status visit(SElemType &e)
{
	cout << e;
	return OK;
};
