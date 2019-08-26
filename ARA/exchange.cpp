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
	for (int i = 0;i < N;i++)//存储剩余节点,存在边连接的
	{
		if ((rnode[i].activation == 1)&&(rnode[i].crruentdegree!=0))
		{
			restnodeexistedge.push_back(i);
		}
	}
	if (restnodeexistedge.size() == 0)//若不存在还有边连接的节点，返回false
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

bool choosenode2and3(vector<int> &restnodeexistedge, vector<vector<int>> &Gbackup, vector<vector<int>> &restG, vector<node> &rnode,int &node1,int &node2,int &node3, int &node4)//返回false说明不存在满足node1条件的node3
{
	int N = Gbackup.size();
	vector<int> node3list;
	vector<int> node3listbackup;
	vector<int> node1neibor;
	for (int i = 0;i < N;i++)//找到node1的仍然存在边连接的节点
	{
		if (restG[restnodeexistedge[node1]][i] == 1)
		{
			node1neibor.push_back(i);
		}
	}
	for (int i = 0;i < N;i++)//找到不与node1连接的node3节点的集合
	{
		if ((rnode[i].activation == 1) && (restG[restnodeexistedge[node1]][i] != 1))
		{
			if (restnodeexistedge[node1] != i)
			{
				node3list.push_back(i);
			}	
		}
	}
	if (node3list.size() == 0)//若满足条件的node3节点集合不存在，返回false
	{
		return false;
	}
	node3listbackup = node3list;//备份一份node3节点的备份
	node2 = ((double)rand() / (RAND_MAX + 1))*node1neibor.size();//找到node2
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

bool choosenode3(int &node2,int &node3,vector<int> &node3listbackup,vector<vector<int>> &Gbackup, vector<int> node1neibor,vector<node> &rnode,int &node4)//返回false说明不存在满足node2条件的node3
{
	int N = Gbackup.size();
	bool sss = true;
	vector<int> node3neibor;
	while (sss)
	{
		node3 = node3listbackup.size()*((double)rand() / (RAND_MAX + 1));//找到node3
		node3neibor.clear();//清除node3的neibor信息
		for (int i = 0;i < N;i++)
		{
		//	if (Gbackup[node3listbackup[node3]][i] == 1)
			if ((Gbackup[node3listbackup[node3]][i] == 1) && (rnode[i].activation == 0))//找到的是和node3相连接，并且已经被攻击的节点，修改成所有与node3相连接的节点都有被交换的可能
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