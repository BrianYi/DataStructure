#include "Stack3.h"
#include <iostream>
#include <conio.h>
using namespace std;

// 产生随机地图
bool gen_rand_map(int Map[][SIZE], PosType &startPoint, PosType &endPoint)
{
	for (int i = 0; i < SIZE; i++)
	{
		Map[0][i]		 = 1;
		Map[SIZE - 1][i] = 1;

		Map[i][0]		 = 1;
		Map[i][SIZE - 1] = 1;
	}

	int digt = 0;
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			digt = rand() % 3;
			if (digt == 0 ||
				digt == 1)
				Map[i][j] = 0;
			else
				Map[i][j] = 1;
		}
	}


	bool hasStartPoint = false;
	bool hasEndPoint = false;
	// 设置起点 
	for (int i = 1; i < SIZE - 1; i++)
	{
		if (Map[1][i] == 0)
		{
			startPoint.row = 1;
			startPoint.col = i;
			Map[1][i] = 3; ////
			hasStartPoint = true;
			break;
		}
	}

	// 设置终点
	for (int i = 1; i < SIZE - 1; i++)
	{
		if (Map[SIZE - 2][i] == 0)
		{
			endPoint.row = SIZE - 2;
			endPoint.col = i;
			Map[SIZE - 2][i] = -1;
			hasEndPoint = true;
			break;
		}
	}

	if (hasStartPoint && hasEndPoint)
		return true;
	else
		return false;
}

// 判断当前光标所指的位置是否可以通过(1:未走过，2:无障碍物)
bool isPass(int Map[][SIZE], PosType& cursor)
{
	if (Map[cursor.row][cursor.col] == 1 || Map[cursor.row][cursor.col] == 2)
		return false;
	return true;
}

// 留下足迹
void leaveClue(int Map[][SIZE], PosType& cursor)
{
	if (Map[cursor.row][cursor.col] != -1 && Map[cursor.row][cursor.col] != 3) // 不为起点、终点
		Map[cursor.row][cursor.col] = 2;
}

// 光标向下一个方位探索
void moveCursor(PosType& cursor, int di)
{
	switch (di)
	{
	case 1: // 东
		cursor.col++;
		break;
	case 2: // 南
		cursor.row++;
		break;
	case 3: // 西
		cursor.col--;
		break;
	case 4: // 北
		cursor.row--;
		break;
	default:
		cout << "moveCursor:ERROR!" << endl;
		break;
	}
}

// 判断是否可达，且返回可达路线
bool get_course(PosType startPoint, PosType endPoint, int Map[][SIZE], SqStack &S)
{
	PosType cursor = startPoint;

	do {
		if (isPass(Map, cursor))
		{
			leaveClue(Map, cursor);
			SElemType step;
			step.di = 1;
			step.seat = cursor;
			//step.ord
			Push(S, step);
			if (cursor.row == endPoint.row && cursor.col == endPoint.col)
				return true;
			moveCursor(cursor, 1);
		}
		else if (!StackEmpty(S))
		{
			SElemType manPos;
			Pop(S, manPos);
			while (manPos.di == 4 && !StackEmpty(S))
			{
				leaveClue(Map, manPos.seat);
				Pop(S, manPos);
			}
			if (manPos.di < 4)
			{
				manPos.di++; // 标记准备探究下一个方向
				Push(S, manPos); // 人物当前位置入栈
				cursor = manPos.seat; // 光标回归到人物当前的位置
				moveCursor(cursor, manPos.di); // 移动光标到标记的方向
			}
		}
	} while (!StackEmpty(S));

	return false;
}

// 显示地图
void show_map(int Map[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			switch (Map[i][j])
			{
			case -1:
				cout << "终";
				break;
			case 0:
			case 2:
				cout << "□";
				break;
			case 1:
				cout << "■";
				break;
			case 3:
				cout << "＊";
				break;
				// 
			case '1':
				cout << "→";
				break;
			case '2':
				cout << "↓";
				break;
			case '3':
				cout << "←";
				break;
			case '4':
				cout << "↑";
				break;
			default:
				cout << "show_map:ERROR!" << endl;
				break;
			}
		}
		cout << endl;
	}
}

