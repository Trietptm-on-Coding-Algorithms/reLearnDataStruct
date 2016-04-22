#include <iostream>

using namespace std;

class Heap{
private:
	int *data, size;
public:
	//length_input:�ѵ��������
	Heap(int length_input){
		data = new int[length_input];
		size = 0;
	}
	~Heap(){
		delete[] data;
	}
	//����
	void push(int value){
		//�ȷ��ڶ������һ��Ԫ�صĺ�һ��λ�ã�ע�������size�Ƕ���ʱ�Ĵ�С�����ѵ���������ǲ�һ����
		data[size] = value;
		//��current�������Ԫ�ص�����
		int current = size;
		//���׽�����������
		int	father = (current-1)/2;
		//��������ֵ���ڸ��ף��ͽ�����ע������ֵҲҪ����
		while (data[current] > data[father]) {
			//ֵ����
			swap(data[current], data[father]);
			//����Ԫ�ص�����������Ϊ���׵�����
			current = father;
			//ͬʱҲ������µĸ��׵�����
			father = (current-1)/2;
		}
		//����󣬶ѵĴ�С+1
		size++;
	}
	//�������
	void output(){
		//��������һ��������
		for (int i = 0; i < size; i++) {
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}
	//���ضѶ�Ԫ��
	int top(){
		return data[0];
	}
	//���϶��µ�����
	//pos:��ǰҪ������λ��
	//n:��ǰ���е�Ԫ�ظ���
	void update(int pos, int n){
		//��������Һ��ӵ�����ֵ�����±Ƚ�posλ�õ�Ԫ�ظ������Һ���Ԫ�صĴ�С
		int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
		//��ʼ�������������ֵ������Ϊpos
		int max_value = pos;
		//��������ҪС�ڶѵĴ�С�����Ҫֵ����max_valueλ�õ�ֵ����ô�͸���max_value
		if (lchild < n && data[lchild] > data[max_value]) {
			max_value = lchild;
		}
		if (rchild < n && data[rchild] > data[max_value]) {
			max_value = rchild;
		}
		//�������������if��max_value���������������ֵ�������ˣ�
		//���������pos���Ǵ��ֵ�������ߣ�����pos�Ļ��Ͳ��������κβ�����
		if (max_value != pos) {
			//���뵽����max_value�϶������Һ��ӵ�ֵ�ˣ������ǲ��ùܣ�������ֵ�ͺ�
			swap(data[pos], data[max_value]);
			//����Ԫ��ֵ�������ٵݹ����
			update(max_value, n);
		}
	}
	//ɾ���Ѷ�Ԫ��
	void pop(){
		//�Ƚ����һ��Ԫ����Ѷ�Ԫ�ص�ֵ����
		swap(data[0], data[size-1]);
		//�ѵĴ�С��1�����൱�ڽ�����Ԫ��ɾ����
		size--;
		//�����϶��µ���λ��0�����µĶѶ���λ�ã�sizeΪ�ѵĴ�С
		update(0, size);
	}
	//������
	//ע�������ݽṹ�Ķ�Ϊ�����
	void heap_sort(){
		//�����һ��Ԫ�ؿ�ʼ���������ֵ�����������϶��µ�����
		for (int i = size -1; i >= 1; i--) {
			//��Ѷ�Ԫ�ؽ�������ô���������һ��Ԫ��data[size-1]��ֵ�����ģ���Ϊ�Ǵ����
			swap(data[i], data[0]);
			//�����϶��µ����ѣ�ע���i+1�����Ժ��Ѿ����������У�����ֻ�����ǰi��
			//��ʵ�����ǽ�ǰi��������ֵ�������Ѷ�����data[0]
			update(0, i);
		}
	}
};

int main(){
	int arr[10] = { 12, 9, 30, 24, 30, 4, 55, 64, 22, 37 };
	Heap heap(100);
	for (int i = 0; i < 10; i++) {
		heap.push(arr[i]);
	}
	//���
	heap.output();
	cout<<heap.top()<<endl;
	heap.pop();
	heap.output();
	//������
	heap.heap_sort();
	heap.output();
	return 0;
}