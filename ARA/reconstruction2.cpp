#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
bool xiu1(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup,int &lastdeletenode)//����false˵���޷��Ż���һ���
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
	for (int i = 0;i < attackednode.size();i++)//��attackednode�к�nodeposition�����Ľڵ�ɾ��
	{
		if (Gbackup[nodeposition][attackednode[i]] == 1)
		{
			attackednode.erase(attackednode.begin() + i);
			i--;
		}
	}
	if (attackednode.size() == 0)//���������Ľڵ���û�����������Ľڵ��򷵻�
	{
		return false;
	}
	for (int i = 0;i < rnode.size();i++)//�ҵ����һ���������Ľڵ�����������û�б������Ľڵ�
	{
		if ((Gbackup[nodeposition][i] == 1)&&(rnode[i].activation==1))
		{
			targetnodeneibors.push_back(i);
		}
	}
	if (targetnodeneibors.size() == 0)//��û�����������һ���������ڵ������Ľڵ㣬�򷵻�false
	{
		return false;
	}
	chooseneibornode(targetnodeneibornode, attackednodeneibornode, attackednodeP, Gbackup, attackednode, targetnodeneibors,rnode);//�ҵ�Ŀ��ڵ��neibor�ڵ㡢�������ڵ�ͱ������ڵ��neibor
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

void chooseneibornode(int &targetnodeneibornode,int &attackednodeneibornode,int &attackednodeP ,vector<vector<int>> &Gbackup, vector<int> &attackednode ,vector<int> &targetnodeneibors, vector<node> &rnode)//�ҵ���targetnodeneibornode����targetnodeneibors�е�λ��,attackednodeneibornode��G�е�λ��
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
		for (int i = 0;i < Gbackup.size();i++)//�ҵ�attackednode��neibor������û�б�����������
		{
			if ((Gbackup[attackednode2[ppi]][i] == 1) && (rnode[i].activation == 1))
			{
				attackednodeneibor.push_back(i);
			}
		}
		while (!judgement(attackednodeneibor, targetnodeneibors[ppi2], Gbackup))//�ж�attackednode��neibor�Ƿ�������Ŀ��ڵ�neibor�ڵ����������
		{
			attackednode2.erase(attackednode2.begin() + ppi);
			if (attackednode2.size() == 0)//���������ڵ㶼�������ˣ���Ȼû��������Ŀ��ڵ�neibor�����������Ľڵ㣬��ɾ����Ŀ��ڵ��neibor�ڵ㣬����ѭ��
			{
				targetnodeneibors.erase(targetnodeneibors.begin() + ppi2);
				break;
			}
			ppi = ((double)rand() / (RAND_MAX + 1))*attackednode2.size();
			attackednodeneibor.clear();
			for (int i = 0;i < Gbackup.size();i++)//�ҵ�attackednode��neibor������û�б�����������
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