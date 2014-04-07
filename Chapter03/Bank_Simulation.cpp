#include "BankSimulation.h"

int cmp(Event a, Event b)
{
	if (a.OccurTime < b.OccurTime)
		return -1;
	else if (a.OccurTime == b.OccurTime)
		return 0;
	else
		return 1;
}

Status OrderInsert(LinkList &ev, ElemType en, int(*cmp)(Event, Event))
{
	Link p = ev.head->next, s = NULL;
	int reslt = 0;

	if (!MakeNode(s, en))
		exit(OVERFLOW);

	if (p == NULL)
	{
		InsFirst(ev, ev.head, s);
		return OK;
	}
	while (p != NULL)
	{
		reslt = cmp(p->data, en);
		if (reslt == 0)
		{
			InsAfter(ev, p, s);
			break;
		}
		else if (reslt == 1)
		{
			InsBefore(ev, p, s);
			break;
		}
		p = p->next;
	}
	return OK;
}

int Minimum(LinkQueue p[])
{
	int minLen = unsigned short(-1);
	int minLenIndex = 1;
	int len = 0;
	for (int i = 1; i <= 4; i++)
	{
		len = QueueLength(p[i]);
		if (minLen > len)
		{
			minLen = len;
			minLenIndex = i;
		}
	}
	return minLenIndex;
}

void OpenForDay()
{
	TotalTime = 0; CustomerNum = 0;
	InitList(ev);
	en.OccurTime = 0; en.NType = 0;
	OrderInsert(ev, en, cmp);
	for (int i = 1; i <= 4; i++)
		InitQueue(q[i]);
	//////////////////
}

void CustomerArrived(int CloseTime)
{
	++CustomerNum;
	int durtime = rand() % 10;
	int intertime = rand() % 20;
	int t = en.OccurTime + intertime;
	ElemType e;

	if (t < CloseTime)
	{
		e.OccurTime = t;
		e.NType = 0;
		OrderInsert(ev, e, cmp);
	}

	int i = Minimum(q);
	QElemType qe; 
	qe.ArrivalTime = en.OccurTime; qe.Duration = durtime;
	cout << "People " << CustomerNum << " coming, time: " << qe.ArrivalTime << ", duration: " << qe.Duration << endl;
	EnQueue(q[i], qe);
	if (QueueLength(q[i]) == 1)
	{
		e.OccurTime = en.OccurTime + durtime;
		e.NType = i;
		OrderInsert(ev, e, cmp);
	}
}

Status DelQueue(LinkQueue &qe, QElemType &customer)
{
	if (QueueEmpty(qe))
		return ERROR;
	else
		DeQueue(qe, customer);
	return OK;
}

void CustomerDeparture()
{
	int i = en.NType; DelQueue(q[i], customer);
	TotalTime += en.OccurTime - customer.ArrivalTime;

	if (!QueueEmpty(q[i]))
	{
		GetHead(q[i], customer);
		ElemType e;
		e.OccurTime = en.OccurTime + customer.Duration;
		e.NType = i;
		OrderInsert(ev, e, cmp);
	}
}

void Bank_Simulation(int CloseTime)
{
	OpenForDay();
	Link p = NULL;
	while (!ListEmpty(ev)) {
		DelFirst(ev, ev.head, p);  en = p->data;
		if (en.NType == 0)
			CustomerArrived(CloseTime);
		else
			CustomerDeparture();
	}
	cout << "The total time is " << TotalTime << endl;
	cout << "The counts is " << CustomerNum << endl;
	cout << "The Average Time is " << (float)TotalTime / (float)CustomerNum << endl;
}


int main()
{
	while (true)
	{
		Bank_Simulation(CloseTime);
		getchar();
	}
	return 0;
}
