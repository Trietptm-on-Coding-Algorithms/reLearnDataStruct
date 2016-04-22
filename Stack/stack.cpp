#include<iostream>
#include<string>
#include <cassert>


using namespace std;

template<class Type> class Stack{
private:
	Type *elements;
	int max_size, top_index;
public:
	//构造函数
	Stack(int length_input){
		elements = new Type[length_input];
		max_size = length_input;
		top_index = -1;
	}
	//析构函数
	~Stack(){
		delete[] elements;
	}
	//入栈
	bool push(const Type &element){
		//是否超过栈容量
		if (top_index >= max_size-1) {
			return false;
		}
		//栈顶向上移，并赋值
		top_index++;
		elements[top_index] = element;
		return true;
	}
	//出栈
	bool pop(){
		//判断栈是否为空
		if (top_index < 0) {
			return false;
		}
		//栈顶向下移
		top_index--;
		return true;
	}
	//获取栈顶元素
	Type top(){
		assert(top_index >= 0);
		return elements[top_index];
		//或者 
		//if (!empty()) {
		//	return elements[top_index];
		//}else{
		//	exit("there is no element");
		//}
	}
	//判断栈是否为空
	bool empty(){
		if (top_index < 0) {
			return true;
		}else{
			return false;
		}
	}
};

int main() {
	//n:	连续正整数的个数
	//minimum:	还没压入栈的最小的序号
	int n, minimum = 1;
    cin >> n;
	int *p = new int[n];
	//判断出栈顺序是否合理的标识
	bool flag = true;
	Stack<int> stack(n);
	
	//输入要判断的出栈顺序
	for (int i = 0; i <n ; i++) {
		cin>>p[i];
	}
	for (i = 0; i <n ; i++) {
		//如果大于还没压入栈的最小的序号，就从还没压入栈的最小的序号到自身都依次压入栈
		if (p[i] >= minimum) {
			for (int j = minimum; j <=p[i] ; j++) {
				stack.push(j);
			}
			//还要更新还没压入栈的最小的序号，要加1，因为本身压进去了
			minimum = p[i] + 1;
		}else{
		//进入这里，说明p[i]已经被压入栈了

			//判断栈顶是否等于该数，
			//因为大的数先出栈，那么比它小的数必须也是从大到小出栈，但不一定从大到小连续出栈
			//如 3 2 1 5 4  或者 3 2 5 4 1
			//1一定不能先于2 ，如 3 1 5 4 2 ，3 1 2 5 4，这都是不合理的出栈顺序
			if (stack.top() != p[i]){
				flag = false;
				break;
			}
		}
		//出栈（经过上面的if，else，能保证出栈顺序能像自己手动输入一样[如果出栈顺序是合理的话]）
		stack.pop();
	}
	
	if (flag) {
		cout<<"YES";
	}else{
		cout<<"NO";
	}
    return 0;
}