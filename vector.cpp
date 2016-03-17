//����������������Ӧ�þ����ַ����Ŀ�
#include "iostream"
#include "cstring"

using namespace std;

class Vector{
private:
	//size:���������length:��ǰ˳���ĸ���
	int size, length;
	//����Ҫʹ�õķ�ʽ�Ƕ�̬���䣬���ԾͶ����ָ��
	int *data;
public:
	//���캯����input_size��˳�����
	Vector(int input_size){
		//��ʼ����������ͳ��ȣ��Լ���ָ�򴢴�Ԫ��ֵ�Ŀռ��ָ���ʼ��
		size = input_size;
        length = 0;
        data = new int[size];
	}
	//��������
	~Vector(){
		//�����ŵĴ��ڻ�ʹ��������ȡ�����С(size)Ȼ�����������ٱ�����Ӧ����ÿ��Ԫ����,һ��size�Ρ�
		//��Ϊ����������飬������Ҳ�жԳ���
		delete[] data;
	}
	
	//loc:����λ�ã�value�������ֵ
	bool insert(int loc, int value){
		//���жϲ���λ���Ƿ�Ϸ�
		if(loc < 0 || loc > length){
            return false;
        }
		//�Ƿ�ﵽ���������
		if(length >= size){
            //return false;
			//����
			expand();
        }
		//�����һ����ʼ��ǰһ����ֵ���Ǻ�һ����ֱ�����һ�Σ�i=loc+1,data[loc+1]=data[loc]
		//�������������������ƶ�
		for (int i = length; i > loc; i--){
			data[i] = data[i-1];
		}
		//��ֵ������+1
		data[loc] = value;
		length++;
        return true;
	}
	//����
	void expand(){
		//����һ��ָ��ָ��data�׵�ַ
		int* old_data = data; 
		//����Ϊԭ������
		size = size * 2;
        data = new int[size];
		//���������ƣ�����
		for (int i = 0; i < length; i++){
			data[i] = old_data[i];
		}
		//�ͷ�ԭ���Ŀռ�
		delete[] old_data;
	}

	//����
	int search(int value){
		//ѭ���������ҵ��������������򷵻�-1
		for (int i = 0; i < length; i++){
			if (data[i] == value){
				return i;
			}
		}
		return -1;
	}
	//ɾ��
	bool remove(int index){
		//�ж��Ƿ�Խ��
		if (index < 0 || index >= length) {
			return false;
		}
		//���渲��ǰ���
		for (int i = index+1; i< length; i++){
			data[i-1] = data[i];
		}
		//����-1
		length--;
		return true;
	}

	//�������
	void print(){
		for (int i = 0; i < length; i++) {
			//������ǵ�һ���������һ���ո�
			if (i > 0) {
				cout<<" ";
			}
			cout<<data[i];
		}
		//����������
		cout<<endl;
	}
};

int main(){
	Vector a(2);
	cout << a.insert(0, 1) << endl;
	cout << a.insert(0, 2) << endl;
	a.print();
	cout << a.remove(1) << endl;
	a.print();
	cout << a.insert(1, 4) << endl;
    cout << a.search(4) << endl;
	cout << a.search(5) << endl;
    return 0;
}
