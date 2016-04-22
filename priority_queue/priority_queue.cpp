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
	//n:一共有n个数，value代表权值（在哈弗曼编码里代表每个字符出啊先的次数）
	//ans:用于保存带权路径长度
	int n, value, ans = 0;
	double sum;
	cin>>n;
	Heap heap(n);
	for (double i = 1; i <= n; i++) {
		cin>>value;
		heap.push(value);
	}
	//因为我们的带权路径长度是不用算根结点的，所以下面的循环就是剩最后一个点时结束
	//只有一个结点就直接它的权值就是带权路径长度
	if (n == 1) {
		ans = ans + heap.top();
	}
	while (heap.heap_size() > 1) {
		//因为上面的数据结构是小根堆（即对于每个结点，它的权值小于以它为根构成的子树的所以的结点，注意这里不是之和）
		//a,b都是从堆顶获取的权值，获取完就删除该结点，所以a,b就是堆里面权值最小的两个结点
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
