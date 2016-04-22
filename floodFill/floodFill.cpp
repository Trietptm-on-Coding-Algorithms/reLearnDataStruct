#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

class Graph{
private:
	int n;
	int *color;
	vector<int> *edges;
public:
	Graph(int input_n){
		n = input_n;
		edges = new vector<int>[n];
		color = new int[n];
		memset(color, 0, n*sizeof(int));
	}
	~Graph(){
		delete[] edges;
		delete[] color;
	}

	void insert(int x, int y){
		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	void floodfill(){
		//��ʾ��ǰ��Ⱦɫ��ֵ
		int color_cnt = 0, i = 0;
		for (i = 0; i < n; i++) {
			//color����0��˵��û��Ⱦɫ
			if (color[i] == 0) {
				color_cnt++;
				color[i] = color_cnt;
				queue<int> q;
				q.push(i);
				while (!q.empty()) {
					int vertex = q.front();
					for (vector<int>::iterator it = edges[vertex].begin(); it != edges[vertex].end(); it++ ) {
						//δȾɫ
						if (color[*it] == 0) {
							color[*it] = color_cnt;
							q.push(*it);
						}
					}
					q.pop();		
				}
			}
		}
		//��� ��� �� ��ɫֵ
		for (i = 0; i < n; i++) {
			cout << i << " " <<color[i] << endl;
		}
	}
};

int main(){
	int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g.insert(x, y);
    }
    g.floodfill();
    return 0;
}


















