#include <iostream>
#include <stdlib.h>
using namespace std;

class DisjointSet{
private:
	//这个用来储存每个元素的父亲是第几个元素
	int* father, *rank;
public:
	//构造函数
	//size为元素的个数
	//一开始时，每个元素自己组成一个集合（就集合中只有自己一个元素），
	//那么下面father[i] = i，就是让父亲为他们自己
	DisjointSet(int size){
		father = new int[size];
		rank = new int[size];
		for (int i = 0; i < size; i++) {
			father[i] = i;
			rank[i] = 0;
		}
	}
	~DisjointSet(){
		delete[] father;
		delete[] rank;
	}
	//路径压缩优化了的
	int find_set(int node){
		//就是使node的父亲就是代表元素
		if (father[node] != node) {
			father[node] = find_set(father[node]);
		}
		return father[node];
	}
	bool merge(int node1, int node2){
		int ancestor1 = find_set(node1);
		int ancestor2 = find_set(node2);
		if (ancestor1 != ancestor2) {
			//按秩合并优化
			//如果ancestor1的孩子较多，就交换
			if (rank[ancestor1] > rank[ancestor2]) {
				swap(ancestor1, ancestor2);
			}
			father[ancestor1] = ancestor2; 
			//更新ancestor2的孩子数
			rank[ancestor2] = (rank[ancestor1]+1) > rank[ancestor2] ? (rank[ancestor1]+1):rank[ancestor2];
			return true;
		}
		return false;
	}
};

int main(){
	int n, m, x, y, count;
	cin>>n;
	count = n;
	DisjointSet dsu(n);
	cin>>m;
	for (int i = 0; i < m; i++) {
		cin>>x>>y;
		bool ans = dsu.merge(x,y);
		if (ans) {
			count--;
			cout<<"success"<<endl;
		}else{
			/cout<<"failed"<<endl;
		}
	}
	cout<<count<<endl;
	return 0;
}