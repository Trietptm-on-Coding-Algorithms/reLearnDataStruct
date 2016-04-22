#include<iostream>
#include <string>
#include <algorithm>

using namespace std;
class Node {
public:
    int data;
	//father���Ǹ��׽�㣬����������һ������һ��
    Node *lchild, *rchild, *father;
    Node(int _data, Node *_father=NULL) {
        data = _data;
        lchild = NULL;
        rchild = NULL;
		father = _father;
    }
    ~Node() {
        if (lchild != NULL) {
            delete lchild;
        }
        if (rchild != NULL) {
            delete rchild;
        }
    }
	//���뺯��
	void insert(int value){
		//value�Ѿ��ڶ������ϣ�ֱ�ӷ���
		if (value == data) {
			return;
		//���ڵ�ǰ�������ݣ������������룬������������	
		}else if (value > data) {
			//������Ϊ�գ��Ͱ�value�����½�㣬���ڵ��ǵ�ǰ�Ľ��
			if (rchild == NULL) {
				rchild = new Node(value, this);
			}else{
			//����ݹ���ò��뺯��
				rchild->insert(value);
			}
		}else{
		//���������������߼���࣬����������������
			if (lchild == NULL) {
				lchild = new Node(value, this);
			}else{
				lchild->insert(value);
			}
		}
	}
	//���Һ���
	Node* search(int value){
		//value == data����ʾ���ҵ��ˣ����ص�ǰ���
		if (value == data) {
			return this;
		//���ڵ�ǰ��㣬������������	
		}else if (value > data) {
			//������Ϊ�գ��������ʧ��
			if (rchild == NULL) {
				return NULL;
			//����ݹ�����������ò���
			}else{
				return rchild->search(value);
			}
		}else{
		//���������������߼���࣬����������������
			if (lchild == NULL) {
				return NULL;
			}else{
				return lchild->search(value);
			}	
		}
	}
	//����ǰ��������˵�����������������ģ�
	Node* predecessor(){
		//������temp��������
		Node *temp = lchild;
		//��ǰ�Ľ��������Һ��Ӳ���Ϊ�գ��������ǲ��ܼ������ұ��������ֵ��Ľ��
		while (temp != NULL && temp->rchild != NULL) {
			//�������Һ��Ӳ���
			temp = temp->rchild;
		}
		//ѭ��������temp��������Ҫ�ҵ�ǰ��
		return temp;
	}
	//���Һ�̣�����˵����������������С�ģ�
	Node* successor(){
		//������temp�����Һ���
		Node *temp = rchild;
		//��ǰ�Ľ����������Ӳ���Ϊ�գ��������ǲ��ܼ������ұ��������ֵС�Ľ��
		while (temp != NULL && temp->lchild != NULL) {
			temp = temp->lchild;
		}
		//ѭ��������temp��������Ҫ�ҵĺ��
		return temp;
	}
	//ɾ����㣨ֻɾ����Ϊ0��1�Ľ�㣬�Ⱦ��Ƿ�֧����Ŀ��������ܷ����ɾ��ǰ���ͺ��
	void remove_node(Node *delete_node){
		//������¼��ǰ���ĺ��ӽ��
		Node *temp = NULL;
		//���Ҫɾ���Ľ������Ӳ�Ϊ��
		if (delete_node->lchild != NULL) {
			//�������ĸ���Ϊdelete_node�ĸ���
			temp = delete_node->lchild;
			temp->father = delete_node->father;
			//���Ұ�delete_node��������Ϊ��
			delete_node->lchild = NULL;
		}
		//���Ҫɾ���Ľ����Һ��Ӳ�Ϊ��
		if (delete_node->rchild != NULL) {
			//�������ĸ���Ϊdelete_node�ĸ���
			temp = delete_node->rchild;
			temp->father = delete_node->father;
			//���Ұ�delete_node���Һ�����Ϊ��
			delete_node->rchild = NULL;
		}
		//���delete_node�Ǹ��׵����ӣ������tempΪdelete_node�ĸ��׵����ӣ�����͸���Ϊ�Һ���
		if (delete_node->father->lchild == delete_node) {
			delete_node->father->lchild = temp;
		}else{
			delete_node->father->rchild = temp;
		}
		//���ɾ���ý��
		delete delete_node;
	}
	//ɾ����������valueֵ�Ľ�㣨ԭ���ǽ����ӽ���ֵ����value����ϵ�ֵ��
	bool delete_tree(int value){
		//delete_node��Ҫɾ���Ľ��
		//current_node����ǰ��㣨valueֵ�ģ�
		Node *delete_node, *current_node;
		//�ҵ�valueֵ����Ӧ�Ľ��
		current_node = search(value);
		//��������Ϊ�գ�������������û����ôһ����㣬����false����ʾɾ��ʧ��
		if (current_node == NULL) {
			return false;
		}
		//������Ӳ�Ϊ�գ�����ǰ�������������������滻��ǰ����valueֵ����ɾ�����������Ľ�㣩
		if (current_node->lchild != NULL) {
			delete_node = current_node->predecessor();
		//����Һ��Ӳ�Ϊ�գ����Һ�̣������Һ�������С���滻��ǰ����valueֵ����ɾ���Һ�������С�Ľ�㣩
		}else if (current_node->rchild != NULL) {
			delete_node = current_node->successor();
		//���Һ��Ӷ�û�У���ɾ����ǰ���
		}else{
            delete_node = current_node;
		}
		//��Ҫɾ����ǰ�����̵�ֵ����current_node��ֵ
			/*
			���������û���Һ���:delete_node��ǰ��
			������Һ��ӣ�������û������:delete_node�Ǻ��
			������Һ��Ӷ�û�У�delete_node����current_node
			*/
        current_node->data = delete_node->data;
		//ɾ��delete_node�������ӵ�delete_nodeҪô����1�ȣ�Ҫô����0�ȣ�
		remove_node(delete_node);
		return true;
		
	}
};
class BinaryTree {
private:
    Node *root;
public:
    BinaryTree() {
        root = NULL;
    }
    ~BinaryTree() {
        if (root != NULL) {
            delete root;
        }
    }
	void insert(int value){
		//������Ϊ�գ���valueֵ����һ�������
		if (root == NULL) {
			root = new Node(value);
		}else{
		//����͵�����rootΪ���ģ���ǰ���������Ĳ��뺯�����в���	
			root->insert(value);
		}
	}
	bool find(int value){
		//���ݲ��ҽ������
		if(root->search(value) == NULL) {
			return false;
		}else{
			return true;
		}
	}

	//��ȡ���Һ��ӵ�Ȩֵ
	void getSon(int value){
		//��ȡ�ý��
		Node *current_node = root->search(value);
		if (current_node == NULL) {
			cout<<"(#, #)";
		}else{
			if (current_node->lchild != NULL) {
				cout<<current_node->lchild->data;
			}else{
				cout<<"#";
			}
			cout<<", ";
			if (current_node->rchild != NULL) {
				cout<<current_node->rchild->data;
			}else{
				cout<<"#";
			}
		}
			
	
	}
	//ɾ����������valueֵ�Ľ��
	bool delete_tree(int value){
		return root->delete_tree(value);
	}
};
int main() {
	BinaryTree binarytree;
	int n, temp;
	cin>>n;
	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		cin>>temp;
		a[i] = temp;
		binarytree.insert(temp);
	}
	sort(a, a+n);
	for (int j = 0; j < n; j++) {
		cout<<a[j]<<"(";
		binarytree.getSon(a[j]);
		cout<<")"<<endl;
	}
	
    return 0;
}
