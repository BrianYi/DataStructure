#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

//#define QElemType char
/*typedef struct {
	int ArrivalTime;
	int Duration;
}QElemType;*/

extern struct BiTNode;
typedef BiTNode *QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue &Q); // 构造一个空队列Q
Status DestroyQueue(LinkQueue &Q); // 销毁队列Q, Q不再存在
Status ClearQueue(LinkQueue &Q); // 把Q置为空队列
Status QueueEmpty(LinkQueue &Q); // 若队列Q为空队列，则返回TRUE，否则返回FALSE
int QueueLength(LinkQueue Q); // 返回S的元素个数，即队列的长度
Status GetHead(LinkQueue Q, QElemType &e); // 若队列不空，则用e返回Q的对头元素，并返回OK;否则返回ERROR
Status EnQueue(LinkQueue &Q, QElemType e); // 插入元素e为Q的新的队尾元素
Status DeQueue(LinkQueue &Q, QElemType &e); // 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType &)); // 从队列头到队列尾依次对队列中每个元素调用函数 visit()。一旦visit()失败，则操作失败
