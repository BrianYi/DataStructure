#pragma once
#include "LinkList2.h"

typedef LinkList polynomial;

void CreatPolyn(polynomial &P, int m);  // 输入m想的系数和指数，建立表示一元多项式的有序链表P
void DestroyPoly(polynomial &P); // 销毁一元多项式P
void PrintPoly(polynomial P); // 打印输出一元多项式P
int PolynLength(polynomial P); // 返回一元多项式P中的项数
void AddPolyn(polynomial &Pa, polynomial &Pb); // 完成多项式相加运算，即：Pa = Pa + Pb，并销毁一元多项式Pb
void SubtractPolyn(polynomial &Pa, polynomial &Pb); // 完成多项式相减运算，即：Pa = Pa - Pb，并销毁一元多项式Pb
void MultiplyPolyn(polynomial &Pa, polynomial &Pb); // 完成多项式相乘运算，即：Pa = Pa * Pb，并销毁一元多项式Pb
int cmp(term a, term b); // 依a的指数值<(或=)(或>)b的指数值，分别返回-1、0和+1

