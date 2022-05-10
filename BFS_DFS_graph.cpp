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

//ͼ�ṹת������ 
GraphF trans_Graph()
{

}

//������ȱ���
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
		//������
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
	//������
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
				//������
				cout << n->value << endl;
			}
		}
	}
}