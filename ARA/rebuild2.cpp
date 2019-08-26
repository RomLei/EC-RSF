#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
/*void rebuild2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup, int lastdeletenode)//从被攻击的节点开始恢复
{
	int N = rnode.size(), u = 0,changenode2;
	int neibornode = 0, neibornode2;
	bool sss = true;
	vector<int> atked1(N);
	for (int i = 0;i < N;i++)
	{
		if ((rnode[i].activation == 0)&&(i!=lastdeletenode))
		{
			atked1[u] = i;
			u++;
		}
	}
	atked1.erase(atked1.begin() + u, atked1.end());
	if (u > 1)
	{
		choosenode2(changenode2, atked1);
		while ( !checknode(Gbackup, lastdeletenode, changenode2))
		{
			if (atked1.size() == 1)
			{
				sss = false;
				break;
			}
			choosenode2(changenode2, atked1);
		}
		if (sss)
		{
			choosenodeneibor(lastdeletenode, changenode2, Gbackup, neibornode);
			choosenodeneibor(changenode2, lastdeletenode, Gbackup, neibornode2);
			Gbackup[neibornode][lastdeletenode] = 0;
			Gbackup[lastdeletenode][neibornode] = 0;
			Gbackup[neibornode2][changenode2] = 0;
			Gbackup[changenode2][neibornode2] = 0;
			//建立新的连接
			Gbackup[neibornode][changenode2] = 1;
			Gbackup[changenode2][neibornode] = 1;
			Gbackup[neibornode2][lastdeletenode] = 1;
			Gbackup[lastdeletenode][neibornode2] = 1;
		}
	}
	recovernet(G, Gbackup);
	calculate_degree(rnode, G);
}*/