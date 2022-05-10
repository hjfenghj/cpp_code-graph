#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<list>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class Edge;

class Node
{
public:
	int value;//节点的值，可以是任何类型，表示该节点存放的内容
	int in;//入度
	int out;//出度
	list<Node*> nexts;//与节点相邻的节点集合
	list<Edge*> edges;//属于节点的边的集合，表示那个边是从该节点出去的
	Node(int v)
	{
		value = v;
		in = 0;
		out = 0;
	}
	Node() { value = 0; in = 0; out = 0; }
};

class Edge
{
public:
	int weight;
	Node* from;
	Node* to;
	Edge(int w, Node* N1, Node* N2)//因为需要定义Node这个类，所以需要再从类中加上
								  //一个没有接受参数的构造函数，不然会出问题
	{
		weight = w;
		from = N1;
		to = N2;
	}
	//Edge() { weight = 0, from = nullptr; to = nullptr; }
};


class GraphF
{
public:
	unordered_map<int, Node*> nodes;//点集,第一个参数表示第几个节点
	unordered_set<Edge*> edges;//边集
	GraphF() {};//用于定义GraphF类对象
};


Node* get_dis_noused_node(unordered_map<Node*, int> res, set<Node*> used_nodes)
{
	int dis_flag =INT_MAX;
	Node* dis_node = nullptr;
	for (auto R : res)
	{
		if (used_nodes.find(R.first) == used_nodes.end())
		{
			if (R.second <= dis_flag)
				dis_node = R.first;
		}
	}
	return dis_node;
}


//从节点head出发到其他节点的边的最小值
//题目不能用在包含累加和为负数的环的图
unordered_map<Node*, int> DijKstra(Node* head)
{
	unordered_map<Node*,int> res;//储存从head出发到图中其他点的最小边权重和，
	                             //如果某个出现在map中，说明head不能到达该节点
	set<Node*> used_nodes; //表明已经选过的节点;
	res.emplace(head, 0);//初始map，首节点到首节点的边的权重为0;

	Node* cur_node = get_dis_noused_node(res, used_nodes);//找寻head能目前能到达的节点中，还没去过的节点中就最小的
	while (!cur_node)
	{
		for (Edge* E : cur_node->edges)
		{
			Node* to_node = E->to;
			//更新权重
			if (used_nodes.find(to_node) == used_nodes.end())
			{
				res.emplace(to_node, E->weight + res[cur_node]);//res[cur_node]表示head节点到cur_node节点的权重，不能使用res[E->from]
			}
			else
			{
				res[to_node] = min(res[to_node], res[to_node] + E->weight);
			}
		}
		used_nodes.insert(cur_node);
		cur_node = get_dis_noused_node(res, used_nodes);
	}
	return res;
}