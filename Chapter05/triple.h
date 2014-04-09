#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define MAXSIZE 1250
#define MAXRC	1250
typedef int ElemType;

typedef struct {
	int		 i, j;
	ElemType e;
}Triple;
typedef struct {
	Triple	data[MAXSIZE + 1];
	int		rpos[MAXRC + 1];
	int		mu, nu, tu;
}TSMatrix;


Status TransposeSMatrix(TSMatrix M, TSMatrix &T);
Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T);
Status computeRpos(TSMatrix& M);
Status AssignMatrix(int **matrix, int row, int col, TSMatrix &M);
void display_matrix(TSMatrix &M);
