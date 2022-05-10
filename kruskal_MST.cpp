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



//kruskal�㷨��Kʵ��
class Kruskal
{
public:
	unordered_map<Node*, list<Node*>> Kru_map;//��ʾĳ�ڵ������Ǹ�����

	//�����ҵ�map,��ʾÿ���ڵ����ڵļ��ϣ���ʼ״̬��ÿ���ڵ�����һ����һ�ļ���
	void Myset(list<Node*> nodes)//��Ҫ�������еĽڵ�
	{
		for (Node* cur : nodes)
		{
			list<Node*> node_from_set;
			node_from_set.push_back(cur);
			Kru_map.insert(pair<Node*, list<Node*>>(cur,node_from_set));
		}
	}

	//�ж������ڵ��Ƿ���һ������
	bool is_same_set(Node* from, Node* to)
	{
		list<Node*> from_set = Kru_map.find(from)->second;
		list<Node*> to_set = Kru_map.find(to)->second;
		return from_set == to_set;
	}

	//�ϲ�from�ڵ��to�ڵ����ڵĽڵ�
	void Union(Node* from, Node* to)
	{
		list<Node*> from_set = Kru_map.find(from)->second;
		list<Node*> to_set = Kru_map.find(to)->second;
		for (auto cur : to_set)
		{
			from_set.push_back(cur);
			Kru_map[cur] = from_set;//����ԭ��to_set�����еĽڵ����ڼ��ϵĵ�ַ
		}
	}
};




/***************��С�����������庯��***************/
//����С���ѱȽ���
bool cmp(Edge* E1, Edge* E2)
{
	return E1->weight > E2->weight;
}

set<Edge*> Kruskal_MST(GraphF graph)
{
	Kruskal KK;
	set<Edge*> res;
	//����ͼ�Ľ���������еĽڵ��������Ϊ������Myset����
	list<Node*> cur_nodes;
	for (auto n : graph.nodes)
	{
		cur_nodes.push_back(n.second);//����node��ɵļ���
	}

	//����map
	KK.Myset(cur_nodes);

	//�������ȶ��У��ñ߸���Ȩֵ�������У�������С
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
