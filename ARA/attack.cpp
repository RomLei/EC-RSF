#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void attack(vector<node> &rnode, vector<vector<int>> &G,double per)//per是攻击节点所占网络节点的百分比,攻击的节点是按照节点度的大小决定，度越大被攻击几率越高
{
	int N = rnode.size(),u=0;
	int attackRange = per*N;
	double attackP;
	int sumdegree=0,atkflag=0,resdegree=0;
	for (int i = 0;i < attackRange;i++)
	{
		attackP = ((double)rand() / (RAND_MAX + 1));
		resdegree = rnode[0].degree;
		u = 0;
		atkflag = 0;
		sumdegree = 0;
		for (int i = 0;i < N;i++)
		{
			sumdegree = sumdegree + rnode[i].degree;
		}
		if (sumdegree == 0)
		{
			atkflag = 1;
			i = attackRange;
		}
		while (atkflag == 0)
		{
			if (attackP <= ((double)resdegree/sumdegree))
			{
				if (rnode[u].activation == 0)
				{
					attackP = ((double)rand() / (RAND_MAX + 1));
					u = 0;
					resdegree = rnode[0].degree;
				}
				else
				{
					atkflag = 1;
					Delete_Node(rnode, G, u);
					calculate_degree(rnode, G);
				}
			}
			else
			{
				u++;
				resdegree = resdegree + rnode[u].degree;
			}
		}
	}
}

void Delete_Node(vector<node> &rnode, vector<vector<int>> &G,int p)//p是删除节点的位置
{
	int N = rnode.size();
	rnode[p].activation = 0;//冻结节点
	for (int i = 0;i < N;i++)
	{
		G[p][i] = 0;
		G[i][p] = 0;
	}
	calculate_degree(rnode, G);
}
