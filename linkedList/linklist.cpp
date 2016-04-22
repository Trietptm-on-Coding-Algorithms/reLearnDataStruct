#include <iostream>

using namespace std;

//���ﶨ������Ľ��
//����Ľ�㶼�����������ָ�������
class Node{
public:
	int data;	//������
	Node* next;	//ָ����һ��㣬��������������������
	//���캯��
	Node(int _data){
		data = _data;
        next = NULL;
	}
};

class LinkList{
private:
	Node* head;
public:
	//���캯��
	LinkList(){
		head = NULL;
	}
	//����	node������Ľ�㣬index��Ҫ����ڼ�������λ��
	void insert(Node* node, int index){
		//�����ǿյģ�Ҳ����ͷָ���ǿյģ�ֱ�ӽ�����Ԫ����Ϊͷ�ڵ㣬����
		if(head == NULL){
            head = node;
            return;
		}
		//�����λ��������ͷ
        if(index == 0){
			//�Ȱ�Ҫ����Ľ�����һ�����ָ��ԭ����ͷ�ڵ�head
            node->next = head;
			//�ٰѲ��������Ϊͷ�ڵ�
			head = node;
			return;
        }
		//����һ����������ҵ����루Ŀ��index��λ�õ�ǰһ��λ��
			
		Node* current_node = head;	//ָ��ǰ��㣬���ڱ������
        int count = 0;	//ͳ�Ʊ����Ľ����

		//ѭ���������ã��ҵ�index��ǰһ��λ��
		//count < index-1����Ϊcount = index - 1�ͷ���false��ѭ�����˳���
		//current_node->next����ǰ������һ����㣬��������ֻ��������㣬���index��5���ⲻ���ܲ���ɡ�
		//��Ȼѭ�������������ʱcurrent_node->next�͵��ڿգ��Ӷ��˳�ѭ�����ˣ��Ӷ���һ��if������ǲ������
		while (current_node->next != NULL && count < index-1) {
			//current_nodeָ����һ��㣬
			current_node = current_node->next;
			count++;
		}
		//�ж�index�Ƿ񳬳������ȣ���Ϊindex�������ѭ���ͻ���Ϊcurrent_node->next == NULL ���˳����Ӷ�count<index-1
		if(count == index-1){
			//��node�ڵ����һ��ָ��current_node����һ�����
			node->next = current_node->next;
			//current_node����һ�����ָ��node
			current_node->next = node;
        }
    }
	//�����������
	void output(){
		//����Ϊ�գ���ͷָ��Ϊ��
		if (head == NULL) {
			return;
		}
		Node* current_node = head;
		while (current_node != NULL) {
			//�����ǰ����������
            cout<<current_node->data<<" ";
			//��ָ��ָ����һ���
            current_node = current_node->next;
		}
        cout<<endl;
	}

	//ɾ�����ĺ���
	void delete_node(int index){
		if (head == NULL) {
			return;
		}
		Node* current_node = head;
        int count = 0;
		if (index == 0) {
			head = head->next;
            delete current_node;
            return;
		}
		// ��Ŀ��λ�õ�ǰһλ
		while (current_node->next != NULL && count < index-1) {
			current_node = current_node->next;
			count++;
		}
		//index���ܳ������� ���Ҳ���ɾ�����һ�����ĺ�һλ����current_node����һ������Ϊ��
		if (count == index-1 && current_node->next != NULL) {
			Node* delete_node = current_node->next;
            current_node->next = delete_node->next;
			//�ȼ��� current_node->next = current_node->next->next; delete current_node->next; 
            delete delete_node;
		}
    }
	//��ת
	void reverse(){
		//�б�Ϊ�վͲ���
		if (head == NULL) {
			return;
		}
		Node *next_node, *current_node;
		//current_node��ʼ��Ϊͷ������һ��
		current_node = head->next;
		head->next = NULL;
		while (current_node != NULL) {
			//next_node���浱ǰ������һ�����
			next_node = current_node->next;
			//ʹcurrent_nodeָ��ԭͷ��㣬 ��һ���ǽ�current_node��Ϊͷ�ڵ㣬����������ķ�����෴��
			current_node->next = head;
            head = current_node;
			//�����current_node�ƶ�����һ��㣬������������
            current_node = next_node;
		}

		
	}
};



int main(){
	LinkList linklist;
	for (int i = 1; i <= 10; i++) {
		//�½�һ�����
		Node *node = new Node(i);
		//����λ�ô�0��ʼŶ
		linklist.insert(node, i-1);
	}
	//���ñ����������
	linklist.output();
	//ɾ������ֵΪ5�Ľ�㣬�����
	linklist.delete_node(5);
    linklist.output();
	//��ת
	linklist.reverse();
	linklist.output();
	return 0;
}