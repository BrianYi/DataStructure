#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;
int Beg = 1, End = 1; // 线性表的起点和终点
int Count = 0; // 解法计数

typedef struct {
	int row, col;
}*Chessboard, Chesspiece;

bool IsPass(Chessboard &CB, Chesspiece &CP, int n); // 判断该布局是否合法
void OutputChessboard(Chessboard &CB, int n); // 输出棋盘
void Trial(Chessboard &CB, int i, int n); // 试探
