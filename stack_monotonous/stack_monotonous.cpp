#include<iostream>
#include<cassert>
using namespace std;
class Node {
public:
    int id, height;
};
template<class Type> class Stack {
private:
    Type *urls;
    int max_size, top_index;
public:
    Stack(int length_input) {
        urls = new Type[length_input];
        max_size = length_input;
        top_index = -1;
    }
    ~Stack() {
        delete[] urls;
    }
    bool push(const Type &element) {
        if (top_index >= max_size - 1) {
            return false;
        }
        top_index++;
        urls[top_index] = element;
        return true;
    }
    bool pop() {
        if (top_index < 0) {
            return false;
        }
        top_index--;
        return true;
    }
    Type top() {
        assert(top_index >= 0);
        return urls[top_index];
    }
    bool empty() {
        if (top_index < 0) {
            return true;
        } else {
            return false;
        }
    }
};
int main() {
	int n, ans=0;
	cin>>n;
	Stack<Node> stack(n);
	Node temp;
	for (int i = 1; i <= n; i++) {
		cin>>temp.height;
		temp.id = i;
	}
    return 0;
}
