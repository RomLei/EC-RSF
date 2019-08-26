#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
//���ӵļ��ʺ͸õ�Ķȳ�����أ�δʵ��)
//���ͱ������ڵ�֮�������ʹ�õ���֮ǰ����������������û�иı�
//�ؽ�����1
void reconnect1(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup)//�������Ľڵ�Ӷ�С�Ŀ�ʼ�ָ�
{
	int attacknum = -1,attacknodeP;
	int ppi = 0, pp = 0, ppi2 = 0, ppi3 = 0;
	calculate_crruentdegree(rnode, G);
	calculate_degree(rnode, Gbackup);
	vector<int> damagenode;
	vector<int> ablenode;
	vector<int> attacknodeneibor;
	vector<int> backupneibor;
	for (int i = 0;i < rnode.size();i++)//�ҵ��������ڵ������
	{
		if (rnode[i].activation == 0)
		{
			attacknum++;
		}
	}
	for (int i = attacknum;i >= 0;i--)
	{
		attacknodeP = Find_Attack_Node(rnode, i);
		for (int u = 0;u < rnode.size();u++)//���Ȼָ�ԭ�����ӵĽڵ���û�б������Ľڵ�
		{
			if (Gbackup[attacknodeP][u] == 1 && rnode[u].activation == 1 && (rnode[u].crruentdegree < rnode[u].degree) && G[attacknodeP][u] != 2)
			{
				G[attacknodeP][u] = 1;G[u][attacknodeP] = 1;
				rnode[attacknodeP].crruentdegree++;
				rnode[u].crruentdegree++;
			}
		}
		Updata_Damagenode(rnode, damagenode, G, attacknodeP);
		Updata_attacknodeneibor(rnode, Gbackup, attacknodeP, attacknodeneibor,G);
		if ((rnode[attacknodeP].crruentdegree < rnode[attacknodeP].degree) && (damagenode.size() != 0))//��ʣ�µ�û�б������Ľڵ���ѡȡһЩ�ڵ㣨���ӵĽڵ��������Ϊ�����ճ��˱���ʧ�Ľڵ㣩��������,������Ϊ�����������ڵ������
		{
			for (int u = 0, uu = rnode[attacknodeP].degree - rnode[attacknodeP].crruentdegree;u < uu;u++)
			{
				if (damagenode.size() != 0)
				{
					pp = ((double)rand() / (RAND_MAX + 1))*damagenode.size();
					ppi = damagenode[pp];
					damagenode.erase(damagenode.begin() + pp);
					ablenode.clear();
					backupneibor.clear();
					for (int j = 0;j < rnode.size();j++)//�ҵ����������ھ�
					{
						if (Gbackup[ppi][j] == 1 && rnode[j].activation == 0 && G[ppi][j] != 2)
						{
							ablenode.push_back(j);
						}
					}
					for (int j = 0;j < ablenode.size();j++)//�ж����ھӵĿ�ѡ����
					{
						if (!judge_connect(ablenode[j], attacknodeneibor, Gbackup, G))
						{
							ablenode.erase(ablenode.begin() + j);
							j--;
						}
					}
					if (ablenode.size() != 0)
					{
						ppi2 = ((double)rand() / (RAND_MAX + 1))*ablenode.size();
						ppi2 = ablenode[ppi2];
						for (int j = 0;j < attacknodeneibor.size();j++)
						{
							if (Gbackup[ppi2][attacknodeneibor[j]] == 1||G[ppi2][attacknodeneibor[j]]==1||ppi2==attacknodeneibor[j])
							{
								backupneibor.push_back(attacknodeneibor[j]);
								attacknodeneibor.erase(attacknodeneibor.begin() + j);
								j--;
							}
						}
						ppi3 = ((double)rand() / (RAND_MAX + 1))*attacknodeneibor.size();
						G[attacknodeP][ppi] = 1;G[ppi][attacknodeP] = 1;
						G[ppi2][attacknodeneibor[ppi3]] = 1;G[attacknodeneibor[ppi3]][ppi2] = 1;
						G[ppi][ppi2] = 2;G[ppi2][ppi] = 2;//�������㲻������
						rnode[attacknodeP].crruentdegree++;
						rnode[ppi].crruentdegree++;
						rnode[ppi2].crruentdegree++;
						rnode[attacknodeneibor[ppi3]].crruentdegree++;
						attacknodeneibor.erase(attacknodeneibor.begin() + ppi3);
						attacknodeneibor.insert(attacknodeneibor.end(), backupneibor.begin(), backupneibor.end());
					}
				}
				
			}
		}
		if (rnode[attacknodeP].crruentdegree < rnode[attacknodeP].degree)
		{
			for (int j = 0;j < attacknodeneibor.size();j++)
			{
				G[attacknodeP][attacknodeneibor[j]] = 1;
				G[attacknodeneibor[j]][attacknodeP] = 1;
				rnode[attacknodeP].crruentdegree++;
				rnode[attacknodeneibor[j]].crruentdegree++;
			}
		}
		rnode[attacknodeP].activation = 1;
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

int Find_Attack_Node(vector<node> rnode,int attacknum)//�ҵ���attacknum�����������½ڵ�λ��
{
	for (int i = 0;i < rnode.size();i++)
	{
		if (rnode[i].attackrank == attacknum)
		{
			return i;
		}
	}
}

void Updata_Damagenode(vector<node> rnode, vector<int> &damagenode, vector<vector<int>> &G,int attacknodeP)
{
	damagenode.clear();
	for (int i = 0;i < rnode.size();i++)
	{
		if ((rnode[i].crruentdegree < rnode[i].degree) && (G[attacknodeP][i] != 1) && rnode[i].activation == 1)
		{
			damagenode.push_back(i);
		}
	}
}

void Updata_attacknodeneibor(vector<node> rnode, vector<vector<int>> &Gbackup, int attacknodeP,vector<int> &attacknodeneibor, vector<vector<int>> &G)
{
	attacknodeneibor.clear();
	for (int i = 0;i < rnode.size();i++)
	{
		if (Gbackup[attacknodeP][i] == 1 && rnode[i].activation == 0 && rnode[i].crruentdegree < rnode[i].degree && G[attacknodeP][i] == 0)
		{
			attacknodeneibor.push_back(i);
		}
	}
}

bool judge_connect(int ablenode, vector<int> attacknodeneibor, vector<vector<int>> &Gbackup, vector<vector<int>> &G)
{
	int x = 0;
	for (int i = 0;i < attacknodeneibor.size();i++)
	{
		if (Gbackup[ablenode][attacknodeneibor[i]] == 1 || ablenode == attacknodeneibor[i] || G[ablenode][attacknodeneibor[i]] == 1)
		{
			x++;
		}
	}
	if (x == attacknodeneibor.size())
	{
		return false;
	}
	else
	{
		return true;
	}
}