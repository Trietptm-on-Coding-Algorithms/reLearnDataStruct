#include<iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node(int _data) {
        data = _data;
        next = NULL;
    }
};
class LinkList {
private:
    Node* head;
public:
    LinkList() {
        head = NULL;
    }
    void insert(Node *node, int index) {
        if (head == NULL) {
            head = node;
			//循环链表，只有一个结点时，自己的下一个就是自己
            head->next = head;
            return;
        }
        if (index == 0) {
			//index==0,node插入成了头，head成了尾，
            node->next = head->next;	//即node的下一个是原来head的下一个
            head->next = node;			//head的下一个是node(新的头)，这样子的循环就不会断了
            return;
        }
		//即从第一个开始，因为上面head已成尾了
        Node *current_node = head->next;
        int count = 0;
		//current_node如果等于head，就是到尾了，只剩一个元素了，那个就是我们要找的
        while (current_node != head && count < index - 1) {
            current_node = current_node->next;
            count++;
        }
        if (count == index - 1) {
			//我们要插入结点指向 current_node（插入位置的前一个）本来的下一个
            node->next = current_node->next;
			//current_node（插入位置的前一个）的下一个指向node
            current_node->next = node;
        }
		//如果结点插入到尾结点后面，head（这里当做尾）的后面是node，那么将head指向node
        if (node == head->next) {
            head = node;
        }
    }
    void output_josephus(int m){
        Node* current_node = head;
		//若current_node->next等于current_node，就只剩一个结点，就是我们找的，所以要把不等作为循环继续的条件
        while (current_node->next != current_node) {
			//数到第m-1个就退出，那个元素是我们要删除元素的前一个元素
            for (int i = 1; i < m; i++) {
				current_node = current_node->next;
			}
			//输出要删除元素的数据域
            cout<<current_node->next->data<<" ";
			//用delete_node保存要删除的结点，以便释放其内存
            Node* delete_node = current_node->next;
			//这个是删除结点的操作
			current_node->next = current_node->next->next;
            delete delete_node;
		}
		cout<<endl<<endl;
		//输出我们要找的那个，即删剩的最后一个
        cout<<current_node->data<<endl;
        delete current_node;
	}
};
int main() {
    LinkList linklist;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        Node *node = new Node(i);
        linklist.insert(node, i - 1);
    }
    linklist.output_josephus(m);
    return 0;
}
