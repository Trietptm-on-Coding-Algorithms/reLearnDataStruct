#include <iostream>
#include <cstring>
using namespace std;

class Graph{
private:
	int **mat;	//邻接矩阵,其实就是二维数组
	int n;	//顶点个数
public:
	Graph(int input_n){
		n= input_n;
		//先分配n个int*的指针，再对每个指针再循环分配
		mat = new int*[n];
		for (int i = 0; i < n; i++) {
			mat[i] = new int[n];
			//将内存中mat[i]的sizeof(int)*n个字节的内容全部设置为那个字符的ASCII值(这里的字符好似0)
			//它是对较大的结构体或数组进行清零操作的一种最快方法
			memset(mat[i], 0, sizeof(int)*n);//Sets buffers to a specified character.
		}
	}
	~Graph(){
		//析构时注意先析构里面的，再外层的
		for (int i = 0; i < n; i++) {
			delete[] mat[i];
		}
		delete[] mat;
	}
	//插入边，直接将对于的位置置为1就可以了
	void insert(int x, int y){
		mat[x][y] = 1;
	}
	//输出邻接矩阵
	void output(){
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout<<mat[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	int getRenQi(int k){
		int follow = 0, fllowed = 0;
		for (int i = 0; i < n; i++) {
			follow += mat[k][i];
		}
		for (int j = 0; j < n; j++) {
			fllowed += mat[j][k];
		}
		return fllowed-follow;
	}

};

int main(){
	//n:顶点个数	m:有向边个数
	//x,y: 表示插入一条x连向y的有向边
	int n, m, x, y;
	cin >> n >> m;
	Graph g(n);
	for (int i = 0; i< m; i++) {
		cin >> x >> y;
		g.insert(x, y);
	}
	g.output();
	return 0;
}