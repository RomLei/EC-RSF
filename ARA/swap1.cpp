#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include"ARA.h"
using namespace std;

void swap1(vector<vector<int>> &G)//�������������
{
	int node1, node11, node2, node21;
	bool suc = true,suc2=true;
	vector<int> node1neibor;
	vector<int> node2neibor;
	node1 = ((double)rand() / (RAND_MAX + 1))*G.size();//��λ��һ���ڵ�
	for (int i=0;i < G.size();i++)//�ҵ���һ���ڵ���ھ�
	{
		if (G[node1][i] == 1)
		{
			node1neibor.push_back(i);
		}
	}
	node11 = node1neibor[((double)rand() / (RAND_MAX + 1))*node1neibor.size()];//��λ���һ���ڵ������Ľڵ�
	while (suc2)
	{
		suc = true;
		suc2 = false;
		node2neibor.clear();
		while (suc)//��λ�ڶ����ڵ�
		{
			suc = false;
			node2 = ((double)rand() / (double)(RAND_MAX + 1))*G.size();
			if ((node2 == node1) || (node2 == node11)||(G[node2][node11]==1))
			{
				suc = true;
			}
		}
		for (int i=0;i < G.size();i++)//�ҵ��ڶ����ڵ���ھ�
		{
			if (G[node2][i] == 1)
			{
				node2neibor.push_back(i);
			}
		}
		node21 = node2neibor[((double)rand() / (double)(RAND_MAX + 1))*node2neibor.size()];//��λ���һ���ڵ������Ľڵ�
		if ((node21 == node1) || (node21 == node11) || (G[node21][node1] == 1))
		{
			suc2 = true;
		}
	}
	G[node1][node11] = 0;
	G[node11][node1] = 0;
	G[node2][node21] = 0;
	G[node21][node2] = 0;
	G[node1][node21] = 1;
	G[node21][node1] = 1;
	G[node2][node11] = 1;
	G[node11][node2] = 1;

}
