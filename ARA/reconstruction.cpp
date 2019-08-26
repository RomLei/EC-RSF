#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void reconstruction(vector<node> &rnode, vector<vector<int>> &G,vector<vector<int>> &Gbackup)
{
	int N = rnode.size();
	int pp = -1;
	vector<int> restnode;//存储剩余节点中被攻击损失了边的节点
	vector<int> attackednode;
	vector<int> backupattack;
	calculate_crruentdegree(rnode, Gbackup);
	for (int i = 0;i < N;i++)
	{
		if (rnode[i].activation == 1)
		{
			if (rnode[i].degree != rnode[i].crruentdegree)
			{
				restnode.push_back(i);
			}
		}
		else
		{
			attackednode.push_back(i);
		}
	}
	for (int i = 0, ii = restnode.size(),iii= restnode.size();i < ii;i++)//排序restnode
	{
		for (int u = 0;u < iii-1;u++)
		{
			if (rnode[restnode[u]].degree < rnode[restnode[u + 1]].degree)
			{
				swap(restnode.begin() + u, restnode.begin() + u + 1);
			}
		}
		iii--;
	}
	for (int i = restnode.size()-1;i >= 0;i--)//恢复被攻击牵连的点
	{
		while (rnode[restnode[i]].degree != rnode[restnode[i]].crruentdegree)
		{
			if ((restnode.size() != 1) && R_choosenode(restnode, restnode[i], pp, G))
			{
				G[restnode[i]][restnode[pp]] = 1;
				G[restnode[pp]][restnode[i]] = 1;
				rnode[restnode[i]].crruentdegree++;
				rnode[restnode[pp]].crruentdegree++;
			}
			else
			{
				pp = ((double)rand() / (RAND_MAX + 1))*attackednode.size();
				while (G[restnode[i]][attackednode[pp]] == 1)
				{
					pp = ((double)rand() / (RAND_MAX + 1))*attackednode.size();
				}
				G[restnode[i]][attackednode[pp]] = 1;
				G[attackednode[pp]][restnode[i]] = 1;
				rnode[restnode[i]].crruentdegree++;
				rnode[attackednode[pp]].crruentdegree++;
				if (rnode[attackednode[pp]].crruentdegree == rnode[attackednode[pp]].degree)
				{
					attackednode.erase(attackednode.begin() + pp);
				}
			}
		}
		restnode.erase(restnode.begin() + i);
	}
	for (int i = 0, ii = attackednode.size()-1;i < ii;i++)//恢复被攻击节点
	{
		backupattack = attackednode;
		backupattack.erase(backupattack.begin() + i);
		while ((rnode[attackednode[i]].degree != rnode[attackednode[i]].crruentdegree)||(backupattack.size()!=0))
		{
			pp = ((double)rand() / (RAND_MAX + 1))*backupattack.size();
			while (G[attackednode[i]][backupattack[pp]]==1)
			{
				backupattack.erase(backupattack.begin() + pp);
				if (backupattack.size() == 0)
				{
					break;
				}
				pp = ((double)rand() / (RAND_MAX + 1))*backupattack.size();
			}
			if (backupattack.size() == 0)
			{
				break;
			}
			G[attackednode[i]][backupattack[pp]] = 1;
			G[backupattack[pp]][attackednode[i]] = 1;
			rnode[attackednode[i]].crruentdegree++;
			rnode[backupattack[pp]].crruentdegree++;
			if (rnode[backupattack[pp]].crruentdegree == rnode[backupattack[pp]].degree)
			{
				attackednode.erase(attackednode.begin() + pp);
			}
		}
		attackednode.erase(attackednode.begin() + i);
	}
}


void calculate_crruentdegree(vector<node> &rnode, vector<vector<int>> &G)//计算当前的degree
{
	int N = rnode.size();
	for (int p = 0;p < N;p++)
	{
		rnode[p].crruentdegree = 0;
		for (int i = 0;i < N;i++)
		{
			if (G[p][i] == 1)
			{
				rnode[p].crruentdegree++;
			}
		}
	}
}

bool R_choosenode(vector<int> &restnode,int x, int &pp, vector<vector<int>> &G)//找到能与x点连接的点，在restnode中
{
	int N = restnode.size();
	int i = 0, u = 1;
	for (;i < N;i++)
	{
		if (G[x][restnode[i]] == 1)
		{
			u++;
		}
	}
	if (u = i)
	{
		return false;
	}
	pp = ((double)rand() / (RAND_MAX + 1))*restnode.size();
	while ((restnode[pp] == x)||(G[x][restnode[pp]]==1))
	{
		pp = ((double)rand() / (RAND_MAX + 1))*restnode.size();
	}
	return true;
}

bool R_choosenode2(vector<int> &attackednode, int x, int &pp, vector<vector<int>> &G)//找到能与x点连接的点，在attackednode中
{
	int N = attackednode.size();
	int i = 0, u = 1;
	for (;i < N;i++)
	{
		if (G[x][attackednode[i]] == 1)
		{
			u++;
		}
	}
	if (u = i)
	{
		return false;
	}
	pp = ((double)rand() / (RAND_MAX + 1))*attackednode.size();
	while ((attackednode[pp] == x) || (G[x][attackednode[pp]] == 1))
	{
		pp = ((double)rand() / (RAND_MAX + 1))*attackednode.size();
	}
	return true;
}