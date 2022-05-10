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


vector<Node*> topo_sorting(GraphF graph)
{
	//第一个参数表示节点，第二个点表示该节点的剩余入度
	unordered_map<Node*, int> in_MAP;
	queue<Node*> zero_in_set;//入度为零的节点的集合
	for (auto n : graph.nodes)
	{
		if (n.second->in == 0)
			zero_in_set.push(n.second);
		else
			in_MAP.insert(pair<Node*, int>(n.second,n.second->in));
	}
	vector<Node*> res;
	while (!zero_in_set.empty())
	{
		Node* cur = zero_in_set.front();//去除一个入度为零的节点
		//处理函数
		res.push_back(cur);//拓扑排序结果
		zero_in_set.pop();
		for (auto n : cur->nexts)//去除入度为零的节点的影响，节点的关联节点入度减1
		{
			in_MAP[n] = n->in--;//更新关联节点的入度，直接insert不能完成更新
			if (in_MAP.find(n)->second == 0)
				zero_in_set.push(n);
		}
	}
	return res;

}