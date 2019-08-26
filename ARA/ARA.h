#ifndef _ARA_H
#define _ARA_H
#define alpha 0.9
#include"vector"
using namespace std;
typedef struct node
{
	int degree = 0;//存储节点的度
	int crruentdegree = 0;//存储当前的度
	int attackrank = -1;//存储被攻击次序
	int activation = 0;//激活开关
	int degreebackup = 0;
	double position[2];//存储位置
	int checkdegree=0;//用于最后检验度是否改变
	int difdegree = 0;//存储degree和crruentdegree的差值
}node;

void initilizationBA(vector<node> &rnode, vector<vector<int>> &G);//initilization.cpp
void backupnet(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);

void attack(vector<node> &rnode, vector<vector<int>> &G, double per);//attack.cpp
void Delete_Node(vector<node> &rnode, vector<vector<int>> &G, int p);

void attack2(vector<node> &rnode, vector<vector<int>> &G, int deletenum, int &lastdeletenode);//attack2.cpp
void reset_attackrank(vector<node> &rnode);

bool xiu2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);//rebuild.cpp
void recovernet(vector<vector<int>> &G, vector<vector<int>> &Gbackup);
bool choosenode1(int &changenode, vector<int> &atked1, vector<vector<int>> &Gbackup);
void choosenode2(int &changenode2, vector<int> &atked2);
void rebuildnode(vector<node> &rnode);
void delete_node_from_atk(int &deletenode, vector<int> &atk);
void find_neibor(int &changenode, vector<int> &changenodeneibor, vector<vector<int>> &Gbackup);
bool judge_node(int &changenode2, vector<int> &neibor, vector<vector<int>> &Gbackup, int &neibornode, int &changenode, int &neibornode2);
bool judge_node_1(int &changenode, int &changenode2, vector<vector<int>> &Gbackup, int &neibornode2);

//void rebuild2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup, int lastdeletenode);//rebuild2.cpp

double compute(vector<node> &rnode, vector<vector<int>> &G);//computeR.cpp
int MaxDegreePosition(vector<node> &rnode);
void calculate_degree(vector<node> &rnode, vector<vector<int>> &G);
void DeleteNode(vector<node> &rnode, int p, vector<vector<int>> &G);
int MaxConnectedCluster(vector<node> &rnode, vector<vector<int>> &G);
bool whether_search_end(vector<int> &search, vector<node> &rnode);
int Include_Nodes(int p, vector<vector<int>> &G, vector<int> &search, vector<node> &rnode);
void copynet(vector<vector<int>> &G, vector<vector<int>> &G2);
void copynode(vector<node> &rnode1, vector<node> &rnode2);
void backupdegree(vector<node> &rnode);
bool checkdegree(vector<node> rnode);

void output_compute_image(vector<node> &rnode, vector<vector<int>> &G);//output.cpp

void reconstruction(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);//reconstruction.cpp
void calculate_crruentdegree(vector<node> &rnode, vector<vector<int>> &G);
bool R_choosenode(vector<int> &restnode, int x, int &pp, vector<vector<int>> &G);
bool R_choosenode2(vector<int> &attackednode, int x, int &pp, vector<vector<int>> &G);

bool xiu1(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup, int &lastdeletenode);//xiu1.cpp
void chooseneibornode(int &targetnodeneibornode, int &attackednodeneibornode, int &attackednodeP, vector<vector<int>> &Gbackup, vector<int> &attackednode, vector<int> &targetnodeneibors, vector<node> &rnode);
bool judgement(vector<int> &attackednodeneibor, int nodep, vector<vector<int>> &Gbackup);

bool xiu3(vector<vector<int>> &restG, vector<node> &rnode, vector<vector<int>> &Gbackup);//exchange.cpp
bool choosenode2and3(vector<int> &restnodeexistedge, vector<vector<int>> &Gbackup, vector<vector<int>> &restG, vector<node> &rnode, int &node1, int &node2, int &node3,int &node4);
bool choosenode3(int &node2, int &node3, vector<int> &node3listbackup, vector<vector<int>> &Gbackup, vector<int> node1neibor, vector<node> &rnode, int &node4);

int findslope(vector<node> &rnode, vector<vector<int>> &G);//findslpoe.cpp

void swap1(vector<vector<int>> &G);//swap1.cpp

bool swap2(vector<vector<int>> &G, vector<node> &rnode);//swap2.cpp

void reconnect1(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);//reconnect.cpp
int Find_Attack_Node(vector<node> rnode, int attacknum);
void Updata_Damagenode(vector<node> rnode, vector<int> &damagenode, vector<vector<int>> &G, int attacknodeP);
void Updata_attacknodeneibor(vector<node> rnode, vector<vector<int>> &Gbackup, int attacknodeP, vector<int> &attacknodeneibor, vector<vector<int>> &G);
bool judge_connect(int ablenode, vector<int> attacknodeneibor, vector<vector<int>> &Gbackup, vector<vector<int>> &G);

void reconnect2(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);//reconnect2.cpp
void updata_targetnodeneibor(vector<node> &rnode, vector<vector<int>> &Gbackup, vector<int> &targetnodeneibor, int targetnode, vector<vector<int>> &G);
bool judge_seizenode(int seizenode, vector<vector<int>> &Gbackup, vector<vector<int>> &G, vector<node> &rnode, vector<int> &targetnodeneibor, int targetnode);

void reconnect3(vector<node> &rnode, vector<vector<int>> &G, vector<vector<int>> &Gbackup);//reconnect3.cpp
bool check_available(int curnode, vector<vector<int>> &Gbackup, vector<vector<int>> &G, int targetnode, vector<node> &rnode, vector<int> restnode);
void updata_difdegree(vector<node> &rnode);

void print_network(vector<vector<int>> G, int gen, int pi, int nettype, int cycnum);//print_network.cpp

double mainloop();//main.cpp
#endif