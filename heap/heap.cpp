#include <iostream>

using namespace std;

class Heap{
private:
	int *data, size;
public:
	//length_input:堆的最大容量
	Heap(int length_input){
		data = new int[length_input];
		size = 0;
	}
	~Heap(){
		delete[] data;
	}
	//插入
	void push(int value){
		//先放在堆中最后一个元素的后一个位置，注意这里的size是堆暂时的大小，跟堆的最大容量是不一样的
		data[size] = value;
		//用current储存插入元素的索引
		int current = size;
		//父亲结点的数组索引
		int	father = (current-1)/2;
		//如果插入的值大于父亲，就交换，注意索引值也要更新
		while (data[current] > data[father]) {
			//值交换
			swap(data[current], data[father]);
			//插入元素的索引，更新为父亲的索引
			current = father;
			//同时也计算出新的父亲的索引
			father = (current-1)/2;
		}
		//插入后，堆的大小+1
		size++;
	}
	//遍历输出
	void output(){
		//就像数组一样就行了
		for (int i = 0; i < size; i++) {
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}
	//返回堆顶元素
	int top(){
		return data[0];
	}
	//自上而下调整堆
	//pos:当前要调整的位置
	//n:当前堆中的元素个数
	void update(int pos, int n){
		//计算出左右孩子的索引值，等下比较pos位置的元素跟其左右孩子元素的大小
		int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
		//初始化这三个的最大值的索引为pos
		int max_value = pos;
		//首先索引要小于堆的大小，其次要值大于max_value位置的值，那么就更新max_value
		if (lchild < n && data[lchild] > data[max_value]) {
			max_value = lchild;
		}
		if (rchild < n && data[rchild] > data[max_value]) {
			max_value = rchild;
		}
		//经过上面的两个if，max_value绝对是三个中最大值得索引了，
		//如果不等于pos，那大的值就往上走，等于pos的话就不用再做任何操作了
		if (max_value != pos) {
			//进入到这里max_value肯定是左右孩子的值了，但我们不用管，有索引值就好
			swap(data[pos], data[max_value]);
			//两个元素值交换后，再递归调整
			update(max_value, n);
		}
	}
	//删除堆顶元素
	void pop(){
		//先将最后一个元素与堆顶元素的值交换
		swap(data[0], data[size-1]);
		//堆的大小减1，就相当于将最后的元素删除了
		size--;
		//再自上而下调整位置0，即新的堆顶的位置，size为堆的大小
		update(0, size);
	}
	//堆排序
	//注：本数据结构的堆为大根堆
	void heap_sort(){
		//从最后一个元素开始，将它与根值交换，再自上而下调整堆
		for (int i = size -1; i >= 1; i--) {
			//与堆顶元素交换，那么交换后最后一个元素data[size-1]的值是最大的，因为是大根堆
			swap(data[i], data[0]);
			//再自上而下调整堆，注意第i+1个及以后已经是升序排列，所以只需调整前i个
			//其实这里是将前i个中最大的值调整到堆顶，即data[0]
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
	//输出
	heap.output();
	cout<<heap.top()<<endl;
	heap.pop();
	heap.output();
	//堆排序
	heap.heap_sort();
	heap.output();
	return 0;
}