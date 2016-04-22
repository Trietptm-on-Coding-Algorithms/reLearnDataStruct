#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

//һ���ߵĽṹ
class Edge {
	//vertex:һ���ߵ���һ���˵�
	//weight:�ñ�Ȩ��
	int vertex, weight;
public:
	Edge(int input_v, int input_w){
		vertex = input_v;
		weight = input_w;
	}
	~Edge(){

	}
};

class Graph{
private:
	int n;
	bool *visited;
	vector<Edge> *edges;
public:
	//dist��distance��:�õ�����������ľ���
	int *dist;
	Graph(int input_n){
		n = input_n;
		edges = new vector<Edge>[n];
		dist = new int[n];
		memset(visited, 0, n * sizeof(bool));
		//��ʼ��ÿ��distΪ0x3f3f3f3f,���Ǹ�����������ʾ�����Զ
		memset(dist,0x3f, n * sizeof(int));
	}
	~Graph(){
		delete[] dist;
		delete[] visited;
		delete[] edges;
	}
	void insert(int x, int y, int weight) {
		Edge temp1(y, weight);
        edges[x].push_back(temp1);
		Edge temp2(x, weight);
        edges[y].push_back(temp2);
    }

	//v�����
	int prim(int v){
		//���岢��ʼ����ȨֵΪ0
		int total_weight = 0;
		//���������ľ���Ϊ0
		dist[v] = 0;
		for (int i = 0; i < n; i++) {
			int min_dist = INF, min_vertex;
			//��n������������Ķ���(��������)
			for (int j = 0; j < n; j++) {
				//��û���ʹ����Ҿ���С����С����
				if (!visited[j] && dist[j] < min_dist) {
					//������С����
					min_dist = dist[j];
					//������С�Ķ���ı��
					min_vertex = j;
				}
			}
			//������С���루Ȩֵ��
			total_weight += min_dist;
			//����Ϊ�ѷ���
            visited[min_vertex] = 1;
			//ö������������еı�
			/*for(Edge &j : edges[min_vertex]){
				//����ߵ���һ���˵�û���ʹ���ȨֵС�ھ���
                if(!visited[j.vertex] && j.weight < dist[j.vertex]){
					//�͸��������Ϊ�ߵ�Ȩֵ
                    dist[j.vertex] = j.weight;
                }
            }*/
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
    cout << g.prim(0) << endl;
    return 0;
}
