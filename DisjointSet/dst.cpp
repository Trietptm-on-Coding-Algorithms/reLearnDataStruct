#include <iostream>
#include <stdlib.h>
using namespace std;

class DisjointSet{
private:
	//�����������ÿ��Ԫ�صĸ����ǵڼ���Ԫ��
	int* father, *rank;
public:
	//���캯��
	//sizeΪԪ�صĸ���
	//һ��ʼʱ��ÿ��Ԫ���Լ����һ�����ϣ��ͼ�����ֻ���Լ�һ��Ԫ�أ���
	//��ô����father[i] = i�������ø���Ϊ�����Լ�
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
	//·��ѹ���Ż��˵�
	int find_set(int node){
		//����ʹnode�ĸ��׾��Ǵ���Ԫ��
		if (father[node] != node) {
			father[node] = find_set(father[node]);
		}
		return father[node];
	}
	bool merge(int node1, int node2){
		int ancestor1 = find_set(node1);
		int ancestor2 = find_set(node2);
		if (ancestor1 != ancestor2) {
			//���Ⱥϲ��Ż�
			//���ancestor1�ĺ��ӽ϶࣬�ͽ���
			if (rank[ancestor1] > rank[ancestor2]) {
				swap(ancestor1, ancestor2);
			}
			father[ancestor1] = ancestor2; 
			//����ancestor2�ĺ�����
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