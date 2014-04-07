#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define SElemType int

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S); // 构造一个空栈S
Status DestroyStack(SqStack &S); // 销毁栈S, S不再存在
Status ClearStack(SqStack &S); // 把S置为空栈
Status StackEmpty(SqStack &S); // 若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack S); // 返回S的元素个数，即栈的长度
SElemType GetTop(SqStack S); // 若栈不空，则用e返回S的栈顶元素，并返回OK;否则返回ERROR
Status Push(SqStack &S, SElemType e); // 插入元素e为新的栈顶元素
Status Pop(SqStack &S, SElemType &e); // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status StackTraverse(SqStack S, Status(*visit)(SElemType &)); // 从栈底到栈顶依次对栈中每个元素调用函数 visit()。一旦visit()失败，则操作失败
Status transfer(SqStack &S); /*自己加的函数*/ // 栈内内容全部颠倒
Status visit(SElemType &);
