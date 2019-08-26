#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void output_compute_image(vector<node> &rnode, vector<vector<int>> &G)//��������������ÿ��ʣ��������Ӵص����������浽ARA.txt��
{
	FILE *result;
	result = fopen("ARA.txt", "wt");
	int N = rnode.size();
	int Maxdegreep;
	double largest = 0;
	int mid;
	vector<vector<int>> G2;//�������ڱ��������ڽ�ͼ
	G2.resize(N, vector<int>(N, 0));
	copynet(G, G2);
	for (int i = 0;i < N - 1;i++)
	{
		Maxdegreep = MaxDegreePosition(rnode);
		DeleteNode(rnode, Maxdegreep, G2);
		mid = MaxConnectedCluster(rnode, G2);
		fprintf(result, "%d\t", i);
		fprintf(result, "%d\n", mid);
	}
	for (int i = 0;i < N;i++)//�����״̬ȫ����ԭ
	{
		rnode[i].activation = 1;
	}
	calculate_degree(rnode, G);
}