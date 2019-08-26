#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
bool xiu3(vector<vector<int>> &restG,vector<node> &rnode, vector<vector<int>> &Gbackup)//local Search 1
{
	int N = rnode.size();
	int node1 = 0, node2 = 0, node3 = 0, node4 = 0;
	vector<int> restnodeexistedge;
	calculate_degree(rnode, Gbackup);
	calculate_crruentdegree(rnode, restG);
	for (int i = 0;i < N;i++)//�洢ʣ��ڵ�,���ڱ����ӵ�
	{
		if ((rnode[i].activation == 1)&&(rnode[i].crruentdegree!=0))
		{
			restnodeexistedge.push_back(i);
		}
	}
	if (restnodeexistedge.size() == 0)//�������ڻ��б����ӵĽڵ㣬����false
	{
		return false;
	}
	node1 = ((double)rand() / (RAND_MAX + 1))*restnodeexistedge.size();
	while (!choosenode2and3(restnodeexistedge, Gbackup, restG, rnode, node1, node2, node3,node4))
	{
		restnodeexistedge.erase(restnodeexistedge.begin() + node1);
		node1 = ((double)rand() / (RAND_MAX + 1))*restnodeexistedge.size();
		if (restnodeexistedge.size() == 0)
		{
			return false;
		}
	}
	copynet(Gbackup, restG);
	restG[restnodeexistedge[node1]][node2] = 0;
	restG[node2][restnodeexistedge[node1]] = 0;
	restG[node3][node4] = 0;
	restG[node4][node3] = 0;
	restG[restnodeexistedge[node1]][node3] = 1;
	restG[node3][restnodeexistedge[node1]] = 1;
	restG[node2][node4] = 1;
	restG[node4][node2] = 1;
}

bool choosenode2and3(vector<int> &restnodeexistedge, vector<vector<int>> &Gbackup, vector<vector<int>> &restG, vector<node> &rnode,int &node1,int &node2,int &node3, int &node4)//����false˵������������node1������node3
{
	int N = Gbackup.size();
	vector<int> node3list;
	vector<int> node3listbackup;
	vector<int> node1neibor;
	for (int i = 0;i < N;i++)//�ҵ�node1����Ȼ���ڱ����ӵĽڵ�
	{
		if (restG[restnodeexistedge[node1]][i] == 1)
		{
			node1neibor.push_back(i);
		}
	}
	for (int i = 0;i < N;i++)//�ҵ�����node1���ӵ�node3�ڵ�ļ���
	{
		if ((rnode[i].activation == 1) && (restG[restnodeexistedge[node1]][i] != 1))
		{
			if (restnodeexistedge[node1] != i)
			{
				node3list.push_back(i);
			}	
		}
	}
	if (node3list.size() == 0)//������������node3�ڵ㼯�ϲ����ڣ�����false
	{
		return false;
	}
	node3listbackup = node3list;//����һ��node3�ڵ�ı���
	node2 = ((double)rand() / (RAND_MAX + 1))*node1neibor.size();//�ҵ�node2
	while (!choosenode3(node2, node3, node3listbackup, Gbackup, node1neibor, rnode,node4))
	{
		node3listbackup = node3list;
		node1neibor.erase(node1neibor.begin() + node2);
		if (node1neibor.size() == 0)
		{
			return false;
		}
		node2 = ((double)rand() / (RAND_MAX + 1))*node1neibor.size();
	}
	node2 = node1neibor[node2];
	return true;
}

bool choosenode3(int &node2,int &node3,vector<int> &node3listbackup,vector<vector<int>> &Gbackup, vector<int> node1neibor,vector<node> &rnode,int &node4)//����false˵������������node2������node3
{
	int N = Gbackup.size();
	bool sss = true;
	vector<int> node3neibor;
	while (sss)
	{
		node3 = node3listbackup.size()*((double)rand() / (RAND_MAX + 1));//�ҵ�node3
		node3neibor.clear();//���node3��neibor��Ϣ
		for (int i = 0;i < N;i++)
		{
		//	if (Gbackup[node3listbackup[node3]][i] == 1)
			if ((Gbackup[node3listbackup[node3]][i] == 1) && (rnode[i].activation == 0))//�ҵ����Ǻ�node3�����ӣ������Ѿ��������Ľڵ㣬�޸ĳ�������node3�����ӵĽڵ㶼�б������Ŀ���
			{
				node3neibor.push_back(i);
			}
		}
		sss = false;
		for (int i = 0, ii = node3neibor.size();i < ii;i++)
		{
			if (Gbackup[node1neibor[node2]][node3neibor[i]] == 1)
			{
				node3neibor.erase(node3neibor.begin() + i);
				i--;
				ii--;
			}
		}
		if (node3neibor.size() == 0)
		{
			sss = true;
			node3listbackup.erase(node3listbackup.begin() + node3);
		}
		if (node3listbackup.size() == 0)
		{
			return false;
		}
	}
	node4 = ((double)rand() / (RAND_MAX + 1))*node3neibor.size();
	node4 = node3neibor[node4];
	node3 = node3listbackup[node3];
	return true;
}