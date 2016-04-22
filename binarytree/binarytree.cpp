#include <iostream>
#include <string>
using namespace std;

//�����
template<class Type> class Node{
public:
	//����
	Type data;
	//���Ӻ��Һ���
	Node *lchild, *rchild;
	Node(Type _data){
		data = _data;
		lchild = NULL;
		rchild = NULL;
	}
	~Node(){
		if (lchild != NULL) {
			delete lchild;
		}
		if (rchild != NULL) {
			delete rchild;
		}
	}
	//������������Լ������ң����Կ��������˳��Ҳ��������
	void preorder(){
		//�����ǰ����������
		cout<<data<<"";
		//��Ϊ�գ���ݹ�����������
		if (lchild != NULL) {
			lchild->preorder();
		}
		//�Ҳ�Ϊ�գ�Ҳ�ݹ�����������
		if (rchild != NULL) {
			rchild->preorder();
		}
	}
	//����������������У����ң�
	void inorder(){
		if (lchild != NULL) {
			lchild->inorder();
		}
		cout<<data<<"";
		if (rchild != NULL) {
			rchild->inorder();
		}
	}
	//��������������ң����м䣩
	void postorder(){
		if (lchild != NULL) {
			lchild->postorder();
		}
		if (rchild != NULL) {
			rchild->postorder();
		}
		cout<<data<<"";
	}
	//�����������򹹽�һ�Ŷ�����
	//pre_str:����������ַ�������124536��
	//in_str:����������ַ���
	//len������������������ַ����ĳ���
	Node* build(const string &pre_str, const string &in_str, int len){
		Node<Type> *p;
		//��������ĵ�һλ��pre_str[0]�����Ǹ���㣬�ȹ��������
		if (pre_str[0]>='0' && pre_str[0]<='9') {
		//�������������
			p = new Node<Type>(pre_str[0]-'0');
		}else{
			p = new Node<Type>(pre_str[0]);
		}
		//Node<Type> *p = new Node<Type>(pre_str[0]);
		//������������и��ڵ��λ�ã��������ߵĶ����������ģ��ұߵĶ�����������
		int pos = in_str.find(pre_str[0]);
		//��������Ϊ�գ�����������
		if (pos > 0) {
			//�Ը�������������Ϊ�µĸ����ȥ��������
			//���������������pos���������е�һ���Ǹ���㣬����substr(1,pos)����ʾ������1��ʼ����ȡpos���ַ����������������������
			//in_str.substr(0,pos):������0��ʼ����ȡpos���ַ�
			p->lchild = build(pre_str.substr(1,pos), in_str.substr(0,pos), pos);
		}
		//��������Ϊ�գ�����������
		if (len - pos -1 > 0) {
			//���������������len - pos -1���������е�һ���Ǹ���㣬������pos���������ģ�����substr(pos+1)����ʾ������pos+1���ַ�������󡿾����������������
			//in_str.substr(pos+1):������pos+1��ʼ���ַ��������
			p->rchild = build(pre_str.substr(pos+1), in_str.substr(pos+1), len - pos -1);
		}
		//�������,���ض�����
		return p;
	}
	Node* buildMirror(const string &pre_str, const string &in_str, int len){
		Node<Type> *p;
		if (pre_str[0]>='0' && pre_str[0]<='9') {
			p = new Node<Type>(pre_str[0]-'0');
		}else{
			p = new Node<Type>(pre_str[0]);
		}
		int pos = in_str.find(pre_str[0]);
		if (pos > 0) {
			p->rchild = buildMirror(pre_str.substr(1,pos), in_str.substr(0,pos), pos);
		}
		if (len - pos -1 > 0) {
			p->lchild = buildMirror(pre_str.substr(pos+1), in_str.substr(pos+1), len - pos -1);
		}
		return p;
	}

};

template<class Type> class BinaryTree{
private:
	//���ĸ�������������Ľ��
	Node<Type> *root;
public:
	//�޲ι��캯��
	BinaryTree(){
		//һ��ʼ��һ��û������--����
		root = NULL;
	}
	//��֪������������Ĺ��캯��
	BinaryTree(const string &pre_str, const string &in_str, int len){
		root = root->build(pre_str, in_str, len);
    }
	~BinaryTree(){
		if (root != NULL) {
			delete root;
		}
	}
	
	//�������
	void preorder(){
		root->preorder();
	}
	//�������
	void inorder(){
		root->inorder();
	}
	//�������
	void postorder(){
		root->postorder();
	}
	//�������������
	void buildMirror(const string &pre_str, const string &in_str, int len){
		root = root->buildMirror(pre_str, in_str, len);
	}
};



int main(){
	string pre_str;
    string in_str;
	cin>>pre_str>>in_str;
	BinaryTree<char> binarytree(pre_str, in_str, in_str.length());
	binarytree.postorder();
	cout<<endl;
	binarytree.buildMirror(pre_str, in_str, in_str.length());
	binarytree.postorder();
	cout<<endl;
   
	return 0;
}