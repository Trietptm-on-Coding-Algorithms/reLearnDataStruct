//包含输入输出流库和应该就是字符串的库
#include "iostream"
#include "cstring"

using namespace std;

class Vector{
private:
	//size:最大容量，length:当前顺序表的个数
	int size, length;
	//我们要使用的方式是动态分配，所以就定义个指针
	int *data;
public:
	//构造函数，input_size：顺序表长度
	Vector(int input_size){
		//初始化最大容量和长度，以及将指向储存元素值的空间的指针初始化
		size = input_size;
        length = 0;
        data = new int[size];
	}
	//析构函数
	~Vector(){
		//方括号的存在会使编译器获取数组大小(size)然后析构函数再被依次应用在每个元素上,一共size次。
		//因为你申请的数组，这样做也有对称美
		delete[] data;
	}
	
	//loc:插入位置，value：插入的值
	bool insert(int loc, int value){
		//先判断插入位置是否合法
		if(loc < 0 || loc > length){
            return false;
        }
		//是否达到最大容量了
		if(length >= size){
            //return false;
			//扩容
			expand();
        }
		//从最后一个开始，前一个的值覆盖后一个，直到最后一次，i=loc+1,data[loc+1]=data[loc]
		//这样就完成了数据向后移动
		for (int i = length; i > loc; i--){
			data[i] = data[i-1];
		}
		//赋值，长度+1
		data[loc] = value;
		length++;
        return true;
	}
	//扩容
	void expand(){
		//定义一个指针指向data首地址
		int* old_data = data; 
		//扩大为原来两倍
		size = size * 2;
        data = new int[size];
		//拷贝（复制）数据
		for (int i = 0; i < length; i++){
			data[i] = old_data[i];
		}
		//释放原来的空间
		delete[] old_data;
	}

	//查找
	int search(int value){
		//循环遍历，找到返回索引，否则返回-1
		for (int i = 0; i < length; i++){
			if (data[i] == value){
				return i;
			}
		}
		return -1;
	}
	//删除
	bool remove(int index){
		//判断是否越界
		if (index < 0 || index >= length) {
			return false;
		}
		//后面覆盖前面的
		for (int i = index+1; i< length; i++){
			data[i-1] = data[i];
		}
		//长度-1
		length--;
		return true;
	}

	//遍历输出
	void print(){
		for (int i = 0; i < length; i++) {
			//如果不是第一个就先输出一个空格
			if (i > 0) {
				cout<<" ";
			}
			cout<<data[i];
		}
		//最后输出换行
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
