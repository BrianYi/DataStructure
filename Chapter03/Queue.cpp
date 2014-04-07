#include "Queue.h"
#include <iostream>
using namespace std;

// 构造一个空队列Q
// PASS
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
// 销毁队列Q, Q不再存在
// PASS
Status DestroyQueue(LinkQueue &Q)
{
	ClearQueue(Q);
	
	free(Q.front);// 销毁头结点
	Q.front = Q.rear = NULL;

	return OK;
}

// 把Q置为空队列
// PASS
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr q = NULL;
	QueuePtr p = Q.front->next; // 指向第一个结点
	while (p != Q.front && p != NULL) // 不为头结点时
	{
		q = p;
		p = p->next;
		cout << q->data << " -> ";
		free(q);
	}
	Q.rear = Q.front;
	return OK;
}

// 若队列Q为空队列，则返回TRUE，否则返回FALSE
// PASS
Status QueueEmpty(LinkQueue &Q)
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

// 返回S的元素个数，即队列的长度
// PASS
int QueueLength(LinkQueue Q)
{
	QueuePtr p = Q.front;
	int len = 0;
	while (p != Q.rear)
	{
		p = p->next;
		len++;
	}
	return len;
}

// 若队列不空，则用e返回Q的对头元素，并返回OK;否则返回ERROR
// PASS
Status GetHead(LinkQueue Q, QElemType &e)
{
	if (QueueEmpty(Q))
		return ERROR;
	e = Q.front->next->data;
	return OK;
}

// 插入元素e为Q的新的队尾元素
// PASS
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr s = (QNode*)malloc(sizeof(QNode));
	if (!s)
		exit(OVERFLOW);
	s->data = e;
	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
	return OK;
}

// 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
// PASS
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
		return ERROR;
	
	QueuePtr q = Q.front->next;
	e = q->data;
	Q.front->next = q->next;
	if (Q.rear == q)
		Q.rear = Q.front;

	free(q);
	return OK;
}

// 从队列头到队列尾依次对队列中每个元素调用函数 visit()。一旦visit()失败，则操作失败
// PASS
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType &))
{
	QueuePtr p = Q.front->next; // p指向队头第一人
	QElemType e;
	while (p != Q.rear && p != NULL) 
	{
		e = p->data;
		visit(e);
		p = p->next;
	}
	visit(e);

	return OK;
}


// PASS
Status visit(QElemType &e)
{
	cout << e << " <- ";
	return OK;
}
