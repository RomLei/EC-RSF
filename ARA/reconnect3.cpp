#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
//重建算子3
//将剩余网络完全重连
void reconnect3(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup)
{
	vector<int> restnode;
	vector<int> restnodeavailable;
	int ppi,curnode;
	for (int i = 0;i < rnode.size();i++)//恢复被攻击节点之间的连接
	{
		if (rnode[i].activation == 0)
		{
			for (int j = 0;j < rnode.size();j++)
			{
				if (Gbackup[i][j] == 1)
				{
					G[i][j] = 1;
					G[j][i] = 1;

				}
			}
		}
	}
	for (int i = 0;i < rnode.size();i++)//断开剩余节点之间的连接
	{
		if (rnode[i].activation == 1)
		{
			for (int j = 0;j < rnode.size();j++)
			{
				if (Gbackup[i][j] == 1 && rnode[j].activation == 1)
				{
					G[i][j] = 0;
					G[j][i] = 0;
				}
			}
		}
	}
	calculate_crruentdegree(rnode, G);
	calculate_degree(rnode, Gbackup);
	updata_difdegree(rnode);
	for (int i = 0;i < rnode.size();i++)
	{
		if (rnode[i].activation == 1)
		{
			restnode.push_back(i);
		}
	}
	for (int i = 0,ii=restnode.size();i < ii;i++)
	{
		if (restnode.size() == 0)
		{
			break;
		}
		curnode = restnode[0];
		restnode.erase(restnode.begin());
		while (rnode[curnode].degree - rnode[curnode].crruentdegree > 0)
		{
			if (restnode.size() == 0)
			{
				break;
			}
			ppi = ((double)rand() / (RAND_MAX + 1))*restnode.size();
			while (!check_available(curnode, Gbackup, G,restnode[ppi],rnode,restnode))
			{
				ppi = ((double)rand() / (RAND_MAX + 1))*restnode.size();
			}
			G[curnode][restnode[ppi]] = 1;
			G[restnode[ppi]][curnode] = 1;
			rnode[curnode].crruentdegree++;
			rnode[curnode].difdegree--;
			rnode[restnode[ppi]].crruentdegree++;
			rnode[restnode[ppi]].difdegree--;
			if (rnode[restnode[ppi]].degree - rnode[restnode[ppi]].crruentdegree == 0)
			{
				restnode.erase(restnode.begin() + ppi);
			}
		}
	}
}

 bool check_available(int curnode, vector<vector<int>> &Gbackup, vector<vector<int>> &G,int targetnode, vector<node> &rnode,vector<int> restnode)//未能实现判断能否相连
{
	if (G[curnode][targetnode] == 1)
	{
		return false;
	}
	if (Gbackup[curnode][targetnode] == 1)
	{
		return true;
	}
	for (int i = 0;i < Gbackup.size();i++)
	{
		if (Gbackup[curnode][i] == 1)
		{
			if (Gbackup[i][targetnode] == 1)
			{
				if (G[curnode][i] == 1 || G[i][targetnode] == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;

/*	int degreeflag = rnode[restnode[0]].difdegree;
	rnode[curnode].difdegree--;
	rnode[targetnode].difdegree--;
	for (int i = 1;i < restnode.size();i++)
	{
		if (degreeflag > 0)
		{
			degreeflag = degreeflag - rnode[restnode[i]].difdegree;
		}
		else
		{
			degreeflag = degreeflag + rnode[restnode[i]].difdegree;
		}
	}
	rnode[curnode].difdegree++;
	rnode[targetnode].difdegree++;
	if (degreeflag == 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/

}

 void updata_difdegree(vector<node> &rnode)
 {
	 for (int i = 0;i < rnode.size();i++)
	 {
		 rnode[i].difdegree = rnode[i].degree - rnode[i].crruentdegree;
	 }
 }