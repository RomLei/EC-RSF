#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include"ARA.h"
using namespace std;

int findslope(vector<node> &rnode, vector<vector<int>> &G)//找到最大连接簇下降最快的地方
{
	int N = rnode.size();
	int Maxdegreep;
	int mid, Gsize = N;
	int maxdeclinevaluep=0, declinevalue = N,ttt=0;
	vector<vector<int>> G2;//创建用于被攻击的邻接图
	G2.resize(N, vector<int>(N, 0));
	copynet(G, G2);
	for (int i = 0;i < N - 1;i++)
	{
		Maxdegreep = MaxDegreePosition(rnode);
		DeleteNode(rnode, Maxdegreep, G2);
		mid = MaxConnectedCluster(rnode, G2);
		if ((declinevalue - mid) > ttt)
		{
			ttt = declinevalue - mid;
			maxdeclinevaluep = i;
		}
		declinevalue = mid;
	}
	for (int i = 0;i < N;i++)//将点的状态全部还原
	{
		rnode[i].activation = 1;
	}
	calculate_degree(rnode, G);
	if (maxdeclinevaluep == 0)
	{
		maxdeclinevaluep++;
	}
	return maxdeclinevaluep;
}