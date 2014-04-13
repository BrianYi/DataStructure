#include "HuffmanTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 初始化数据和权值
void InitDataWeitgh(char *data, int *w) 
{
	for (int i = 1; i < MAX_SIZE; i++)
	{
		data[i] = NULL;
		w[i] = 0;
	}
}


// w存放n个字符的权值(均>0)，构造赫夫曼树HT,并求出n个字符的赫夫曼编码HC。
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) *sizeof(HTNode)); // 第一个空着不用
	
	// 初始化 1..n 赋上权值, n+1..m权值为0
	for (int i = 1; i <= m; i++)
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		if (i > n)
			HT[i].weight = 0;
		else
			HT[i].weight = w[i];
	}

	// 建造赫夫曼树
	int s1, s2;
	for (int i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	// 从叶子节点倒推出赫夫曼编码
	HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));
	char *cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = NULL;
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else if (HT[f].rchild == c)
				cd[--start] = '1';
		}

		int lenHC = (n - 1) - start; // 起始的start 减去 最终的 start,即为该编码的长度
		HC[i] = (char*)malloc((lenHC + 1)*sizeof(char)); // 最后一个位置放字符串结尾'\0'
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}

// 在HT[1..i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
void Select(HuffmanTree &HT, int n, int &s1, int &s2)
{
	unsigned int minValue1 = -1, minValue2 = -1; // 两者都取正整型中最大的数
	
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			if (minValue1 >= HT[i].weight)
			{
				if (minValue2 > minValue1)
				{
					s2 = s1;
					minValue2 = minValue1;
				}
				minValue1 = HT[i].weight;
				s1 = i;
			}
			else
			{
				if (minValue2 >= HT[i].weight)
				{
					minValue2 = HT[i].weight;
					s2 = i;
				}
			}
		}
	}
}

// 计算用户输入的字符串中的不同字符所含的个数(保存在data中)和权值(保存在w中)
void WeightComputing(char *data, char *String, int *w)
{
	int len = strlen(String) - 1;
	int i, j;
	for (i = 1; i <= len; i++)
	{
		for (j = 1; data[j]; j++)
		{
			if (data[j] == String[i])
			{
				w[j]++;
				break;
			}
		}
		if (data[j] == NULL)
		{
			data[j] = String[i];
			data[j + 1] = NULL;
			w[j] = 1;
		}
	}
}

// 将用户输入的字符串转换为对应的赫夫曼代码串(即->编码)
Status StringToHuffmanCode(char *data, char *String, HuffmanCode &HC, HuffmanCode &HcStr)
{
	int LenData = strlen(data) - 1;
	int LenStr = strlen(String) - 1;
	int LenHC = 0;
	HcStr = (HuffmanCode)malloc((LenStr + 1)*sizeof(char*)); // 存放字符串转换后的编码形式
	for (int i = 1; i <= LenStr; i++)
	{
		for (int j = 1; j <= LenData; j++)
		{
			if (data[j] == String[i])
			{
				LenHC = strlen(HC[j]);
				HcStr[i] = (char*)malloc((LenHC + 1)*sizeof(char));
				strcpy(HcStr[i], HC[j]);
			}
		}
	}
	return OK;
}

void OutputWeightHuffmanCode(char *data, int *w, HuffmanCode &HC) // 输出对应的数据、权值和赫夫曼编码
{
	int len = strlen(data) - 1;
	int width = 10;
	cout << "字符: ";
	for (int i = 1; i <= len; i++)
	{
		cout << setiosflags(ios::left) << setw(width) << data[i];
	}
	cout << endl;

	cout << "权重: ";
	for (int i = 1; i <= len; i++)
	{
		cout << setiosflags(ios::left) << setw(width) << w[i];
	}
	cout << endl;

	cout << "编码: ";
	for (int i = 1; i <= len; i++)
	{
		cout << setiosflags(ios::left) << setw(width) << HC[i];
	}
}

