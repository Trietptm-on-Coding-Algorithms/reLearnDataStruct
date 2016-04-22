#include <iostream>
#include <cstring>
using namespace std;

class Graph{
private:
	int **mat;	//�ڽӾ���,��ʵ���Ƕ�ά����
	int n;	//�������
public:
	Graph(int input_n){
		n= input_n;
		//�ȷ���n��int*��ָ�룬�ٶ�ÿ��ָ����ѭ������
		mat = new int*[n];
		for (int i = 0; i < n; i++) {
			mat[i] = new int[n];
			//���ڴ���mat[i]��sizeof(int)*n���ֽڵ�����ȫ������Ϊ�Ǹ��ַ���ASCIIֵ(������ַ�����0)
			//���ǶԽϴ�Ľṹ�������������������һ����췽��
			memset(mat[i], 0, sizeof(int)*n);//Sets buffers to a specified character.
		}
	}
	~Graph(){
		//����ʱע������������ģ�������
		for (int i = 0; i < n; i++) {
			delete[] mat[i];
		}
		delete[] mat;
	}
	//����ߣ�ֱ�ӽ����ڵ�λ����Ϊ1�Ϳ�����
	void insert(int x, int y){
		mat[x][y] = 1;
	}
	//����ڽӾ���
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
	//n:�������	m:����߸���
	//x,y: ��ʾ����һ��x����y�������
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