#include <iostream>
#include "Stack2.h"
using namespace std;


// 算法 3.1
void conversion()
{
	SqStack stack;
	InitStack(stack);
	SElemType e;
	cin >> e;
	while (e)
	{
		Push(stack, e % 8);
		e /= 8;
	}

	while (!StackEmpty(stack))
	{
		Pop(stack, e);
		cout << e;
	}
	cout << endl;

}

// 括号匹配
// PASS
bool bracketMach()
{
	SqStack OptLeft;
	InitStack(OptLeft);

	SElemType e;
	bool ismatch = true;
	while (cin >> e && e != '#')
	{
		if (e == '{' || e == '[' || e == '(')
			Push(OptLeft, e);
		else
		{
			if (StackEmpty(OptLeft))
				ismatch = FALSE;

			SElemType topElem;
			Pop(OptLeft, topElem);
			if (topElem == '{' && e != '}')
				ismatch = FALSE;
			else if (topElem == '[' && e != ']')
				ismatch = FALSE;
			else if (topElem == '(' && e != ')')
				ismatch = FALSE;
		}
	}

	DestroyStack(OptLeft);
	return ismatch;
}



// 算法 3.2
void LineEdit(SqStack &S, Status(*visit)(SElemType&))
{
	InitStack(S);
	SElemType ch = getchar();
	while (ch != EOF)
	{
		while (ch != EOF && ch != '\n')
		{
			switch (ch)
			{
			case '#':
				Pop(S, ch);
				break;
			case '@':
				ClearStack(S);
				break;
			default:
				Push(S, ch);
				break;
			}
			ch = getchar();
		}

		transfer(S);

		while (!StackEmpty(S))
		{
			Pop(S, ch);
			visit(ch);
		}
		cout << endl;

		ClearStack(S);
		if (ch != EOF)
			ch = getchar();
	}

	DestroyStack(S);
}

int main()
{
	while (true)
	{
		//conversion();

		/*bool isMatch = bracketMach();
		if (isMatch)
		cout << "匹配成功!" << endl;
		else
		cout << "匹配失败!" << endl;*/

		SqStack stack;
		LineEdit(stack, visit);
	}

	return 0;
}
