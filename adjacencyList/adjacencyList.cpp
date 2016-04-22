#include <iostream>
using namespace std;

//������
class LinkedListNode{
public:
	//vertex:�������ֵ
	int vertex;
	//ָ����һ������ָ��
	LinkedListNode *next;
	LinkedListNode(int vertex_input){
		vertex = vertex_input;
		next = NULL;
	}
};

//����
class LinkedList{
public:
	LinkedListNode *head;

	LinkedList(){
		head = NULL;
	}

	~LinkedList(){
		//˳��������
		while (head != NULL) {
			LinkedListNode *delete_node = head;
			head = head->next;
			delete delete_node;
		}
	}
	//���뺯��������ֱ�Ӳ嵽ͷ��ǰ����
	void insert(int vertex){
		LinkedListNode *node = new LinkedListNode(vertex);
		node->next = head;
		head = node;
	}
};

//ͼ
class Graph{
private:
	//���������ָ��
	LinkedList *edges;
	//n:������Ŀ
	int n;
public:
	Graph(int input_n){
		n = input_n;
		edges = new LinkedList[n];
	}
	~Graph(){
		delete[] edges;
	}
	
	//����͵�������Ĳ���
	void insert(int x, int y) {
		edges[x].insert(y);
    }
	
	//ѭ�����ÿ�������ÿ������ֵ����
    void output() {
		for (int i = 0; i < n; i++) {
			cout<<i<<":";
			//auto �� C++11 �������ԣ��ڶ������ʱ����ָ�����ͣ���������ͨ�������Ƶ��õ�ʵ�ʵ�����
			//������vc++6.0�����Բ�֧��
			//for (auto* j = edges[i].head; j != NULL; j = j->next) {
			for (LinkedListNode* j = edges[i].head; j != NULL; j = j->next) {
				cout<<j->vertex<<" ";
			}
			cout<<endl;
		}
    }
};

int main(){
	int n, m, x, y;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        g.insert(x, y);
    }
    g.output();
	return 0;
}