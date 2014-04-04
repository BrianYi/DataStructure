#pragma once
#include "Stack3.h"
bool Pass(PosType curpos, int Map[][SIZE]);
void FootPrint(PosType curpos, int Map[][SIZE]);
PosType NextPos(PosType pos, int di);
Status MazePath(PosType start, PosType end, int Map[][SIZE], SqStack &S);
Status display_path(SElemType e);
void display_maze(int [][SIZE]);
