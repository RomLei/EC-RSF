#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
double compute(vector<node> &rnode, vector<vector<int>> &G)//��������G��Rֵ
{
	int N = rnode.size();
	int Maxdegreep;
	double largest = 0;
	int mid;
	double res = 0;
	vector<vector<int>> G2;//�������ڱ��������ڽ�ͼ
	G2.resize(N, vector<int>(N, 0));
	copynet(G, G2);
	for (int i = 0;i < N - 1;i++)
	{
		Maxdegreep = MaxDegreePosition(rnode);
		DeleteNode(rnode, Maxdegreep, G2);
		mid = MaxConnectedCluster(rnode, G2);
		largest = largest + (double)mid / N;
	}
	res = (double)largest / N;
	for (int i = 0;i < N;i++)//�����״̬ȫ����ԭ
	{
		rnode[i].activation = 1;
	}
	calculate_degree(rnode, G);
	return res;
}

int MaxDegreePosition(vector<node> &rnode)//����������degree���Ľڵ��λ��
{
	int N = rnode.size();
	int maxnump = 0;
	int maxdegree = rnode[0].degree;
	for (int i = 1;i < N;i++)
	{
		if (rnode[i].degree > maxdegree)
		{
			maxnump = i;
			maxdegree = rnode[i].degree;
		}
	}
	if (maxdegree == 0)
	{
		for (int i = 0;i < rnode.size();i++)
		{
			if (rnode[i].activation == 1)
			{
				maxnump = i;
				return maxnump;
			}
		}
	}
	return maxnump;
}

void calculate_degree(vector<node> &rnode, vector<vector<int>> &G)//�Ǽ��������������нڵ��degree
{
	int N = rnode.size();
	for (int p = 0;p < N;p++)
	{
		rnode[p].degree = 0;
		for (int i = 0;i < N;i++)
		{
			if (G[p][i] == 1)
			{
				rnode[p].degree++;
			}
		}
	}
}

void DeleteNode(vector<node> &rnode, int p, vector<vector<int>> &G)//p��ɾ���Ľڵ�λ��
{
	int N = rnode.size();
	rnode[p].activation = 0;//����ڵ�
	for (int i = 0;i < N;i++)
	{
		if (G[p][i] == 1)
		{
			G[p][i] = 0;
			G[i][p] = 0;
			rnode[p].degree--;
			rnode[i].degree--;
		}	
	}
}

int MaxConnectedCluster(vector<node> &rnode, vector<vector<int>> &G)//����������ӴصĽڵ�����
{
	int N = rnode.size();
	vector<int> search(N);//�洢�ڵ��Ƿ񱻼���������Ϣ
	int maxconnectnum = 1;
	int p = 0;
	int IN = 0;
	for (int i = 0;i < N;i++)
	{
		search[i] = i;
	}
	while (whether_search_end(search, rnode))
	{
		while (search[p] == -1 || rnode[p].activation == 0)
		{
			p++;
		}
		IN = Include_Nodes(p, G, search, rnode);
		if (maxconnectnum < IN)
		{
			maxconnectnum = IN;
		}
	}
	return maxconnectnum;
}

bool whether_search_end(vector<int> &search, vector<node> &rnode)//����false˵��ȫ���㶼���������ˣ�����true���е�δ������
{
	int N = rnode.size();
	bool u = false;
	for (int i = 0;i < N;i++)
	{
		if (search[i] != -1 && rnode[i].activation != 0)
		{
			u = true;
		}
	}
	return u;
}

int Include_Nodes(int p, vector<vector<int>> &G, vector<int> &search, vector<node> &rnode)//����ڵ�λ��p�������ýڵ����ӵ�δ���������Ľڵ�����������ֵ
{
	int N = rnode.size();
	int res;
	if (search[p] != -1 && rnode[p].activation != 0)
	{
		search[p] = -1;
		int maxconnectnum = 1;
		for (int i = 0;i < N;i++)
		{
			if (G[p][i] == 1 && search[i] != -1)
			{
				maxconnectnum = maxconnectnum + Include_Nodes(i, G, search, rnode);
			}
		}
		res = maxconnectnum;
	}
	else
	{
		res = 0;
	}
	return res;
}

void copynet(vector<vector<int>> &G, vector<vector<int>> &G2)//��G��������Ϣȫ������������G2
{
	int N = G.size();
	for (int i = 0;i < N;i++)
	{
		for (int u = 0;u < N;u++)
		{
			G2[i][u] = G[i][u];
		}
	}
}

void copynode(vector<node> &rnode1, vector<node> &rnode2)//��rnode1����Ϣȫ��������rnode2��
{
	for (int i = 0;i < rnode1.size();i++)
	{
		rnode2[i].activation = rnode1[i].activation;
		rnode2[i].crruentdegree = rnode1[i].crruentdegree;
		rnode2[i].degree = rnode1[i].degree;
		rnode2[i].degreebackup = rnode1[i].degreebackup;
		rnode2[i].position[1] = rnode1[i].position[1];
		rnode2[i].position[0] = rnode1[i].position[0];
	}
}

void backupdegree(vector<node> &rnode)
{
	for (int i = 0;i < rnode.size();i++)
	{
		rnode[i].checkdegree = rnode[i].degree;
	}
}

bool checkdegree(vector<node> rnode)
{
	for (int i = 0;i < rnode.size();i++)
	{
		if (rnode[i].degree != rnode[i].checkdegree)
		{
			return false;
		}
	}
	return true;

}