#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include"ARA.h"
#include"numeric"
using namespace std;
void print_network(vector<vector<int>> G,int gen ,int pi,int nettype,int cycnum)//将网络输出为gml格式,只有一个文件，一个网络！
{
	ofstream PrintNetwork;
	if (nettype == 1)
	{
		PrintNetwork.open("InitialNetwork.gml");
	}
	else
	{
		PrintNetwork.open("FinalNetwork.gml");
	}
	PrintNetwork << "Creator \" N=" << G.size() << " gen=" << gen << " pi=" << pi << " \"" << endl;
	PrintNetwork << "graph" << endl;
	PrintNetwork << "[" << endl;
	PrintNetwork << "  directed 0" << endl;
	for (int i = 0;i < G.size() ; i++)
	{
		PrintNetwork << "  node" << endl;
		PrintNetwork << "  [" << endl;
		PrintNetwork << "    id " << i << endl;
		PrintNetwork << "  ]" << endl;
	}
	for (int i = 0;i < G.size();i++)
	{
		for (int j = 0;j < G.size();j++)
		{
			if (G[i][j] == 1)
			{
				PrintNetwork << "  edge" << endl;
				PrintNetwork << "  [" << endl;
				PrintNetwork << "    source " << i << endl;
				PrintNetwork << "    target " << j << endl;
				PrintNetwork << "  ]" << endl;
				G[j][i] = 0;
			}
		}
	}
	PrintNetwork << "]" << endl;
	PrintNetwork.close();
}