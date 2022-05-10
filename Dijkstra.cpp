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


//�ӽڵ�head�����������ڵ�ıߵ���Сֵ
//��Ŀ�������ڰ����ۼӺ�Ϊ�����Ļ���ͼ
unordered_map<Node*, int> DijKstra(Node* head)
{
	unordered_map<Node*,int> res;//�����head������ͼ�����������С��Ȩ�غͣ�
	                             //���ĳ��������map�У�˵��head���ܵ���ýڵ�
	set<Node*> used_nodes; //�����Ѿ�ѡ���Ľڵ�;
	res.emplace(head, 0);//��ʼmap���׽ڵ㵽�׽ڵ�ıߵ�Ȩ��Ϊ0;

	Node* cur_node = get_dis_noused_node(res, used_nodes);//��Ѱhead��Ŀǰ�ܵ���Ľڵ��У���ûȥ���Ľڵ��о���С��
	while (!cur_node)
	{
		for (Edge* E : cur_node->edges)
		{
			Node* to_node = E->to;
			//����Ȩ��
			if (used_nodes.find(to_node) == used_nodes.end())
			{
				res.emplace(to_node, E->weight + res[cur_node]);//res[cur_node]��ʾhead�ڵ㵽cur_node�ڵ��Ȩ�أ�����ʹ��res[E->from]
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