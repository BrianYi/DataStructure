#include <iostream>
#include "Stack4.h"
using namespace std;

bool In(SElemType c, SElemType OP[])
{
	SElemType *p = OP;
	while (*p && *p++ != c);
	if (*(p - 1) == c)
		return true;
	return false;
}

SElemType Preecede(SElemType op1, SElemType op2)
{
	switch (op1)
	{
	case '+':
	case '-':
		switch (op2)
		{
		case '+':
		case '-':
		case ')':
		case '#':
			return '>';
			break;
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		}
	case '*':
	case '/':
		switch (op2)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		case '(':
			return '<';
			break;
		}
	case '(':
		switch (op2)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case ')':
			return '=';
			break;
		case '#':
			cout << "ERROR!";
			exit(0);
			break;
		}
	case ')':
		switch (op2)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			return '>';
			break;
		case '(':
			cout << "ERROR!";
			exit(0);
			break;
		case ')':
		case '#':
			return '>';
			break;
		}
	case '#':
		switch (op2)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case ')':
			cout << "ERROR!";
			exit(0);
			break;
		case '#':
			return '=';
			break;
		}
	}
}

SElemType Operate(SElemType a, SElemType theta, SElemType b)
{
	switch (theta)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	default:
		break;
	}
}

SElemType EvaluateExpression()
{
	SElemType *OP = new SElemType[20];
	int i = 0;
	OP[i++] = '+';
	OP[i++] = '-';
	OP[i++] = '*';
	OP[i++] = '/';
	OP[i++] = '(';
	OP[i++] = ')';
	OP[i++] = '#';
	OP[i] = NULL;

	SqStack OPTR, OPND;
	InitStack(OPTR);
	InitStack(OPND);

	Push(OPTR, '#');
	SElemType c = getchar();
	SElemType a, b, theta;
	while (c != '#' || GetTop(OPTR) != '#')
	{
		if (!In(c, OP))
		{
			c -= '0';
			Push(OPND, c);
			c = getchar();
		}
		else
		{
			switch (Preecede(GetTop(OPTR), c))
			{
			case '<':
				Push(OPTR, c);
				c = getchar();
				break;
			case '=':
				Pop(OPTR, c);
				c = getchar();
				break;
			case '>':
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			default:
				break;
			}
		}
	}

	delete[] OP;

	return GetTop(OPND);
}

int main()
{
	while (true)
		cout << "结果为: " << EvaluateExpression() << endl;
	return 0;
}
