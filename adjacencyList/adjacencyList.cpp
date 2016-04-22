#include <iostream>
using namespace std;

//链表结点
class LinkedListNode{
public:
	//vertex:链表结点的值
	int vertex;
	//指向下一个结点的指针
	LinkedListNode *next;
	LinkedListNode(int vertex_input){
		vertex = vertex_input;
		next = NULL;
	}
};

//链表
class LinkedList{
public:
	LinkedListNode *head;

	LinkedList(){
		head = NULL;
	}

	~LinkedList(){
		//顺着链析构
		while (head != NULL) {
			LinkedListNode *delete_node = head;
			head = head->next;
			delete delete_node;
		}
	}
	//插入函数，这里直接插到头的前面了
	void insert(int vertex){
		LinkedListNode *node = new LinkedListNode(vertex);
		node->next = head;
		head = node;
	}
};

//图
class Graph{
private:
	//储存链表的指针
	LinkedList *edges;
	//n:顶点数目
	int n;
public:
	Graph(int input_n){
		n = input_n;
		edges = new LinkedList[n];
	}
	~Graph(){
		delete[] edges;
	}
	
	//插入就调用链表的插入
	void insert(int x, int y) {
		edges[x].insert(y);
    }
	
	//循环输出每个链表的每个结点的值即可
    void output() {
		for (int i = 0; i < n; i++) {
			cout<<i<<":";
			//auto 是 C++11 的新特性，在定义变量时无需指定类型，编译器会通过类型推导得到实际的类型
			//但我用vc++6.0，所以不支持
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