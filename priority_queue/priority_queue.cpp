#include<iostream>
#include <math.h>
using namespace std;
class Heap {
private:
	int size;
    double *data;
public:
    Heap(int length_input) {
        data = new double[length_input];
        size = 0;
    }
    ~Heap() {
        delete[] data;
    }
    void push(double value) {
        data[size] = value;
        int current = size;
        int father = (current - 1) / 2;
        while (data[current] > data[father]) {
            swap(data[current], data[father]);
            current = father;
            father = (current - 1) / 2;
        }
        size++;
    }
    double top() {
         return data[0];
    }
    void update(int pos, int n) {
        int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
        int min_value = pos;
        if (lchild < n && data[lchild] > data[min_value]) {
            min_value = lchild;
        }
        if (rchild < n && data[rchild] > data[min_value]) {
            min_value = rchild;
        }
        if (min_value != pos) {
            swap(data[pos], data[min_value]);
            update(min_value, n);
        }
    }
    void pop() {
        swap(data[0], data[size - 1]);
        size--;
        update(0, size);
    }
    double heap_size() {
        return size;
    }
};
int main() {
	//n:һ����n������value����Ȩֵ���ڹ��������������ÿ���ַ������ȵĴ�����
	//ans:���ڱ����Ȩ·������
	int n, value, ans = 0;
	double sum;
	cin>>n;
	Heap heap(n);
	for (double i = 1; i <= n; i++) {
		cin>>value;
		heap.push(value);
	}
	//��Ϊ���ǵĴ�Ȩ·�������ǲ���������ģ����������ѭ������ʣ���һ����ʱ����
	//ֻ��һ������ֱ������Ȩֵ���Ǵ�Ȩ·������
	if (n == 1) {
		ans = ans + heap.top();
	}
	while (heap.heap_size() > 1) {
		//��Ϊ��������ݽṹ��С���ѣ�������ÿ����㣬����ȨֵС������Ϊ�����ɵ����������ԵĽ�㣬ע�����ﲻ��֮�ͣ�
		//a,b���ǴӶѶ���ȡ��Ȩֵ����ȡ���ɾ���ý�㣬����a,b���Ƕ�����Ȩֵ��С���������
		double a = heap.top();
		heap.pop();
		double b = heap.top();
		heap.pop();
		sum = pow(a*b*b,1.0/3);
		ans = ans + sum;	
		heap.push(sum);
	}
	cout<<sum<<endl;
    return 0;
}
