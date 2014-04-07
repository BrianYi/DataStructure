#include "Queue.h"
#include <iostream>
using namespace std;

int main()
{
	LinkQueue Q;
	InitQueue(Q);
	int n = 0;
	char m;
	while (cin >> n, n != -1)
	{
		while (n--, n >= 0)
		{
			cin >> m;
			EnQueue(Q, m);
			DeQueue(Q, m);
			cout << m << " <- ";
		}
	}
	if (QueueEmpty(Q))
		cout << "空" << QueueLength(Q) << endl;
	else
		cout << "非空" << QueueLength(Q) << endl;

	DestroyQueue(Q);
	return 0;
}
