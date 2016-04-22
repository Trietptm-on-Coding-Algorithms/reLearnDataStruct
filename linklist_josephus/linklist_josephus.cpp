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
			//ѭ������ֻ��һ�����ʱ���Լ�����һ�������Լ�
            head->next = head;
            return;
        }
        if (index == 0) {
			//index==0,node�������ͷ��head����β��
            node->next = head->next;	//��node����һ����ԭ��head����һ��
            head->next = node;			//head����һ����node(�µ�ͷ)�������ӵ�ѭ���Ͳ������
            return;
        }
		//���ӵ�һ����ʼ����Ϊ����head�ѳ�β��
        Node *current_node = head->next;
        int count = 0;
		//current_node�������head�����ǵ�β�ˣ�ֻʣһ��Ԫ���ˣ��Ǹ���������Ҫ�ҵ�
        while (current_node != head && count < index - 1) {
            current_node = current_node->next;
            count++;
        }
        if (count == index - 1) {
			//����Ҫ������ָ�� current_node������λ�õ�ǰһ������������һ��
            node->next = current_node->next;
			//current_node������λ�õ�ǰһ��������һ��ָ��node
            current_node->next = node;
        }
		//��������뵽β�����棬head�����ﵱ��β���ĺ�����node����ô��headָ��node
        if (node == head->next) {
            head = node;
        }
    }
    void output_josephus(int m){
        Node* current_node = head;
		//��current_node->next����current_node����ֻʣһ����㣬���������ҵģ�����Ҫ�Ѳ�����Ϊѭ������������
        while (current_node->next != current_node) {
			//������m-1�����˳����Ǹ�Ԫ��������Ҫɾ��Ԫ�ص�ǰһ��Ԫ��
            for (int i = 1; i < m; i++) {
				current_node = current_node->next;
			}
			//���Ҫɾ��Ԫ�ص�������
            cout<<current_node->next->data<<" ";
			//��delete_node����Ҫɾ���Ľ�㣬�Ա��ͷ����ڴ�
            Node* delete_node = current_node->next;
			//�����ɾ�����Ĳ���
			current_node->next = current_node->next->next;
            delete delete_node;
		}
		cout<<endl<<endl;
		//�������Ҫ�ҵ��Ǹ�����ɾʣ�����һ��
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
