#pragma once

#include "BinaryTree.h"
#include "typedefine.h"

/* 二叉排序树 */
// 查找
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p);

// 插入
Status InsertBST(BiTree &T, SElemType e);

// 删除
Status DeleteBST(BiTree &T, KeyType key);

// 删除(子函数)
Status Delete(BiTree &p);
