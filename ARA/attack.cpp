#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void attack(vector<node> &rnode, vector<vector<int>> &G,double per)//per�ǹ����ڵ���ռ����ڵ�İٷֱ�,�����Ľڵ��ǰ��սڵ�ȵĴ�С��������Խ�󱻹�������Խ��
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

void Delete_Node(vector<node> &rnode, vector<vector<int>> &G,int p)//p��ɾ���ڵ��λ��
{
	int N = rnode.size();
	rnode[p].activation = 0;//����ڵ�
	for (int i = 0;i < N;i++)
	{
		G[p][i] = 0;
		G[i][p] = 0;
	}
	calculate_degree(rnode, G);
}
