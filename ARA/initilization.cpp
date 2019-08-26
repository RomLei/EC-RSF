#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;

/*void initilizationBA(vector<node> &rnode,vector<vector<int>> &G)
{
	int N = rnode.size();
	int sum = 0;
	double pp = 0;
	double ppi = 0;
	int u = 0, tt = 0, xx[2], c = 0;
	rnode[0].position[0] = ((double)rand() / RAND_MAX)*N;//初始化最开始两个节点的位置
	rnode[0].position[1] = ((double)rand() / RAND_MAX)*N;
	rnode[0].activation = 1;//激活
	rnode[1].position[0] = ((double)rand() / RAND_MAX)*N;
	rnode[1].position[1] = ((double)rand() / RAND_MAX)*N;
	rnode[0].activation = 1;
	rnode[2].position[0] = ((double)rand() / RAND_MAX)*N;
	rnode[2].position[1] = ((double)rand() / RAND_MAX)*N;
	rnode[2].activation = 1;
	G[0][1] = 1;G[1][0] = 1;
	G[0][2] = 1;G[2][0] = 1;
	G[1][2] = 1;G[2][1] = 1;
	rnode[2].degree = 2;
	rnode[0].degree = 2;
	rnode[1].degree = 2;
	for (int i = 3;i < N;i++)//开始将剩下的节点加入网络
	{
		rnode[i].position[0] = ((double)rand() / RAND_MAX)*N;
		rnode[i].position[1] = ((double)rand() / RAND_MAX)*N;
		rnode[i].activation = 1;
		sum = 0;
		for (int k = 0;k < i;k++)
		{
			sum = sum + rnode[k].degree;
		}
		while (rnode[i].degree == 0)
		{
			ppi = 0;
			u = 0, tt = 0;
			pp = (double)rand() / (RAND_MAX + 1);
			while (tt != 2)//开始建立节点,每个节点只连接两个节点
			{
				if ((pp - ppi) <= ((double)rnode[u].degree / sum))//若小于概率则连接
				{
					if (G[i][u] != 1)//若随机到的没有被选过则选上
					{
						G[i][u] = 1;G[u][i] = 1;
						rnode[u].degree++;
						rnode[i].degree++;
						tt++;
						pp = (double)rand() / (RAND_MAX + 1);
						u = -1;
						sum = 0;
						for (int k = 0;k < i;k++)
						{
								sum = sum + rnode[k].degree;
						}
					}
					else//若随机选择的点被选择过则重新选
					{
						pp = (double)rand() / (RAND_MAX + 1);
						u = -1;
					}
				}
				if (u == -1)
				{
					u = 0;
					ppi = 0;
				}
				else
				{
					ppi = ppi + ((double)rnode[u].degree / sum);
					u++;
				}

			}
		}
	}

}*/

void backupnet(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup)//备份网络
{
	int N = rnode.size();
	for (int i = 0;i < N;i++)
	{
		rnode[i].degreebackup = rnode[i].degree;
		for (int u = 0;u < N;u++)
		{
			Gbackup[i][u] = G[i][u];
		}
	}
}

void initilizationBA(vector<node> &rnode, vector<vector<int>> &G)
{
	int degree_ALL=0;
	double pp = 0, ppi = 0;
	G[0][1] = 1;G[1][0] = 1;
	G[2][0] = 1;G[0][2] = 1;
	G[2][1] = 1;G[1][2] = 1;
	rnode[0].degree = 2;
	rnode[1].degree = 2;
	rnode[2].degree = 2;
	for (int i = 3, k = 0, j = 0;i < rnode.size();i++)
	{
		k = 0;j = 0;
		ppi = 0;
		degree_ALL = 0;
		for (int u = 0;u < i;u++)
		{
			degree_ALL += rnode[u].degree;
		}
		pp = (double)rand() / RAND_MAX;
		while (rnode[i].degree < 1)
		{
			if ((pp - ppi) <= (double)rnode[k].degree / degree_ALL)
			{
				G[i][k] = 1;G[k][i] = 1;
				rnode[i].degree++;
				rnode[k].degree++;
			}
			else
			{
				ppi += (double)rnode[k].degree/degree_ALL;
				k++;
			}
		}
		degree_ALL = 0;
		for (int u = 0;u < i;u++)
		{
			if (u != k)
			{
				degree_ALL += rnode[u].degree;
			}
		}
		pp = (double)rand() / RAND_MAX;
		ppi = 0;
		if (k == 0)
		{
			j++;
		}
		while (rnode[i].degree < 2)
		{
			if ((pp - ppi) <= (double)rnode[j].degree / degree_ALL)
			{
				if (G[i][j] == 1)
				{
					pp = (double)rand() / RAND_MAX;
					ppi = 0;
					j = 0;
				}
				else
				{
					G[i][j] = 1;G[j][i] = 1;
					rnode[i].degree++;
					rnode[j].degree++;
				}
			}
			else
			{
				ppi += (double)rnode[j].degree/degree_ALL;
				j++;
				if (j == k)
				{
					j++;
				}
			}
		}
	}
	rebuildnode(rnode);
}