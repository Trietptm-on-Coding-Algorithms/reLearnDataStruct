#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

//一个边的结构
class Edge {
	//vertex:一条边的另一个端点
	//weight:该边权重
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
	//dist（distance）:该点距离生成树的距离
	int *dist;
	Graph(int input_n){
		n = input_n;
		edges = new vector<Edge>[n];
		dist = new int[n];
		memset(visited, 0, n * sizeof(bool));
		//初始化每个dist为0x3f3f3f3f,这是个大整数，表示距离很远
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

	//v：起点
	int prim(int v){
		//定义并初始化总权值为0
		int total_weight = 0;
		//起点距离起点的距离为0
		dist[v] = 0;
		for (int i = 0; i < n; i++) {
			int min_dist = INF, min_vertex;
			//从n个点中找最近的顶点(离起点最近)
			for (int j = 0; j < n; j++) {
				//若没访问过，且距离小于最小距离
				if (!visited[j] && dist[j] < min_dist) {
					//更新最小距离
					min_dist = dist[j];
					//保存最小的顶点的编号
					min_vertex = j;
				}
			}
			//加上最小距离（权值）
			total_weight += min_dist;
			//设置为已访问
            visited[min_vertex] = 1;
			//枚举这个结点的所有的边
			/*for(Edge &j : edges[min_vertex]){
				//如果边的另一个端点没访问过且权值小于距离
                if(!visited[j.vertex] && j.weight < dist[j.vertex]){
					//就更新其距离为边的权值
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
