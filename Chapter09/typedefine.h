#pragma

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;

typedef int KeyType; // 整型
typedef struct {
	KeyType key;
}SElemType;

#define		EQ(a ,b)	((a) == (b))
#define		LT(a, b)	((a) <  (b))
#define		LQ(a, b)	((a) <= (b))
