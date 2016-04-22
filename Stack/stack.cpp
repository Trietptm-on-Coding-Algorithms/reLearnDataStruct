#include<iostream>
#include<string>
#include <cassert>


using namespace std;

template<class Type> class Stack{
private:
	Type *elements;
	int max_size, top_index;
public:
	//���캯��
	Stack(int length_input){
		elements = new Type[length_input];
		max_size = length_input;
		top_index = -1;
	}
	//��������
	~Stack(){
		delete[] elements;
	}
	//��ջ
	bool push(const Type &element){
		//�Ƿ񳬹�ջ����
		if (top_index >= max_size-1) {
			return false;
		}
		//ջ�������ƣ�����ֵ
		top_index++;
		elements[top_index] = element;
		return true;
	}
	//��ջ
	bool pop(){
		//�ж�ջ�Ƿ�Ϊ��
		if (top_index < 0) {
			return false;
		}
		//ջ��������
		top_index--;
		return true;
	}
	//��ȡջ��Ԫ��
	Type top(){
		assert(top_index >= 0);
		return elements[top_index];
		//���� 
		//if (!empty()) {
		//	return elements[top_index];
		//}else{
		//	exit("there is no element");
		//}
	}
	//�ж�ջ�Ƿ�Ϊ��
	bool empty(){
		if (top_index < 0) {
			return true;
		}else{
			return false;
		}
	}
};

int main() {
	//n:	�����������ĸ���
	//minimum:	��ûѹ��ջ����С�����
	int n, minimum = 1;
    cin >> n;
	int *p = new int[n];
	//�жϳ�ջ˳���Ƿ����ı�ʶ
	bool flag = true;
	Stack<int> stack(n);
	
	//����Ҫ�жϵĳ�ջ˳��
	for (int i = 0; i <n ; i++) {
		cin>>p[i];
	}
	for (i = 0; i <n ; i++) {
		//������ڻ�ûѹ��ջ����С����ţ��ʹӻ�ûѹ��ջ����С����ŵ���������ѹ��ջ
		if (p[i] >= minimum) {
			for (int j = minimum; j <=p[i] ; j++) {
				stack.push(j);
			}
			//��Ҫ���»�ûѹ��ջ����С����ţ�Ҫ��1����Ϊ����ѹ��ȥ��
			minimum = p[i] + 1;
		}else{
		//�������˵��p[i]�Ѿ���ѹ��ջ��

			//�ж�ջ���Ƿ���ڸ�����
			//��Ϊ������ȳ�ջ����ô����С��������Ҳ�ǴӴ�С��ջ������һ���Ӵ�С������ջ
			//�� 3 2 1 5 4  ���� 3 2 5 4 1
			//1һ����������2 ���� 3 1 5 4 2 ��3 1 2 5 4���ⶼ�ǲ�����ĳ�ջ˳��
			if (stack.top() != p[i]){
				flag = false;
				break;
			}
		}
		//��ջ�����������if��else���ܱ�֤��ջ˳�������Լ��ֶ�����һ��[�����ջ˳���Ǻ���Ļ�]��
		stack.pop();
	}
	
	if (flag) {
		cout<<"YES";
	}else{
		cout<<"NO";
	}
    return 0;
}