void OutputStrHuffmanCode(HuffmanCode &HcStr, int len) // 输出原串的编码串
{
	for (int i = 1; i <= len; i++)
	{
		cout << HcStr[i];
	}
}

// 将用户输入的赫夫曼代码串(HcStr)转换为对应的字符串(String)(即->译码)
Status HuffmanCodeToString(char *HcStr, HuffmanTree &HT, HuffmanCode &HC, char *data, char *String)
{
	int lenHcStr = strlen(HcStr) - 1;
	int lenData = strlen(data) - 1;
	int lenHC = lenData;
	int lenStr = 0;
	char *cd = (char*)malloc(lenData * sizeof(char));
	int m = 2 * lenData - 1;
	int p = m;
	int start = 1;
	for (int i = 1; i <= lenHcStr + 1; i++)
	{
		if (HcStr[i] == '0')
		{
			p = HT[p].lchild;
			if (p == 0)
			{
				cd[start] = NULL;
				String[++lenStr] = data[HuffmanCodeToChar(cd, HC, lenHC)];
				start = 1;
				i--;
				p = m;
			}
			else
				cd[start++] = '0';
		}
		else if (HcStr[i] == '1')
		{
			p = HT[p].rchild;
			if (p == 0)
			{
				cd[start] = NULL;
				String[++lenStr] = data[HuffmanCodeToChar(cd, HC, lenHC)];
				start = 1;
				i--;
				p = m;
			}
			else
				cd[start++] = '1';
		} 
		else if (HcStr[i] == NULL)
		{
			cd[start] = NULL;
			String[++lenStr] = data[HuffmanCodeToChar(cd, HC, lenHC)];
		}
	}

	String[++lenStr] = NULL;

	//free(cd);
	return OK;
}

int HuffmanCodeToChar(char *cd, HuffmanCode &HC, int lenHC) // 根据赫夫曼编码找到对应的字符下标
{
	for (int i = 1; i <= lenHC; i++)
	{
		if (strcmp(&cd[1],HC[i]) == 0)
			return i;
	}
	exit(0);
	return -1;
}

int main()
{
	
	char data[MAX_SIZE]; // 存放字符
	int w[MAX_SIZE]; // 存放与字符对应的权值
	char String[MAX_SIZE]; // 存放用户输入的字符
	char HcString[MAX_SIZE]; // 存放用户输入的赫夫曼编码
	InitDataWeitgh(data, w);

	cout << "请输入随意字符并按回车结束输入 :";
	
	int lenStr = 0;
	char ch = getchar();
	while (ch != '\n')
	{
		String[++lenStr] = ch;
		ch = getchar();
	}
	String[lenStr + 1] = NULL; // 字符串末尾值为0，表示字符串结束

	WeightComputing(data, String, w); // 计算权重，并将字符串中的字符归类统计

	/*计算生成赫夫曼树，并计算赫夫曼编码*/
	HuffmanTree HT;
	HuffmanCode HC;
	int lenData = strlen(data) - 1;
	HuffmanCoding(HT, HC, w, lenData); 
	
	/*输出字符的值、权重、编码*/
	HuffmanCode HcStr;
	int lenHcStr = lenStr;
	StringToHuffmanCode(data, String, HC, HcStr);
	OutputWeightHuffmanCode(data, w, HC);
	cout << endl;

	/*输出字符串转换为编码后的样子*/
	cout << "原串  : " << &String[1] << endl;
	cout << "编码串: ";
	OutputStrHuffmanCode(HcStr, lenHcStr);
	cout << endl;

	/*译码*/
	while (true)
	{
		cout << "请输入编码，按下回车后会将其译码: ";
		lenStr = 0;
		ch = getchar();
		while (ch != '\n')
		{
			HcString[++lenStr] = ch;
			ch = getchar();
		}
		HcString[lenStr + 1] = NULL; // 字符串末尾值为0，表示字符串结束
		HuffmanCodeToString(HcString, HT, HC, data, String);
		cout << &String[1] << endl;
	}
	delete HT;
	delete[] HC;
	delete[] HcStr;
	return 0;
}
