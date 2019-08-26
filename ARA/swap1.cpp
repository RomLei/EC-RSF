#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include"ARA.h"
using namespace std;

void swap1(vector<vector<int>> &G)//随机交换两条边
{
	int node1, node11, node2, node21;
	bool suc = true,suc2=true;
	vector<int> node1neibor;
	vector<int> node2neibor;
	node1 = ((double)rand() / (RAND_MAX + 1))*G.size();//定位第一个节点
	for (int i=0;i < G.size();i++)//找到第一个节点的邻居
	{
		if (G[node1][i] == 1)
		{
			node1neibor.push_back(i);
		}
	}
	node11 = node1neibor[((double)rand() / (RAND_MAX + 1))*node1neibor.size()];//定位与第一个节点相连的节点
	while (suc2)
	{
		suc = true;
		suc2 = false;
		node2neibor.clear();
		while (suc)//定位第二个节点
		{
			suc = false;
			node2 = ((double)rand() / (double)(RAND_MAX + 1))*G.size();
			if ((node2 == node1) || (node2 == node11)||(G[node2][node11]==1))
			{
				suc = true;
			}
		}
		for (int i=0;i < G.size();i++)//找到第二个节点的邻居
		{
			if (G[node2][i] == 1)
			{
				node2neibor.push_back(i);
			}
		}
		node21 = node2neibor[((double)rand() / (double)(RAND_MAX + 1))*node2neibor.size()];//定位与第一个节点相连的节点
		if ((node21 == node1) || (node21 == node11) || (G[node21][node1] == 1))
		{
			suc2 = true;
		}
	}
	G[node1][node11] = 0;
	G[node11][node1] = 0;
	G[node2][node21] = 0;
	G[node21][node2] = 0;
	G[node1][node21] = 1;
	G[node21][node1] = 1;
	G[node2][node11] = 1;
	G[node11][node2] = 1;

}
