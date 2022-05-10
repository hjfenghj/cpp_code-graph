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


bool cmp(Edge* E1, Edge* E2)
{
	return E1->weight > E2->weight;
}

vector<Edge*> Prim_MST(GraphF graph)
{
	priority_queue<Edge*,vector<Edge*>,decltype(&cmp)> pri_que(cmp);//优先队列用来储存解锁的边
	set<Node*> used_nodes;//储存使用过的节点
	vector<Edge*> Reserved_edges;

	list<Node*> cur_nodes;
	for (auto n : graph.nodes)
	{
		cur_nodes.push_back(n.second);//所有node组成的集合
	}

	for (Node* N : cur_nodes)//处理森林的机制
	{
		if (used_nodes.find(N) == used_nodes.end())
		{
			used_nodes.insert(N);
		}
		for (Edge* E : N->edges)
		{
			pri_que.push(E);
		}

		while (!pri_que.empty())
		{
			Edge* cur_edge = pri_que.top();
			pri_que.pop();
			Node* edge_to = cur_edge->to;
			if (used_nodes.find(edge_to) == used_nodes.end())
			{
				Reserved_edges.push_back(cur_edge);
				used_nodes.insert(edge_to);
				for (Edge* E : edge_to->edges)
				{
					pri_que.push(E);
				}
			}
		}
	}
	return Reserved_edges;

}