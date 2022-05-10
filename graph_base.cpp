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

/*
[
	[0,1,7],
	[1,2,5],
	[2,3,7],
	[3,1,8]
]
��һ�б�ʾ�����ڵ�
�ڶ��б�ʾ��β�ڵ�
�����б�ʾ�����ڵ�ֱ�ӱߵ�Ȩ��
*/
//���ϱߵ�ͼ�ṹ����ת��Ϊ���Ƕ����ͼ�ṹ����

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