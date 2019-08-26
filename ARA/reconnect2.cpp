#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
//重建算子2
//从被攻击影响的算子开始恢复
void reconnect2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup)
{
	vector<int> influencednode;
	vector<int> influencednodebackup;
	vector<int> targetnodeneibor;//和targetnode相连并且没有激活的节点
	int targetnode;
	int seizenode;
	int midnum;
	for (int i = 0;i < rnode.size();i++)//恢复被攻击节点之间的连接
	{
		if (rnode[i].activation == 0)
		{
			for (int j = 0;j < rnode.size();j++)
			{
				if (Gbackup[i][j] == 1 && rnode[j].activation == 0)
				{
					G[i][j] = 1;
					G[j][i] = 1;
					
				}
			}
		}
	}
	calculate_crruentdegree(rnode, G);
	calculate_degree(rnode, Gbackup);
	for (int i = 0;i < rnode.size();i++)//获得被影响节点
	{
		if (rnode[i].activation == 1 && rnode[i].crruentdegree < rnode[i].degree)
		{
			influencednode.push_back(i);
		}
	}
	for (int i = 0;i < (influencednode.size()-1);i++)//对被攻击影响节点进行排序，度小的优先
	{
		for (int j = 0;j < (influencednode.size() - i-1);j++)
		{
			if (rnode[influencednode[j]].degree > rnode[influencednode[j + 1]].degree)
			{
				swap(influencednode[j], influencednode[j + 1]);
			}
		}
	}
	for (int i = 0, ii = influencednode.size();i < ii;i++)
	{
		targetnode = influencednode[0];
		influencednode.erase(influencednode.begin());
		influencednodebackup = influencednode;
		targetnodeneibor.clear();
		updata_targetnodeneibor(rnode, Gbackup, targetnodeneibor, targetnode,G);
		if (influencednode.size() > 0)
		{
			for (int k = 0, kk = influencednodebackup.size();k < kk;k++)
			{
				if (G[targetnode][influencednodebackup[k]] == 1)
				{
					influencednodebackup.erase(influencednodebackup.begin() + k);
					k--;kk--;
				}
			}
			if (influencednodebackup.size() > 0)
			{
				for (int j = 0, jj = rnode[targetnode].degree - rnode[targetnode].crruentdegree;j < jj;j++)//抢夺与被攻击影响节点的连接
				{
					if (influencednodebackup.size() == 0)
					{
						break;
					}
					midnum = ((double)rand() / (RAND_MAX + 1))*influencednodebackup.size();
					seizenode = influencednodebackup[midnum];
					influencednodebackup.erase(influencednodebackup.begin() + midnum);
					judge_seizenode(seizenode, Gbackup, G, rnode, targetnodeneibor, targetnode);
				}
			}
			for (int j = 0, jj = rnode[targetnode].degree - rnode[targetnode].crruentdegree;j < jj;j++)//恢复与之前存在连接的被攻击节点之间的连接
			{
				G[targetnode][targetnodeneibor[j]] = 1;
				G[targetnodeneibor[j]][targetnode] = 1;
				rnode[targetnode].crruentdegree++;
				rnode[targetnodeneibor[j]].crruentdegree++;
			}
		}
		else
		{
			for (int j = 0, jj = rnode[targetnode].degree - rnode[targetnode].crruentdegree;j < jj;j++)//恢复与之前存在连接的被攻击节点之间的连接
			{
				G[targetnode][targetnodeneibor[j]] = 1;
				G[targetnodeneibor[j]][targetnode] = 1;
				rnode[targetnode].crruentdegree++;
				rnode[targetnodeneibor[j]].crruentdegree++;
			}
		}
	}
	for (int i = 0;i < rnode.size();i++)
	{
		for (int j = 0;j < rnode.size();j++)
		{
			if (G[i][j] == 2)
			{
				G[i][j] = 0;
				G[j][i] = 0;
			}
		}
	}
}

void updata_targetnodeneibor(vector<node> &rnode, vector<vector<int>> &Gbackup, vector<int> &targetnodeneibor,int targetnode, vector<vector<int>> &G)
{
	for (int i = 0;i < rnode.size();i++)
	{
		if (Gbackup[targetnode][i] == 1 && rnode[i].activation == 0 && G[targetnode][i] != 2)
		{
			targetnodeneibor.push_back(i);
		}
	}
}

bool judge_seizenode(int seizenode, vector<vector<int>> &Gbackup, vector<vector<int>> &G, vector<node> &rnode, vector<int> &targetnodeneibor, int targetnode)
{
	vector<int> seizenodeneibor;
	vector<int> targetnodeneiborbackup;
	int ppi, ppi2;
	for (int i = 0;i < Gbackup.size();i++)
	{
		if (Gbackup[seizenode][i] == 1 && rnode[i].activation == 0 && G[seizenode][i] != 2)
		{
			seizenodeneibor.push_back(i);
		}
	}
	for (int i = 0, ii = seizenodeneibor.size();i < ii;i++)
	{
		targetnodeneiborbackup = targetnodeneibor;
		ppi = ((double)rand() / (RAND_MAX + 1))*seizenodeneibor.size();
		for (int j = 0,jj=targetnodeneiborbackup.size();j < jj;j++)
		{
			if (G[seizenodeneibor[ppi]][targetnodeneiborbackup[j]] == 1||seizenodeneibor[ppi]==targetnodeneiborbackup[j])
			{
				targetnodeneiborbackup.erase(targetnodeneiborbackup.begin() + j);
				j--;jj--;
			}
		}
		if (targetnodeneiborbackup.size() > 0)
		{
			ppi2 = ((double)rand() / (RAND_MAX + 1))*targetnodeneiborbackup.size();
			G[targetnodeneiborbackup[ppi2]][seizenodeneibor[ppi]] = 1;
			G[seizenodeneibor[ppi]][targetnodeneiborbackup[ppi2]] = 1;
			G[targetnode][seizenode] = 1;
			G[seizenode][targetnode] = 1;
			rnode[targetnode].crruentdegree++;
			rnode[seizenode].crruentdegree++;
			rnode[targetnodeneiborbackup[ppi2]].crruentdegree++;
			rnode[seizenodeneibor[ppi]].crruentdegree++;
			G[seizenodeneibor[ppi]][seizenode] = 2;
			G[seizenode][seizenodeneibor[ppi]] = 2;
			G[targetnode][targetnodeneiborbackup[ppi2]] = 2;
			G[targetnodeneiborbackup[ppi2]][targetnode] = 2;
			for (int l = 0;l < targetnodeneibor.size();l++)
			{
				if (targetnodeneibor[l] == targetnodeneiborbackup[ppi2])
				{
					targetnodeneibor.erase(targetnodeneibor.begin() + l);
				}
			}
			return true;
		}
		seizenodeneibor.erase(seizenodeneibor.begin() + ppi);
	}
	return false;
}