#pragma once
#include "SString.h"
#include "LinkList.h"

#define MaxBookNum	1000
#define MaxKeyNum	2500
#define MaxLineLen	500
#define MaxWordNum	10

typedef struct {
	char **item;
	int last;
}WordListType;

typedef int ElemType;
typedef struct {
	SString key;
	LinkList bnolist;
}IdxTermType;
typedef struct {
	IdxTermType item[MaxKeyNum + 1];
	int			last;
}IdxListType;


char *buf;
WordListType wdlist;

void InitIdxList(IdxListType &idxlist);  // 基本操作
void GetLine(FILE f); // 从文件f读入一个书目信息到书目串缓冲区buf
void ExtractKeyWord(ElemType &bno); // 从buf中提取书名关键词到词表wdlist,书号存入bno
Status InsIdxList(IdxListType &idxlist, ElemType bno); // 将书号为bno的书名关键词按词典顺序插入索引表idxlist
void PutText(FILE g, IdxListType idxlist); // 将生成的索引表idxlist输出到文件g

void GetWord(int i, SString &wd); // 用wd返回词表wdlist中第i个关键词
// 在索引表idxlist中查询是否存在于wd相等的关键词。
//若存在，则返回其在索引表中的位置，且b取值TRUE；否则返回插入位置，且b取值FALSE
int Locate(IdxListType idxlist, SString wd, bool &b); 
void InsertNewKey(IdxListType &idxlist, int i, SString wd); // 在索引表idxlist的第i项上插入新关键词wd,并初始化书号索引的链表为空表
Status InsertBook(IdxListType &idxlist, int i, int bno); // 在索引表idxlist的第i项中插入书号为bno的索引
