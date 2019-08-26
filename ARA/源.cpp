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
vector<double> Rinitial;
vector<double> Rres;
vector<vector<int>> sucnumber;
vector<int> degrees;
vector<int> middegrees;
vector<bool> degreedistribution;
int cycnum = 0;
string realworldline;
using namespace std;
//修1：xiu1
//修2: xiu2
//修3: xiu3
//重1：reconnect1
//重2：reconnect2
void main()
{
	double RR = 0;
	double Rin=0;
	double variance = 0;
	int Agen = 1;
	sucnumber.resize(Agen, vector<int>(5, 0));
	vector<double> resultR(Agen);
	for (int i = 0;i < Agen;i++)
	{
		cycnum = i;
		resultR[i] = mainloop();
		RR = RR + resultR[i];
	}
	RR = (double)RR / Agen;
	for (int i = 0;i < Agen;i++)
	{
		printf("the initial R is %f ", Rinitial[i]);
		printf("the final R is %f ", Rres[i]);
		printf("the sucnumber is ");
		for (int j = 0;j < sucnumber[i].size();j++)
		{
			printf(" %d ", sucnumber[i][j]);
		}	
//		printf("the middegree and final degree is %d , %d ",middegrees[i], degrees[i]);
		if (degreedistribution[i]==false)
		{
			printf("the degree has changed......%d !", degrees[i]);
		}
		else
		{
			printf("the degree hasn't change");
		}
		printf("\n");
	}
	for (int i = 0;i < Agen;i++)
	{
		Rin = Rin + Rinitial[i];
	}
	Rin = Rin / Agen;
	for (int i = 0;i < Agen;i++)
	{
		variance += pow(RR - resultR[i], 2);
	}
	variance = pow(variance, 0.5);
	printf("the average initial R is %f \n", Rin);
	printf("the variance is %f\n", variance);
	printf("the final res is %f", RR);
	cin >> RR;
}
double mainloop()
{
	srand(cycnum);
	int N = 500;//网络大小
	int rnodesnum = 25;//种群大小
	int maxGp = 0;//最优网络位置
	int countnum = 0;
	int gen = 40;
	int pi = 2;
	int gen2 = 2;
	int gencomb = 10;
	int gencomb2 = 40;
	int gencomb3 = 40;
	int sucnum = 0;
	int sucnumber1 = 0, sucnumber2 = 0;
	double midR = 0;
	double p = 0;//退火法接受概率
	double deltaR = 0;
	double T = 0.1;
	double Tmin = 0.001;
	int aaa = 0;
	double Rmid = 0;
	int lastdeletenode = 0;


	ifstream translationresult("translationresult.txt");//读取真实网络文件
	char realworldgraph;
	int invaliddata,jack=0;
	N = 0;
	realworldgraph = translationresult.get();
	while (realworldgraph != 10)
	{
		N++;
		realworldgraph = translationresult.get();
		printf("reading data %d\n", jack);jack++;
	}
	translationresult.seekg(0);
	

	double R1 = 0, R2 = 0;//存储网络R值
//	vector<double> RR1(rnodesnum);
//	vector<double> RR2(rnodesnum);
	double RRmax = 0;//当前种群最优R值
	double per = 0;//存储攻击比例
	vector<node> rnode(N);//创建节点
	vector<vector<node>> rnodes;
	vector<vector<int>> G;//创建邻接图
	vector<vector<int>> Gbackup;//创建备份邻接图
	vector<vector<int>> G2;
	vector<vector<int>> Gmid;
	vector<vector<vector<int>>> Gind;
	G.resize(N, vector<int>(N, 0));
	G2.resize(N, vector<int>(N, 0));
	Gbackup.resize(N, vector<int>(N, 0));
	Gmid.resize(N, vector<int>(N, 0));
//	Gind.resize(rnodesnum, vector<vector<int>>(N, vector<int>(N, 0)));
//	rnodes.resize(rnodesnum, vector<node>(N));
//	initilizationBA(rnode, G);//初始化BA网络

	//创建真实网络
	for (int i = 0, abama = 0, abama2 = 0;i < N;i++)
	{
		abama2 = 0;
		getline(translationresult, realworldline);
		for (int j = 0;j < N;j++)
		{
			G[i][j] = realworldline[abama2] - 48;
			printf("creating network %d\n", abama);abama++;
			abama2++;
		}
		abama++;
	}
	rebuildnode(rnode);
	calculate_degree(rnode, G);
	//
	

	backupnet(rnode, G, Gbackup);//备份网络
	print_network(G, gen, pi,1,cycnum);//打印初始网络
	R1 = compute(rnode, G);
	output_compute_image(rnode, G);
	backupdegree(rnode);
	std::cout << "the initial R is " << R1 << endl;
	Rinitial.push_back(R1);
	//开始迭代

	//重建1+2+修1+3+2
for (int ppi = 0;ppi < pi;ppi++)
{
	for (int i = 0;i < gen;i++)
	{
		for (int u = 2;u < rnode.size();u++)
		{
			//			for (int j = 0;j < 80;j++)
			//			{
			copynet(G, G2);
			copynet(G, Gbackup);
			rebuildnode(rnode);
			//攻击
			attack2(rnode, G, u, lastdeletenode);
			//恢复
			reconnect1(rnode, G, Gbackup);
			calculate_degree(rnode, G);
			rebuildnode(rnode);
			R2 = compute(rnode, G);
			//对比R
			if (R2 < R1)
			{
				copynet(G2, G);
			}
			else
			{
				R1 = R2;
				sucnumber[cycnum][0]++;
			}

			//生成下一代
			countnum++;
			printf("gen:%d, cycnum:%d , R: %f\n", countnum, cycnum, R1);
			//			}
		}
	}
	for (int i = 0;i < gen;i++)
	{
		for (int u = 2;u < rnode.size();u++)
		{
			for (int j = 0;j < 1;j++)
			{
				copynet(G, G2);
				copynet(G, Gbackup);
				rebuildnode(rnode);
				//攻击
				attack2(rnode, G, u, lastdeletenode);
				//恢复
				reconnect2(rnode, G, Gbackup);
				calculate_degree(rnode, G);
				rebuildnode(rnode);
				R2 = compute(rnode, G);
				//对比R
				if (R2 < R1)
				{
					copynet(G2, G);
				}
				else
				{
					R1 = R2;
					sucnumber[cycnum][1]++;
				}

				//生成下一代
				countnum++;
				printf("gen:%d, cycnum:%d , R: %f\n", countnum, cycnum, R1);
			}
		}
	}
	for (int i = 0;i < gen;i++)
	{
		for (int u = 2;u < rnode.size();u++)//为什么交换循环次序会发生优化性能急剧减小的情况
		{
			for (int j = 0;j < 1;j++)
			{
				copynet(G, G2);
				copynet(G, Gbackup);
				rebuildnode(rnode);
				attack2(rnode, G, u, lastdeletenode);
				if (xiu1(rnode, G, Gbackup, lastdeletenode))
				{
					rebuildnode(rnode);
					calculate_degree(rnode, G);
					R2 = compute(rnode, G);
					if (R2 < R1)
					{
						copynet(G2, G);
					}
					else
					{
						sucnumber[cycnum][2]++;
						R1 = R2;
					}
				}
				else
				{
					copynet(Gbackup, G);
					calculate_degree(rnode, G);
					break;
				}
				countnum++;
				printf("gen:%d, cycnum:%d , R: %f\n", countnum, cycnum, R1);
			}
		}
	}
	for (int i = 0;i < gen;i++)
	{
		for (int u = 2;u < rnode.size();u++)
		{
			for (int j = 0;j < 1;j++)
			{
				copynet(G, Gbackup);
				copynet(G, G2);
				rebuildnode(rnode);
				attack2(rnode, G, u, lastdeletenode);
				if (xiu3(G, rnode, Gbackup))
				{
					rebuildnode(rnode);
					calculate_degree(rnode, G);
					R2 = compute(rnode, G);
					if (R2 < R1)
					{
						copynet(G2, G);
					}
					else
					{
						R1 = R2;
						sucnumber[cycnum][3]++;
					}
				}
				else
				{
					copynet(Gbackup, G);
					calculate_degree(rnode, G);
					break;
				}
				countnum++;
				printf("gen:%d, cycnum:%d , R: %f\n", countnum, cycnum, R1);
			}
		}
	}
	for (int i = 0;i < gen;i++)//恢复被攻击节点部分结构
	{
		for (int u = 2;u < rnode.size();u++)
		{
			for (int j = 0;j < 1;j++)
			{
				copynet(G, G2);
				copynet(G, Gbackup);
				rebuildnode(rnode);
				//攻击
				attack2(rnode, G, u, lastdeletenode);
				//恢复
				xiu2(rnode, G, Gbackup);
				calculate_degree(rnode, G);
				rebuildnode(rnode);
				R2 = compute(rnode, G);
				//对比R
				if (R2 < R1)
				{
					copynet(G2, G);
				}
				else
				{
					R1 = R2;
					sucnumber[cycnum][4]++;
				}

				//生成下一代
				countnum++;
				printf("gen:%d, cycnum:%d , R: %f\n", countnum, cycnum, R1);
			}
		}
	}

}
	aaa = 0;
	for (int i = 0;i < rnode.size();i++)
	{
		aaa = aaa + rnode[i].degree;
	}
	degreedistribution.push_back(checkdegree(rnode));
	degrees.push_back(aaa);
	print_network(G, gen, pi, 2,cycnum);//打印结果
	std::cout << "the final R is " << R1 << " and " << Rmid << endl;
	Rres.push_back(R1);
	return R1;
}