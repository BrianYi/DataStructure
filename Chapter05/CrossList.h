#pragma once


#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int Status;
typedef int	ElemType;

typedef struct OLNode {
	int			i, j;
	ElemType	e;
	struct OLNode *right, *down;
}OLNode, *OLink;

typedef struct {
	OLink *rhead, *chead;
	int		mu, nu, tu;
}CrossList;

void initCrossList(CrossList &M);
void displayCrossList(CrossList &M);
void DestroyCrossList(CrossList &M);
Status CreateSMatrix_OL(CrossList &M);
void CrossListAddition();