void compute_course(SqStack &S, int Map[][SIZE], int Map2[][SIZE])
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			Map2[i][j] = Map[i][j];
		}
	}


	SElemType point;
	if (StackEmpty(S))
		return;
	else
		Pop(S, point); // 抛掉终点

	transfer(S); // 栈内元素颠倒

	Pop(S, point); // 抛掉起点

	while (!StackEmpty(S))
	{
		Pop(S, point);
		Map2[point.seat.row][point.seat.col] = point.di + '0'; // 方位转换为可以显示的箭头
	}
}
// 显示可达路线
void show_course(int Map2[][SIZE])
{
	show_map(Map2);
}

void maze_interface()
{
	cout << "*****************************************\n";
	cout << "*                                       *\n";
	cout << "*                                       *\n";
	cout << "*               迷宫游戏                *\n";
	cout << "*                                       *\n";
	cout << "*             1. 开始游戏               *\n";
	cout << "*             2. 游戏介绍               *\n";
	cout << "*             3. 退出游戏               *\n";
	cout << "*                                       *\n";
	cout << "*                                       *\n";
	cout << "*****************************************\n";
}

void maze_info()
{

}

void maze_begin(int Map[][SIZE], SqStack &S)
{
	PosType startPoint, endPoint;
	// 生成有起点且有终点的地图 且 判断是否可达
	while (!gen_rand_map(Map, startPoint, endPoint) || 
		!get_course(startPoint, endPoint, Map, S));

	PosType manPos = startPoint; // 人物初始位置
	
	int(*Map2)[SIZE] = new int[SIZE][SIZE]; // 地图副本：用来存储地图解法
	compute_course(S, Map, Map2);  // 生成地图解法

	bool isWin = false; // 人物是否走出迷宫
	while (!isWin)
	{
		system("CLS");
		show_map(Map);
		cout << "友情提示:要看迷宫解法请按下z键!" << endl;
		char choice = _getch();
		switch (choice)
		{
		case 'w':
		case 'W':
			if (Map[manPos.row - 1][manPos.col] != 1)
			{
				Map[manPos.row][manPos.col] = 0;
				manPos.row--;
				Map[manPos.row][manPos.col] = 3;
			}
			break;
		case 's':
		case 'S':
			if (Map[manPos.row + 1][manPos.col] != 1)
			{
				Map[manPos.row][manPos.col] = 0;
				manPos.row++;
				Map[manPos.row][manPos.col] = 3;
			}
			break;
		case 'a':
		case 'A':
			if (Map[manPos.row][manPos.col - 1] != 1)
			{
				Map[manPos.row][manPos.col] = 0;
				manPos.col--;
				Map[manPos.row][manPos.col] = 3;
			}
			break;
		case 'd':
		case 'D':
			if (Map[manPos.row][manPos.col + 1] != 1)
			{
				Map[manPos.row][manPos.col] = 0;
				manPos.col++;
				Map[manPos.row][manPos.col] = 3;
			}
			break;
		case 'z':
		case 'Z':
			show_course(Map2);
			_getch();
			break;
		default:
			cout << "输入有误!" << endl;
			break;
		}

		if (manPos.row == endPoint.row && manPos.col == endPoint.col) // 当前位置为终点
			isWin = true;
	}

	delete[] Map2;


}

void maze_exit(int Map[][SIZE])
{
	delete[]Map;
}

int main()
{
	int(*Map)[SIZE] = new int[SIZE][SIZE];
	SqStack S;

	while (true) 
	{
		InitStack(S);
		system("CLS");
		maze_interface();
		char choice = _getch();
		switch (choice)
		{
		case '1':
			maze_begin(Map, S);
			break;
		case '2':
			maze_info();
			break;
		case '3':
			maze_exit(Map);
			break;
		default:
			cout << "输入无效!!!" << endl;
			break;
		}
	}
	return 0;
}
