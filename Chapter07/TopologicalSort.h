#pragma once

#include "Stack.h"
#include "Graph.h"


Status TopologicalSort(ALGraph &AL); // 拓扑排序
void FindInDegree(ALGraph &AL); // 初始化入度数据到indegree中
