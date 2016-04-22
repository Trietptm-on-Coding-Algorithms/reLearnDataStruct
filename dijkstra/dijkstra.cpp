#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

//����һ���ϴ��������
const int INF = 0x3f3f3f3f;

//�ߵĶ��壬vertex:�ߵ�����һ���˵㣬weight:�ߵ�Ȩֵ
struct Edge {
	int vertex, weight;
};

class Graph {
private:
	int n; //�������
	vector<Edge> * edges; //�ڽӱ�
    bool * visited; //��¼�Ƿ���ʹ���
public:
	int * dist; //������ڱ��������������ÿ����ľ���
	Graph (int input_n) {
		n = input_n;
		edges = new vector<Edge>[n];
		dist = new int[n];
        visited = new bool[n];
        memset(visited, 0, n);
		memset(dist, 0x3f, n * sizeof(int));
	}
	~Graph() {
		delete[] dist;
		delete[] edges;
        delete[] visited;
	}
    void insert(int x, int y, int weight) {
        edges[x].push_back(Edge{y, weight});
        edges[y].push_back(Edge{x, weight});
    }
    void dijkstra(int v) {
		dist[v] = 0;
		//���ѭ����Ҫ����㵽n����������·��
		for (int i = 0; i < n; i++) {
			int min_dist = INF, min_vertex;
			
			//ѭ����δ���ʽ���У����������������������ĵ�
			//��Ϊ�����dist����㵽ÿ������ľ���
			for (int j = 0; j < n; j++) {
				//δ������С����һ����¼��̾���
				if (!visited[j] && dist[j] < min_dist) {
					min_dist = dist[j];
					min_vertex = j;
				}
			}
			//���Ϊ�ѷ���
			visited[min_vertex] = 1;
			//��ʵ���Ǹ��µ�ǰmin_vertex�����ŵĵ����Χ����distΪ��С��Ȩֵ
			for(Edge &j : edges[min_vertex]){ 
				//��i=0ʱ�����ǵ�һ��ѭ��ʱ��min_vertex������ͼ��a�㣬������Ǹ���a��e�ľ���Ϊ10��a��l�ľ���Ϊ5
				//����i=2��min_vertex����ͼ��l�㣬min_dist = 5, j��һ��������e��min_dist + j.weight = 5 + 3 = 8 < 10 = dist[j.vertex]
				//���Ը������a��e����̾���
                if (min_dist + j.weight < dist[j.vertex]) {
					dist[j.vertex] = min_dist + j.weight;
                }
            }  

		}
    }
};

int main() {
	int n, m;
	cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.insert(a, b, c);
	}
	//�����㷨����㵽��������·���������������У����潫�������
	g.dijkstra(0);
	for (int i = 0; i < n; i++) {
		cout << i << ": " << g.dist[i] << endl;
	}
	return 0;
}