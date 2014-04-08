#include "array.h"
#include <iostream>
using namespace std;


// 若维数dim和随后的各维长度合法，则构造相应的数组A,并返回OK
Status InitArray(Array& A, int dim, ...)
{
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int)); // 存放每一维的长度
	if (!A.bounds)
		exit(OVERFLOW);
	
	int elemtotal = 1;
	va_start(ap, dim);
	for (int i = 0; i < dim; i++)
	{
		A.bounds[i] = va_arg(ap, int); // 存放每一维的长度
		if (A.bounds[i] < 0)
			return UNDERFLOW;
		elemtotal *= A.bounds[i]; // 存放将n维数组化成一维数组后的一维数组的长度
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base)
		exit(OVERFLOW);
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants)
		exit(OVERFLOW);
	A.constants[dim - 1] = 1; 
	for (int i = dim - 2; i >= 0; i--)
		/*存放每一维的基本单位 比如 A[3][4][2][5] 
		 对于第四维: [5] 基本单位为1, 所以 = 1
		 对于第三维: [2] 基本单位为[5], 所以 = 5 * 1
		 对于第二维: [4] 基本单位为[2][5]，所以 = 2 * 5 * 1
		 对于第一维: [3] 基本单位为[4][2][5]，所以 = 4 * 2 * 5 * 1
		*/
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];  // 存放每一维的基本单位
	
	return OK;
}

// 销毁数组A
Status DestroyArray(Array& A)
{
	if (!A.base)
		return ERROR;
	free(A.base);
	A.base = NULL;

	if (!A.bounds)
		return ERROR;
	free(A.bounds);
	A.bounds = NULL;

	if (!A.constants)
		return ERROR;
	free(A.constants);
	A.constants = NULL;
}

// 若ap指示的各下标值合法，则求出该元素在A中相对地址off
Status Locate(Array A, va_list ap, int& off)
{
	off = 0;
	int index = 0;
	for (int i = 0; i < A.dim; i++)
	{
		index = va_arg(ap, int);
		if (index < 0 || index >= A.bounds[i])
			return OVERFLOW;
		off += A.constants[i] * index; // 求出元素相对于最起始的位置的偏移量
	}

	return OK;
}

// A是n维数组，e为元素变量，随后是n个下标值。 若各下标不超界，则e赋值为所指定的A的元素值，并返回OK。
Status Value(Array A, ElemType &e, ...)
{
	int off;
	va_start(ap, e);
	int result = Locate(A, ap, off);
	if (result <= 0)
		return result;
	e = *(A.base + off); 
	return OK;
}

// A是n维数组，e为元素变量，随后是n个小标值。若下标不超界，则将e的值赋给所指定的A的元素，并返回OK。
Status Assign(Array& A, ElemType e, ...)
{
	va_start(ap, e);
        int off;
	int result = Locate(A, ap, off);
	if (result <= 0)
		return result;
	*(A.base + off) = e;
	return OK;
}
