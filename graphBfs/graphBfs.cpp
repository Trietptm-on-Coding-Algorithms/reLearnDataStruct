#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

class Graph{
private:
	int n;
	bool *visited;
	int *deep;
	vector<int> *edges;
public:
	Graph(int input_n){
		n = input_n;
		edges = new vector<int>[n];
		visited = new bool[n];
		memset(visited, 0, n);
		deep = new int[n];
		memset(deep, 0, sizeof(int)*n);
	}
	~Graph(){
		delete[] edges;
		delete[] visited;
		delete[] deep;
	}
	void insert(int x, int y){
		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	void bfs(int start_vertex){
		queue<int> bfs_queue;
		bfs_queue.push(start_vertex);
		visited[start_vertex] = true;
		while (!bfs_queue.empty()) {
			//获取队首元素的编号
			int vertex = bfs_queue.front();
			cout<<vertex<<endl;
			bfs_queue.pop();
			for (vector<int>::iterator it = edges[vertex].begin(); it != edges[vertex].end(); it++ ) {
				if (!visited[*it]) {
					visited[*it] = true;
					bfs_queue.push(*it);
				}
			}
		}
	}
	void getLength(int start_vertex){
		int length = 0;
		bool tmp = false;
		queue<int> bfs_queue;
		bfs_queue.push(start_vertex);
		visited[start_vertex] = true;
		deep[start_vertex] = 0;
		while (!bfs_queue.empty()) {
			int vertex = bfs_queue.front();
			bfs_queue.pop();
			for (vector<int>::iterator it = edges[vertex].begin(); it != edges[vertex].end(); it++ ) {
				if (!visited[*it]) {
					visited[*it] = true;
					deep[*it] = deep[vertex] + 1;
					bfs_queue.push(*it);
				}
			}
			tmp = false;
		}
	}
	int getDeep(int vertex){
		return deep[vertex];
	}
};

int main(){
	int n, m, k;
	int x, y;
    cin >> n >> m >> k;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        g.insert(x-1, y-1);
    }
	g.getLength(k-1);
	for (int j = 0; j < n; j++) {
		cout<<g.getDeep(j)<<endl;
	}
	
	return 0;
}
