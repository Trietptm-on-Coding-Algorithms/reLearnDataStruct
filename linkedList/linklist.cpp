#include <iostream>

using namespace std;

//这里定义链表的结点
//链表的结点都是有数据域和指针域组成
class Node{
public:
	int data;	//数据域
	Node* next;	//指向下一结点，这样不就能连起来了吗
	//构造函数
	Node(int _data){
		data = _data;
        next = NULL;
	}
};

class LinkList{
private:
	Node* head;
public:
	//构造函数
	LinkList(){
		head = NULL;
	}
	//插入	node：插入的结点，index：要插入第几个结点的位置
	void insert(Node* node, int index){
		//链表是空的，也就是头指针是空的，直接将插入元素作为头节点，返回
		if(head == NULL){
            head = node;
            return;
		}
		//插入的位置是链表头
        if(index == 0){
			//先把要插入的结点的下一个结点指向原来的头节点head
            node->next = head;
			//再把插入结点更新为头节点
			head = node;
			return;
        }
		//对于一般情况，先找到插入（目标index）位置的前一个位置
			
		Node* current_node = head;	//指向当前结点，用于遍历结点
        int count = 0;	//统计遍历的结点数

		//循环语句的作用：找到index的前一个位置
		//count < index-1，因为count = index - 1就返回false，循环就退出了
		//current_node->next：当前结点的下一个结点，比如现在只有三个结点，你的index是5，这不可能插入吧。
		//显然循环到第三个结点时current_node->next就等于空，从而退出循环得了，从而下一个if语句他是不满足的
		while (current_node->next != NULL && count < index-1) {
			//current_node指向下一结点，
			current_node = current_node->next;
			count++;
		}
		//判断index是否超出链表长度，因为index大，上面的循环就会因为current_node->next == NULL 而退出，从而count<index-1
		if(count == index-1){
			//将node节点的下一个指向current_node的下一个结点
			node->next = current_node->next;
			//current_node的下一个结点指向node
			current_node->next = node;
        }
    }
	//遍历输出函数
	void output(){
		//链表为空，即头指针为空
		if (head == NULL) {
			return;
		}
		Node* current_node = head;
		while (current_node != NULL) {
			//输出当前结点的数据域
            cout<<current_node->data<<" ";
			//让指针指向下一结点
            current_node = current_node->next;
		}
        cout<<endl;
	}

	//删除结点的函数
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
		// 找目标位置的前一位
		while (current_node->next != NULL && count < index-1) {
			current_node = current_node->next;
			count++;
		}
		//index不能超出长度 而且不能删除最后一个结点的后一位，即current_node的下一个不能为空
		if (count == index-1 && current_node->next != NULL) {
			Node* delete_node = current_node->next;
            current_node->next = delete_node->next;
			//等价于 current_node->next = current_node->next->next; delete current_node->next; 
            delete delete_node;
		}
    }
	//翻转
	void reverse(){
		//列表为空就不翻
		if (head == NULL) {
			return;
		}
		Node *next_node, *current_node;
		//current_node初始化为头结点的下一个
		current_node = head->next;
		head->next = NULL;
		while (current_node != NULL) {
			//next_node保存当前结点的下一个结点
			next_node = current_node->next;
			//使current_node指向原头结点， 下一句是将current_node作为头节点，这样这个两的方向就相反了
			current_node->next = head;
            head = current_node;
			//最后让current_node移动到下一结点，继续两两反向
            current_node = next_node;
		}

		
	}
};



int main(){
	LinkList linklist;
	for (int i = 1; i <= 10; i++) {
		//新建一个结点
		Node *node = new Node(i);
		//插入位置从0开始哦
		linklist.insert(node, i-1);
	}
	//调用遍历输出函数
	linklist.output();
	//删除索引值为5的结点，再输出
	linklist.delete_node(5);
    linklist.output();
	//翻转
	linklist.reverse();
	linklist.output();
	return 0;
}