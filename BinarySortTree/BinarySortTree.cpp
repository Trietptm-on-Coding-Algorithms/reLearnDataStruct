#include<iostream>
#include <string>
#include <algorithm>

using namespace std;
class Node {
public:
    int data;
	//father就是父亲结点，就是往上走一级的那一个
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
	//插入函数
	void insert(int value){
		//value已经在二叉树上，直接返回
		if (value == data) {
			return;
		//大于当前结点的数据，在右子树插入，否则在左子树	
		}else if (value > data) {
			//右子树为空，就把value当做新结点，父节点是当前的结点
			if (rchild == NULL) {
				rchild = new Node(value, this);
			}else{
			//否则递归调用插入函数
				rchild->insert(value);
			}
		}else{
		//这里基本跟上面的逻辑差不多，这里是左子树而已
			if (lchild == NULL) {
				lchild = new Node(value, this);
			}else{
				lchild->insert(value);
			}
		}
	}
	//查找函数
	Node* search(int value){
		//value == data，表示查找到了，返回当前结点
		if (value == data) {
			return this;
		//大于当前结点，向右子树查找	
		}else if (value > data) {
			//右子树为空，代表查找失败
			if (rchild == NULL) {
				return NULL;
			//否则递归对右子树调用查找
			}else{
				return rchild->search(value);
			}
		}else{
		//这里基本跟上面的逻辑差不多，这里是左子树而已
			if (lchild == NULL) {
				return NULL;
			}else{
				return lchild->search(value);
			}	
		}
	}
	//查找前驱（简单来说就是在左子树找最大的）
	Node* predecessor(){
		//首先用temp保存左孩子
		Node *temp = lchild;
		//当前的结点和他的右孩子不能为空，这样我们才能继续查找比这个结点的值大的结点
		while (temp != NULL && temp->rchild != NULL) {
			//继续向右孩子查找
			temp = temp->rchild;
		}
		//循环结束，temp就是我们要找的前驱
		return temp;
	}
	//查找后继（简单来说就是在右子树找最小的）
	Node* successor(){
		//首先用temp保存右孩子
		Node *temp = rchild;
		//当前的结点和他的左孩子不能为空，这样我们才能继续查找比这个结点的值小的结点
		while (temp != NULL && temp->lchild != NULL) {
			temp = temp->lchild;
		}
		//循环结束，temp就是我们要找的后继
		return temp;
	}
	//删除结点（只删除度为0或1的结点，度就是分支的数目），这个很方便地删除前驱和后继
	void remove_node(Node *delete_node){
		//用来记录当前结点的孩子结点
		Node *temp = NULL;
		//如果要删除的结点的左孩子不为空
		if (delete_node->lchild != NULL) {
			//更新它的父亲为delete_node的父亲
			temp = delete_node->lchild;
			temp->father = delete_node->father;
			//并且把delete_node的左孩子置为空
			delete_node->lchild = NULL;
		}
		//如果要删除的结点的右孩子不为空
		if (delete_node->rchild != NULL) {
			//更新它的父亲为delete_node的父亲
			temp = delete_node->rchild;
			temp->father = delete_node->father;
			//并且把delete_node的右孩子置为空
			delete_node->rchild = NULL;
		}
		//如果delete_node是父亲的左孩子，则更新temp为delete_node的父亲的左孩子，否则就更新为右孩子
		if (delete_node->father->lchild == delete_node) {
			delete_node->father->lchild = temp;
		}else{
			delete_node->father->rchild = temp;
		}
		//最后删除该结点
		delete delete_node;
	}
	//删除二叉树上value值的结点（原理是将孩子结点的值覆盖value结点上的值）
	bool delete_tree(int value){
		//delete_node：要删除的结点
		//current_node：当前结点（value值的）
		Node *delete_node, *current_node;
		//找到value值所对应的结点
		current_node = search(value);
		//若果返回为空，表明二叉树上没有这么一个结点，返回false，表示删除失败
		if (current_node == NULL) {
			return false;
		}
		//如果左孩子不为空，就找前驱（即用左孩子中最大的替换当前结点的value值，再删除左孩子中最大的结点）
		if (current_node->lchild != NULL) {
			delete_node = current_node->predecessor();
		//如果右孩子不为空，就找后继（即用右孩子中最小的替换当前结点的value值，再删除右孩子中最小的结点）
		}else if (current_node->rchild != NULL) {
			delete_node = current_node->successor();
		//左右孩子都没有，就删除当前结点
		}else{
            delete_node = current_node;
		}
		//将要删除的前驱或后继的值覆盖current_node的值
			/*
			如果有左孩子没有右孩子:delete_node是前驱
			如果有右孩子，不管有没有左孩子:delete_node是后继
			如果左右孩子都没有：delete_node就是current_node
			*/
        current_node->data = delete_node->data;
		//删除delete_node（这样子的delete_node要么就是1度，要么就是0度）
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
		//若树根为空，以value值建立一个根结点
		if (root == NULL) {
			root = new Node(value);
		}else{
		//否则就调用以root为根的（当前）二叉树的插入函数进行插入	
			root->insert(value);
		}
	}
	bool find(int value){
		//根据查找结果返回
		if(root->search(value) == NULL) {
			return false;
		}else{
			return true;
		}
	}

	//获取左右孩子的权值
	void getSon(int value){
		//获取该结点
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
	//删除二叉树上value值的结点
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
