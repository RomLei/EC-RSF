#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
bool xiu1(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup,int &lastdeletenode)//返回false说明无法优化这一情况
{
	vector<int> attackednode;//Vk
	vector<int> targetnodeneibors;//Vj
	int targetnodeneibornode = -1;
	int attackednodeneibornode;//Vl
	int attackednodeP;//Vk
	calculate_degree(rnode, Gbackup);
	calculate_crruentdegree(rnode, G);
	int nodeposition;//Vi
	for (int i = 0, ii = rnode.size();i < ii;i++)
	{
		if ((rnode[i].activation == 0) && (i != lastdeletenode))
		{
			attackednode.push_back(i);
		}
	}
	nodeposition = lastdeletenode;
	for (int i = 0;i < attackednode.size();i++)//将attackednode中和nodeposition相连的节点删除
	{
		if (Gbackup[nodeposition][attackednode[i]] == 1)
		{
			attackednode.erase(attackednode.begin() + i);
			i--;
		}
	}
	if (attackednode.size() == 0)//若被攻击的节点中没有满足条件的节点则返回
	{
		return false;
	}
	for (int i = 0;i < rnode.size();i++)//找到最后一个被攻击的节点与其相连的没有被攻击的节点
	{
		if ((Gbackup[nodeposition][i] == 1)&&(rnode[i].activation==1))
		{
			targetnodeneibors.push_back(i);
		}
	}
	if (targetnodeneibors.size() == 0)//若没有满足与最后一个被攻击节点相连的节点，则返回false
	{
		return false;
	}
	chooseneibornode(targetnodeneibornode, attackednodeneibornode, attackednodeP, Gbackup, attackednode, targetnodeneibors,rnode);//找到目标节点的neibor节点、被攻击节点和被攻击节点的neibor
	if (targetnodeneibornode==-1)
	{
		return false;
	}
	copynet(Gbackup, G);
	G[nodeposition][targetnodeneibors[targetnodeneibornode]] = 0;
	G[targetnodeneibors[targetnodeneibornode]][nodeposition] = 0;
	G[attackednodeP][attackednodeneibornode] = 0;
	G[attackednodeneibornode][attackednodeP] = 0;
	G[nodeposition][attackednodeP] = 1;
	G[attackednodeP][nodeposition] = 1;
	G[targetnodeneibors[targetnodeneibornode]][attackednodeneibornode] = 1;
	G[attackednodeneibornode][targetnodeneibors[targetnodeneibornode]] = 1;
	return true;
}

void chooseneibornode(int &targetnodeneibornode,int &attackednodeneibornode,int &attackednodeP ,vector<vector<int>> &Gbackup, vector<int> &attackednode ,vector<int> &targetnodeneibors, vector<node> &rnode)//找到的targetnodeneibornode是在targetnodeneibors中的位置,attackednodeneibornode是G中的位置
{
	vector<int>attackednodeneibor;
	vector<int>attackednode2;//Vk
	int ppi, ppi2;
	bool flagg=false;
	while ((targetnodeneibors.size() != 0)&&(!flagg))
	{
		attackednode2 = attackednode;
		ppi2 = ((double)rand() / (RAND_MAX + 1))*targetnodeneibors.size();
		ppi = ((double)rand() / (RAND_MAX + 1))*attackednode2.size();
		attackednodeneibor.clear();
		for (int i = 0;i < Gbackup.size();i++)//找到attackednode的neibor，满足没有被攻击的条件
		{
			if ((Gbackup[attackednode2[ppi]][i] == 1) && (rnode[i].activation == 1))
			{
				attackednodeneibor.push_back(i);
			}
		}
		while (!judgement(attackednodeneibor, targetnodeneibors[ppi2], Gbackup))//判断attackednode的neibor是否满足与目标节点neibor节点的连接条件
		{
			attackednode2.erase(attackednode2.begin() + ppi);
			if (attackednode2.size() == 0)//若被攻击节点都被遍历了，仍然没有满足与目标节点neibor不相连条件的节点，则删除该目标节点的neibor节点，跳出循环
			{
				targetnodeneibors.erase(targetnodeneibors.begin() + ppi2);
				break;
			}
			ppi = ((double)rand() / (RAND_MAX + 1))*attackednode2.size();
			attackednodeneibor.clear();
			for (int i = 0;i < Gbackup.size();i++)//找到attackednode的neibor，满足没有被攻击的条件
			{
				if ((Gbackup[attackednode2[ppi]][i] == 1) && (rnode[i].activation == 1))
				{
					attackednodeneibor.push_back(i);
				}
			}
		}
		if (attackednode2.size() != 0)
		{
			targetnodeneibornode = ppi2;
			attackednodeP = attackednode2[ppi];
			attackednodeneibornode = ((double)rand() / (RAND_MAX + 1))*attackednodeneibor.size();
			attackednodeneibornode = attackednodeneibor[attackednodeneibornode];
			flagg = true;
		}
	}
	if (targetnodeneibors.size() == 0)
	{
		targetnodeneibornode = -1;
	}
}

bool judgement(vector<int> &attackednodeneibor, int nodep, vector<vector<int>> &Gbackup)
{
	for (int i = 0;i < attackednodeneibor.size();i++)
	{
		if ((Gbackup[nodep][attackednodeneibor[i]] == 1) || (attackednodeneibor[i] == nodep))
		{
			attackednodeneibor.erase(attackednodeneibor.begin() + i);
			i--;
		}
	}
	if (attackednodeneibor.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}