#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

//定义一个较大的整形数
const int INF = 0x3f3f3f3f;

//边的定义，vertex:边的另外一个端点，weight:边的权值
struct Edge {
	int vertex, weight;
};

class Graph {
private:
	int n; //顶点个数
	vector<Edge> * edges; //邻接表
    bool * visited; //记录是否访问过了
public:
	int * dist; //这个用于保存从起点出发，到每个点的距离
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
		//外层循环是要找起点到n个顶点的最短路径
		for (int i = 0; i < n; i++) {
			int min_dist = INF, min_vertex;
			
			//循环从未访问结点中，从起点出发，距离起点最近的点
			//因为这里的dist是起点到每个顶点的距离
			for (int j = 0; j < n; j++) {
				//未访问且小于上一个记录最短距离
				if (!visited[j] && dist[j] < min_dist) {
					min_dist = dist[j];
					min_vertex = j;
				}
			}
			//标记为已访问
			visited[min_vertex] = 1;
			//其实就是更新当前min_vertex这个编号的点的周围结点的dist为最小的权值
			for(Edge &j : edges[min_vertex]){ 
				//当i=0时，就是第一次循环时，min_vertex就是下图的a点，下面就是更新a，e的距离为10，a，l的距离为5
				//而当i=2，min_vertex是下图的l点，min_dist = 5, j第一个遍历到e，min_dist + j.weight = 5 + 3 = 8 < 10 = dist[j.vertex]
				//所以更新起点a到e的最短距离
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
	//调用算法，起点到各点的最短路径都储存在数组中，下面将数组输出
	g.dijkstra(0);
	for (int i = 0; i < n; i++) {
		cout << i << ": " << g.dist[i] << endl;
	}
	return 0;
}