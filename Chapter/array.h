#pragma once
#include <stdarg.h>

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

#define MAX_ARRAY_DIM 8
typedef int ElemType;
typedef struct
{
	ElemType	*base;
	int			dim;
	int			*bounds;
	int			*constants;
}Array;

va_list ap;

Status InitArray(Array& A, int dim, ...); // 若维数dim和随后的各维长度合法，则构造相应的数组A,并返回OK
Status DestroyArray(Array& A); // 销毁数组A
Status Value(Array A, ElemType &e, ...); // A是n维数组，e为元素变量，随后是n个下标值。 若各下标不超界，则e赋值为所指定的A的元素值，并返回OK。
Status Assign(Array& A, ElemType e, ...); // A是n维数组，e为元素变量，随后是n个小标值。若下标不超界，则将e的值赋给所指定的A的元素，并返回OK。
