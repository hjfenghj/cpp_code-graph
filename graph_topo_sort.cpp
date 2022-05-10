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


vector<Node*> topo_sorting(GraphF graph)
{
	//��һ��������ʾ�ڵ㣬�ڶ������ʾ�ýڵ��ʣ�����
	unordered_map<Node*, int> in_MAP;
	queue<Node*> zero_in_set;//���Ϊ��Ľڵ�ļ���
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
		Node* cur = zero_in_set.front();//ȥ��һ�����Ϊ��Ľڵ�
		//������
		res.push_back(cur);//����������
		zero_in_set.pop();
		for (auto n : cur->nexts)//ȥ�����Ϊ��Ľڵ��Ӱ�죬�ڵ�Ĺ����ڵ���ȼ�1
		{
			in_MAP[n] = n->in--;//���¹����ڵ����ȣ�ֱ��insert������ɸ���
			if (in_MAP.find(n)->second == 0)
				zero_in_set.push(n);
		}
	}
	return res;

}