#pragma once

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

#define MAX_SIZE 1000

typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

#define _CRT_SECURE_NO_WARNINGS

// 初始化数据和权值
void InitDataWeitgh(char *data, int *w);

// w存放n个字符的权值(均>0)，构造赫夫曼树HT,并求出n个字符的赫夫曼编码HC。
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n); 

// 在HT[1..i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
void Select(HuffmanTree &HT, int n, int &s1, int &s2);

// 计算用户输入的字符串中的不同字符所含的个数(保存在data中)和权值(保存在w中)
void WeightComputing(char *data, char *String, int *w);

// 将用户输入的字符串转换为对应的赫夫曼代码串(即->编码)
Status StringToHuffmanCode(char *data, char *String, HuffmanCode &HC, HuffmanCode &HcStr);

// 输出对应的数据、权值和赫夫曼编码
void OutputWeightHuffmanCode(char *data, int *w, HuffmanCode &HC); 

// 输出原串的编码串
void OutputStrHuffmanCode(HuffmanCode &HcStr, int len); 

// 将用户输入的赫夫曼代码串(HcStr)转换为对应的字符串(String)(即->译码)
Status HuffmanCodeToString(char *HcStr, HuffmanTree &HT, HuffmanCode &HC, char *data, char *String);

// 根据赫夫曼编码找到对应的字符下标
int HuffmanCodeToChar(char *cd, HuffmanCode &HC, int lenHC);
