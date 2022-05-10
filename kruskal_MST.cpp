#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include <functional>

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



//kruskal算法的K实现
class Kruskal
{
public:
	unordered_map<Node*, list<Node*>> Kru_map;//表示某节点属于那个集合

	//构建我的map,表示每个节点属于的集合，初始状态是每个节点属于一个单一的集合
	void Myset(list<Node*> nodes)//需要传入所有的节点
	{
		for (Node* cur : nodes)
		{
			list<Node*> node_from_set;
			node_from_set.push_back(cur);
			Kru_map.insert(pair<Node*, list<Node*>>(cur,node_from_set));
		}
	}

	//判断两个节点是否是一个集合
	bool is_same_set(Node* from, Node* to)
	{
		list<Node*> from_set = Kru_map.find(from)->second;
		list<Node*> to_set = Kru_map.find(to)->second;
		return from_set == to_set;
	}

	//合并from节点和to节点所在的节点
	void Union(Node* from, Node* to)
	{
		list<Node*> from_set = Kru_map.find(from)->second;
		list<Node*> to_set = Kru_map.find(to)->second;
		for (auto cur : to_set)
		{
			from_set.push_back(cur);
			Kru_map[cur] = from_set;//更新原来to_set集合中的节点所在集合的地址
		}
	}
};




/***************最小生成树，主体函数***************/
//构建小根堆比较器
bool cmp(Edge* E1, Edge* E2)
{
	return E1->weight > E2->weight;
}

set<Edge*> Kruskal_MST(GraphF graph)
{
	Kruskal KK;
	set<Edge*> res;
	//根据图的结果，把所有的节点提出来，为了输入Myset函数
	list<Node*> cur_nodes;
	for (auto n : graph.nodes)
	{
		cur_nodes.push_back(n.second);//所有node组成的集合
	}

	//构建map
	KK.Myset(cur_nodes);

	//构建优先队列，让边根据权值升序排列，队首最小
	priority_queue<Edge*,vector<Edge*>,decltype(&cmp)> pri_que(cmp);
	for (auto e : graph.edges)
	{
		pri_que.push(e);
	}

	while (!pri_que.empty())
	{
		Edge* cur_edge = pri_que.top();
		pri_que.pop();
		Node* from_node = cur_edge->from;
		Node* to_node = cur_edge->to;
		if (!KK.is_same_set(from_node, to_node))
		{
			res.insert(cur_edge);
			KK.Union(from_node, to_node);
		}
	}
	return res;	
}
