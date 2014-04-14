#include "Queen.h"
#include <iostream>
using namespace std;

// 判断该布局是否合法
bool IsPass(Chessboard &CB, Chesspiece &CP, int n)
{
	int i, j;
	float div;
	for (i = 1; i <= n; i++)
	{
		// ①任何两个棋子不占据棋盘上同一行、同一列(行不需要判断了，已经确保每行只有1个棋子了)
		if (CP.col == CB[i].col)
			return false;
		else { 
			// ②不占同一对角线，即 斜率为1或-1
			div = float(CP.row - CB[i].row) / (CP.col - CB[i].col);
			if (div == 1 || div == -1) 
				return false;
		}
	}
	return true;
}

// 输出棋盘
void OutputChessboard(Chessboard &CB, int n)
{
	int i, j;
	Count++;
	cout << "第 " << Count << " 种:" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (CB[Beg].row == i && CB[Beg].col == j && Beg != End)
			{
				cout << "■";
				Beg++; // 指向下一个元素
			}
			else
				cout << "□";
		}
		cout << endl;
	}
	cout << endl;
	Beg = 1; // 指向第一个元素
}

// 试探
void Trial(Chessboard &CB, int i, int n)
{
	if (i > n)
		OutputChessboard(CB, n);
	else {
		Chesspiece CP; // 一粒棋子
		for (int j = 1; j <= n; j++)
		{
			CP.row = i; // 棋子 行初始化
			CP.col = j; // 棋子 列初始化
			CB[End++] = CP; // 放入棋子，插入线性表最后一个
			if (IsPass(CB, CP, i-1)) // 检查[1..i-1]行的棋子与当前的第i行j列的棋子CP是否能够构成一个合法的棋盘
			{
				Trial(CB, i + 1, n);
			}
			End--; // 将最后一个元素删除
		}
	}
}


int main()
{
	int n;
	while (true)
	{
		Count = 0;
		cout << "N皇后?!!!(N>0)" << endl;
		cout << "请输入N值: "; 
		cin >> n;
		Chessboard CB = new Chesspiece[n + 1]; // 第一个不用
		Trial(CB, 1, n);
		delete CB;
	}
	return 0;
}
