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

/*
[
	[0,1,7],
	[1,2,5],
	[2,3,7],
	[3,1,8]
]
第一列表示出发节点
第二列表示结尾节点
第三列表示两个节点直接边的权重
*/
//将上边的图结构描述转换为我们定义的图结构描述

GraphF trans_Graph(vector<vector<int>>& matrix)
{
	GraphF graph;
	for (int k = 0; k < matrix.size(); k++)
	{
		int from = matrix[k][0];
		int to = matrix[k][1];
		int weight = matrix[k][2];
		Node newfromNode(from);
		Node newtoNode(to);

		if (graph.nodes.find(from) == graph.nodes.end())
			graph.nodes.insert(pair<int, Node*>(from, &newfromNode));
		if (graph.nodes.find(to) == graph.nodes.end())
			graph.nodes.insert(pair<int, Node*>(to, &newtoNode));

		auto fromNode = graph.nodes.find(from);
		auto toNode = graph.nodes.find(to);

		(*fromNode).second->nexts.push_back(toNode->second);
		(*fromNode).second->out++;
		(*toNode).second->in++;
		Edge new_edge(weight, (*fromNode).second, (*toNode).second);
		Edge* newedge = &new_edge;
		(*fromNode).second->edges.push_back(newedge);
		graph.edges.insert(newedge);
	}
	return graph;
}


int main()
{
	vector<vector<int>>  mat{ {0,1,7},{1,2,5},{2,3,7},{3,1,8} };
	GraphF G;

	G = trans_Graph(mat);
	cout << 1 << endl;
	return 0;
}