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
	int value;//�ڵ��ֵ���������κ����ͣ���ʾ�ýڵ��ŵ�����
	int in;//���
	int out;//����
	list<Node*> nexts;//��ڵ����ڵĽڵ㼯��
	list<Edge*> edges;//���ڽڵ�ıߵļ��ϣ���ʾ�Ǹ����ǴӸýڵ��ȥ��
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
	Edge(int w, Node* N1, Node* N2)//��Ϊ��Ҫ����Node����࣬������Ҫ�ٴ����м���
								  //һ��û�н��ܲ����Ĺ��캯������Ȼ�������
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
	unordered_map<int, Node*> nodes;//�㼯,��һ��������ʾ�ڼ����ڵ�
	unordered_set<Edge*> edges;//�߼�
	GraphF() {};//���ڶ���GraphF�����
};


bool cmp(Edge* E1, Edge* E2)
{
	return E1->weight > E2->weight;
}

vector<Edge*> Prim_MST(GraphF graph)
{
	priority_queue<Edge*,vector<Edge*>,decltype(&cmp)> pri_que(cmp);//���ȶ���������������ı�
	set<Node*> used_nodes;//����ʹ�ù��Ľڵ�
	vector<Edge*> Reserved_edges;

	list<Node*> cur_nodes;
	for (auto n : graph.nodes)
	{
		cur_nodes.push_back(n.second);//����node��ɵļ���
	}

	for (Node* N : cur_nodes)//����ɭ�ֵĻ���
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