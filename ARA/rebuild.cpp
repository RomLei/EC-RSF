#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
bool xiu2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup)//随机交换被攻击节点的边
{
	int N = rnode.size();
	int suc = 0, changenode = -1, y = 0, x = 0, changenode2 = -1,changenode22;
	int neibornode = 0, neibornode2 = 0;
	vector<int> atked;
	vector<int> atked1;
	vector<int> atked2;
	vector<int> node1neibor;//存储交换的节点的邻居
	vector<int> node2neibor2;//存储交换的节点的邻居
	vector<int> nodeneiborbackup;
	double ppi;
	bool sss = true;
	//找到被攻击的节点，放入atked,u是被攻击节点的数量
	for (int i = 0;i < N;i++)
	{
		if (rnode[i].activation == 0)
		{
			atked.push_back(i);
			atked1.push_back(i);
			atked2.push_back(i);
		}
	}
	while (atked1.size() > 0)
	{
		choosenode1(changenode, atked1, Gbackup);
		atked2 = atked;
		delete_node_from_atk(changenode, atked2);
		if (atked2.size() == 0)
		{
			return false;
		}
		find_neibor(changenode,node1neibor, Gbackup);
		nodeneiborbackup = node1neibor;
		choosenode2(changenode2, atked2);
		sss = true;
		while (!judge_node(changenode2, nodeneiborbackup, Gbackup, neibornode,changenode,neibornode2))
		{
			if (atked2.size() == 0)
			{
				sss = false;
				break;
			}
			choosenode2(changenode2, atked2);
		}
		if (sss == true)
		{
			break;
		}
	}
	if (atked1.size() == 0)
	{
		return false;
	}

	recovernet(G, Gbackup);
	G[changenode][neibornode] = 0;
	G[neibornode][changenode] = 0;
	G[changenode2][neibornode2] = 0;
	G[neibornode2][changenode2] = 0;
	G[changenode][neibornode2] = 1;
	G[neibornode2][changenode] = 1;
	G[changenode2][neibornode] = 1;
	G[neibornode][changenode2] = 1;
	return true;
}

void recovernet(vector<vector<int>> &G, vector<vector<int>> &Gbackup)//将备份网络拷入正式网络
{
	int N = G.size();
	for (int i = 0;i < N;i++)
	{
		for (int u = 0;u < N;u++)
		{
			G[i][u] = Gbackup[i][u];
		}
	}
}


bool choosenode1(int &changenode,  vector<int> &atked1, vector<vector<int>> &Gbackup)//选出node1
{
	int bb;
	if (atked1.size() > 0)
	{
		bb = ((double)rand() / (RAND_MAX + 1))*atked1.size();
		changenode = atked1[bb];
		atked1.erase(atked1.begin() + bb);
		return true;
	}
	else
	{
		return false;
	}
}

void choosenode2(int &changenode2,vector<int> &atked2)//选出node2
{
	int bb;
	bb = ((double)rand() / (RAND_MAX + 1))*atked2.size();
	changenode2 = atked2[bb];
	atked2.erase(atked2.begin() + bb);
}

void rebuildnode(vector<node> &rnode)
{
	for (int i = 0, ii = rnode.size();i < ii;i++)
	{
		rnode[i].activation = 1;
	}
}

void delete_node_from_atk(int &deletenode,vector<int> &atk)//删除atk中和deletenode相同的节点
{
	for (int i = 0;i < atk.size();i++)
	{
		if (atk[i] == deletenode)
		{
			atk.erase(atk.begin() + i);
			break;
		}
	}
}

void find_neibor(int &changenode,vector<int> &changenodeneibor, vector<vector<int>> &Gbackup)//找到changenode在atk中的neibor
{
	changenodeneibor.clear();
	for (int i = 0;i < Gbackup.size();i++)
	{
		if (Gbackup[changenode][i] == 1)
		{
			changenodeneibor.push_back(i);
		}
	}
}

bool judge_node(int &changenode2,vector<int> &neibor, vector<vector<int>> &Gbackup,int &neibornode,int &changenode,int &neibornode2)//判断changenode能否在neibor中找到一个符合条件的节点，保存在neibornode中，成功返回true
{
	while (neibor.size() != 0)
	{
		neibornode = ((double)rand() / (RAND_MAX + 1))*neibor.size();
		if ((Gbackup[neibor[neibornode]][changenode2] == 1)||(neibor[neibornode]==changenode2))
		{
			neibor.erase(neibor.begin() + neibornode);
		}
		else if(judge_node_1(changenode,changenode2,Gbackup,neibornode2))
		{
			neibornode = neibor[neibornode];
			return true;
		}
		else
		{
			return false;
		}
	}	
	return false;
}

bool judge_node_1(int &changenode,int &changenode2, vector<vector<int>> &Gbackup,int &neibornode2)
{
	vector<int> changenode2neibor;
	for (int i = 0;i < Gbackup.size();i++)
	{
		if ((Gbackup[i][changenode2] == 1)&&(i!=changenode))
		{
			changenode2neibor.push_back(i);
		}
	}
	while (changenode2neibor.size() != 0)
	{
		neibornode2 = ((double)rand() / (RAND_MAX + 1))*changenode2neibor.size();
		if (Gbackup[changenode][changenode2neibor[neibornode2]] == 1)
		{
			changenode2neibor.erase(changenode2neibor.begin() + neibornode2);
		}
		else
		{
			neibornode2 = changenode2neibor[neibornode2];
			return true;
		}
	}
	return false;
}