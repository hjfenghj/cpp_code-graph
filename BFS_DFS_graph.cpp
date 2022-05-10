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

//图结构转换函数 
GraphF trans_Graph()
{

}

//宽度优先遍历
void bfs_graph(Node* node)
{
	if (node == nullptr)
		return;
	queue<Node*>  que;
	set<Node*> H;
	que.push(node);
	H.insert(node);
	while (!que.empty())
	{
		Node* cur = que.front();
		que.pop();
		//处理函数
		cout << cur->value << endl;
		for (auto n : cur->nexts)
		{
			if (H.find(n) == H.end())
			{
				H.insert(n);
				que.push(n);
			}
		}
	}
}

void DFS_graph(Node* node)
{
	if (node == nullptr)
		return;
	stack<Node*> st;
	set<Node*> H;
	st.push(node);
	H.insert(node);
	//处理函数
	cout << node->value << endl;
	while (!st.empty())
	{
		Node* cur = st.top();
		st.pop();
		for (auto n : node->nexts)
		{
			if (H.find(n) == H.end())
			{
				H.insert(n);
				st.push(cur);
				st.push(n);
				//处理函数
				cout << n->value << endl;
			}
		}
	}
}