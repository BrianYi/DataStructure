#include <iostream>
#include "Polynomial.h"
using namespace std;


int main()
{
	while (true) 
	{
		int m, n;
		cin >> m >> n;
		polynomial p1, p2;
		CreatPolyn(p1, m);
		PrintPoly(p1); 
		CreatPolyn(p2, n);
		PrintPoly(p2);

		AddPolyn(p1, p2);
		PrintPoly(p1);

		DestroyPoly(p1);
	}
	return 0;
}

// 输入m项的系数和指数，建立表示一元多项式的有序链表P
// PASS
void CreatPolyn(polynomial &P, int m)
{
	InitList(P); 
	Link h = GetHead(P);
	Link q = NULL, s = NULL;
	term e;
	e.coef = 0.0; e.expn = -1;
	SetCurElem(P, h, e); // 头结点初始化

	for (int i = 0; i < m; i++)
	{
		cin >> e.coef >> e.expn;
		if (MakeNode(s, e))
			InsAfter(P, P.tail, s);
	}
}

// 销毁一元多项式P
// PASS
void DestroyPoly(polynomial &P)
{
	Link p = P.head;
	Link q = p;

	cout << "DestroyPoly: ";
	while (p != NULL)
	{
		q = p;
		p = p->next;

		cout << q->data.coef << "x" << q->data.expn;
		if (p != NULL)
			cout << " + ";
		else
			cout << endl;

		FreeNode(q);
	}
	
}

// 打印输出一元多项式P
// PASS
void PrintPoly(polynomial P)
{
	Link p = P.head;

	while (p->next != NULL)
	{
		p = p->next;
		cout << p->data.coef << "x^" << p->data.expn;
		if (p->next != NULL)
		{
			if (p->next->data.coef > 0)
				cout << " + ";
		}
		else
			cout << endl;
	}
}

// 返回一元多项式P中的项数
// PASS
int PolynLength(polynomial P)
{
	int len = 0;
	Link p = P.head->next;
	while (p != NULL)
	{
		p = p->next;
		len++;
	}
	
	return len;
}

// 完成多项式相加运算，即：Pa = Pa + Pb，并销毁一元多项式Pb
void AddPolyn(polynomial &Pa, polynomial &Pb)
{
	Link ha = GetHead(Pa), hb = GetHead(Pb);
	Link qa = NextPos(Pa, ha), qb = NextPos(Pb, hb);
	Link q = NULL;
	float sum = 0.0;
	while (qa && qb)
	{
		term a = GetCurElem(Pa, qa);
		term b = GetCurElem(Pb, qb);
		switch (cmp(a, b))
		{
		case -1: // a < b
			ha = NextPos(Pa, ha);
			qa = NextPos(Pa, qa);
			break;

		case 0: // a == b
			sum = a.coef + b.coef;
			if (abs(sum) < 0.00001)
			{
				// a.coef + b.coef = 0
				// 清除Pa上的结点
				q = qa;
				qa = NextPos(Pa, qa);
				ha->next = qa;
				FreeNode(q);
			}
			else
			{
				// 修改Pa上该点的值
				term e = qa->data;
				e.coef = sum;
				SetCurElem(Pa, qa, e);
			}

			// 清除Pb上的结点
			q = qb;
			qb = NextPos(Pb, qb);
			hb->next = qb;
			FreeNode(q);

			break;

		case 1: // a > b
			// 让qb指针所指的结点在Pb上脱离，并保存在q中
			Link q = qb;
			qb = NextPos(Pb, qb);
			hb->next = qb;

			// 将q指针所指的结点链接到Pa上,qa所指的结点之前(即：ha所指的结点之后)
			ha->next = q;
			q->next = qa;
			break;
		}
	}

	if (qb != NULL)
		ha->next = qb;

	FreeNode(hb);
}

// 完成多项式相减运算，即：Pa = Pa - Pb，并销毁一元多项式Pb
void SubtractPolyn(polynomial &Pa, polynomial &Pb)
{

}

// 完成多项式相乘运算，即：Pa = Pa * Pb，并销毁一元多项式Pb
void MultiplyPolyn(polynomial &Pa, polynomial &Pb)
{}

// 依a的指数值<(或=)(或>)b的指数值，分别返回-1、0和+1
// PASS
int cmp(term a, term b)
{
	if (a.expn < b.expn)
		return -1;
	else if (a.expn == b.expn)
		return 0;
	else
		return 1;
}
