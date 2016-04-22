//下面的是一般是无向图
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Graph{
private:
	int n;	//顶点数量
	vector<int> *edges;	//邻接表
	bool *visited;	//记录结点是否已经访问过了
public:
	Graph(int input_n){
		n = input_n;
		edges = new vector<int>[n];
		//初始化visited指针
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
	//vertex:起点的编号
	void dfs(int vertex){
		cout<<vertex<<endl;
		visited[vertex] = true;	//标记为已访问
		//c++11可以写成下面的这一句
		//for (int adj_vertex:edges[vertex]) {	
		for (vector<int>::iterator it = edges[vertex].begin(); it != edges[vertex].end(); it++ ) {
		//遍历跟起点相邻的顶点，没被访问过就递归调用深度优先搜索
			if (!visited[*it]) {
				dfs(*it);
			}
		}
	}
};

int main(){
	int n, m, k;
	cout<<"请分别输入顶点数和边数"<<endl;
    cin >> n >> m;
    Graph g(n);
	cout<<"请分别输入无向边"<<endl;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g.insert(x, y);
    }
	cout<<"请输入遍历的起点"<<endl;
    cin >> k;
    g.dfs(k);
	return 0;
}
