#include "triple.h"
#include <iostream>
using namespace std;

// 算法 5.1
Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	int q = 1;
	if (T.tu) {
		for (int col = 1; col <= M.nu; ++col)
		{
			for (int p = 1; p <= M.tu; ++p)
			{
				if (M.data[p].j == col)
				{
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					++q;
				}
			}
		}
	}

	computeRpos(T);

	return OK;
}

// 算法 5.2
Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu; 
	T.nu = M.mu;
	T.tu = M.tu;
	int *num = new int[T.tu * sizeof(int) + 1];
	int *cpot = new int[T.tu * sizeof(int) + 1];
	int col;
	if (T.tu != 0)
	{
		for (col = 1; col <= M.tu; col++) // M上每列的非零元的数目初始化
			num[col] = 0;

		for (int t = 1; t <= M.tu; t++) // 存储M上每列的非零元的数目
			++num[M.data[t].j];

		cpot[1] = 1; 

		for (col = 2; col <= M.nu; col++)
			cpot[col] = cpot[col - 1] + num[col - 1]; // N上第col行第一个非零元的下标

		for (int q, p = 1; p <= M.tu; p++)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j; // 列变行
			T.data[q].j = M.data[p].i; // 行变列
			T.data[q].e = M.data[p].e; // 赋值
			++cpot[col]; //  
		}
	}

	delete [] num;
	delete [] cpot;

	computeRpos(T);

	return OK;
}

// 算法 5.3
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
	if (M.nu != N.mu)
		return ERROR;
	Q.mu = M.mu;
	Q.nu = N.nu;
	Q.tu = 0;
	if (M.tu * N.tu != 0)
	{
		// 
		int *ctemp = new int[N.nu + 1];
		int tp, t, brow, ccol;
		Triple tr;
		for (int arow = 1; arow <= M.mu; arow++)
		{
			for (int i = 1; i <= N.nu; i++)
				ctemp[i] = 0;

			Q.rpos[arow] = Q.tu + 1;
			if (arow < M.mu)
				tp = M.rpos[arow + 1];
			else
				tp = M.tu + 1;
			
			for (int p = M.rpos[arow]; p < tp; p++)
			{
				brow = M.data[p].j;
				if (brow < N.mu)
					t = N.rpos[brow + 1];
				else
					t = N.tu + 1;

				for (int q = N.rpos[brow]; q < t; q++)
				{
					ccol = N.data[q].j;
					ctemp[ccol] += M.data[p].e * N.data[q].e;
				}
			}

			for (ccol = 1; ccol <= Q.nu; ccol++)
			{
				if (ctemp[ccol]) {
					if (++Q.tu > MAXSIZE)
						return ERROR;
					tr.i = arow;
					tr.j = ccol;
					tr.e = ctemp[ccol];
					Q.data[Q.tu] = tr;
				}
			}
		}

		delete[] ctemp;

		computeRpos(Q);
	}
	return OK;
}

// 计算Rpos 可能有点小问题（希望大家能够帮我找出来，并给我留言告诉我怎么改正，谢谢！*^_^*）
Status computeRpos(TSMatrix& M)
{
	int p = 1, row = 1;
	for (; p <= M.tu;)
	{
		if (M.data[p].i == row)
		{
			if (M.rpos[row] != p)
				M.rpos[row] = p;
			
			while (M.data[++p].i == row); // 到下一行的第一个非零元
			row++;
		}
		else if (M.data[p].i > row)
		{
			while (row <= M.data[p].i)
			{
				M.rpos[row] = p;
				row++;
			}
		}
		else 
			while (M.data[++p].i == row);
	}

	while (row <= M.mu)
	{
		M.rpos[row++] = p;
	}

	return OK;
}

// 将二维数组转化成矩阵
Status AssignMatrix(int **matrix, int row, int col, TSMatrix &M)
{
	M.mu = row;
	M.nu = col;
	M.tu = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (matrix[i][j] != 0)
			{
				M.data[++M.tu].i = i + 1;
				M.data[M.tu].j = j + 1;
				M.data[M.tu].e = matrix[i][j];
			}
		}
	}

	computeRpos(M);

	return OK;
}

// 显示矩阵
void display_matrix(TSMatrix &M)
{
	int p = 1;
	for (int i = 1; i <= M.mu; i++)
	{
		for (int j = 1; j <= M.nu; j++)
		{
			if (M.data[p].i == i && M.data[p].j == j)
			{
				cout << M.data[p].e << "\t";
				p++;
			}
			else
				cout << "0\t";
			if (j == M.nu)
				cout << endl;
		}
	}
}

int main()
{
	int m, n;
	cout << "--Please enter the row and column of Matrix that you need--" << endl;
	cout << "row :"; cin >> m;
	cout << "column :"; cin >> n;
	cout << "Now you need just type some digits which size is related to your typed in just now, "
		<< "and must eligible to form a matrix." << endl;
	int **p = new int*[m];
	for (int i = 0; i < m; i++)
		p[i] = new int[n];
	
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> p[i][j];
	}
	TSMatrix M, T, N, Q;
	AssignMatrix(p, m, n, M);

	cout << endl;
	cout << "Matrix M :" << endl;
	display_matrix(M);
	cout << endl;

	cout << "Transpose M -> T, Matrix T :" << endl;
	TransposeSMatrix(M, T);
	display_matrix(T);
	cout << endl;

	cout << "FastTranspose T -> N, Matrix N :" << endl;
	FastTransposeSMatrix(T, N);
	display_matrix(N);
	cout << endl;

	cout << "MultSMatrix M * T -> Q, Matrix Q :" << endl;
	MultSMatrix(M, T, Q);
	display_matrix(Q);
	cout << endl;

	for (int i = 0; i < m; i++)
	{
		delete p[i];
	}
	delete p;

	return 0;
}
