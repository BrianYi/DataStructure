#include "wordindex.h"

// 基本操作
// 算法 4.10
void InitIdxList(IdxListType &idxlist)
{

}

// 从文件f读入一个书目信息到书目串缓冲区buf
void GetLine(FILE f)
{

}

// 从buf中提取书名关键词到词表wdlist,书号存入bno
void ExtractKeyWord(ElemType &bno)
{

}

// 将书号为bno的书名关键词按词典顺序插入索引表idxlist
Status InsIdxList(IdxListType &idxlist, ElemType bno)
{

}

// 将生成的索引表idxlist输出到文件g
void PutText(FILE g, IdxListType idxlist)
{

}



// 用wd返回词表wdlist中第i个关键词
// 算法 4.11
void GetWord(int i, SString &wd)
{

}

// 在索引表idxlist中查询是否存在于wd相等的关键词。
// 若存在，则返回其在索引表中的位置，且b取值TRUE；否则返回插入位置，且b取值FALSE
// 算法 4.12
int Locate(IdxListType idxlist, SString wd, bool &b)
{

}

// 在索引表idxlist的第i项上插入新关键词wd,并初始化书号索引的链表为空表
// 算法 4.13
void InsertNewKey(IdxListType &idxlist, int i, SString wd)
{

}

// 在索引表idxlist的第i项中插入书号为bno的索引
// 算法 4.14
Status InsertBook(IdxListType &idxlist, int i, int bno)
{

}

// 算法 4.9
int main()
{


	return 0;
}
