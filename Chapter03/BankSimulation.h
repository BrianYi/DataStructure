#include "Queue.h"
#include "LinkList.h"



typedef LinkList EventList;



EventList	ev;
Event		en;
LinkQueue	q[5];
QElemType	customer;
int			TotalTime, CustomerNum;
int			CloseTime = 10 * 60; // 银行关门时间 假设营业10小时

int cmp(Event a, Event b);
void OpenForDay();
void CustomerArrived(int CloseTime);
void CustomerDeparture();
void Bank_Simulation(int CloseTime);
