#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void output_compute_image(vector<node> &rnode, vector<vector<int>> &G)//创建被攻击网络每次剩余最大连接簇的数量，保存到ARA.txt中
{
	FILE *result;
	result = fopen("ARA.txt", "wt");
	int N = rnode.size();
	int Maxdegreep;
	double largest = 0;
	int mid;
	vector<vector<int>> G2;//创建用于被攻击的邻接图
	G2.resize(N, vector<int>(N, 0));
	copynet(G, G2);
	for (int i = 0;i < N - 1;i++)
	{
		Maxdegreep = MaxDegreePosition(rnode);
		DeleteNode(rnode, Maxdegreep, G2);
		mid = MaxConnectedCluster(rnode, G2);
		fprintf(result, "%d\t", i);
		fprintf(result, "%d\n", mid);
	}
	for (int i = 0;i < N;i++)//将点的状态全部还原
	{
		rnode[i].activation = 1;
	}
	calculate_degree(rnode, G);
}