//�������һ��������ͼ
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Graph{
private:
	int n;	//��������
	vector<int> *edges;	//�ڽӱ�
	bool *visited;	//��¼����Ƿ��Ѿ����ʹ���
public:
	Graph(int input_n){
		n = input_n;
		edges = new vector<int>[n];
		//��ʼ��visitedָ��
		visited = new bool[n];
		memset(visited, 0, n);
	}
	~Graph(){
		delete[] edges;
		delete[] visited;
	}
	void insert(int x, int y){
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	//vertex:���ı��
	void dfs(int vertex){
		cout<<vertex<<endl;
		visited[vertex] = true;	//���Ϊ�ѷ���
		//c++11����д���������һ��
		//for (int adj_vertex:edges[vertex]) {	
		for (vector<int>::iterator it = edges[vertex].begin(); it != edges[vertex].end(); it++ ) {
		//������������ڵĶ��㣬û�����ʹ��͵ݹ���������������
			if (!visited[*it]) {
				dfs(*it);
			}
		}
	}
};

int main(){
	int n, m, k;
	cout<<"��ֱ����붥�����ͱ���"<<endl;
    cin >> n >> m;
    Graph g(n);
	cout<<"��ֱ����������"<<endl;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g.insert(x, y);
    }
	cout<<"��������������"<<endl;
    cin >> k;
    g.dfs(k);
	return 0;
}
