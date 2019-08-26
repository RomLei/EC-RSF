#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include"ARA.h"
using namespace std;
void attack2(vector<node> &rnode, vector<vector<int>> &G, int deletenum,int &lastdeletenode)//deletenum是删除节点的数量,删除节点从大到小的顺序
{
	int maxdegreeP = 0;
	reset_attackrank(rnode);
	for (int i = 0;i < deletenum;i++)
	{
		maxdegreeP = MaxDegreePosition(rnode);
		rnode[maxdegreeP].attackrank = i;
		DeleteNode(rnode, maxdegreeP, G);
	}
	lastdeletenode = maxdegreeP;
}

void reset_attackrank(vector<node> &rnode)
{
	for (int i = 0;i < rnode.size();i++)
	{
		rnode[i].attackrank = -1;
	}
}