#include <iostream>
#include <cstring>

using namespace std;

class Vector {
private:
    int size, length;
    int *data;
public:
    Vector(int input_size) {
        size = input_size;
        length = 0;
        data = new int[size];
    }
    ~Vector() {
        delete[] data;
    }
    bool insert(int loc, int value) {
		//插入位置的范围判断
        if (loc < 0 || loc > length) {
            return false;
        }
        if (length >= size) {
			//若当前线性表的长度大于等于容量时，就扩容
            expand();
        }
		//将loc后面的数据全部后移，从最后一个元素开始移
        for (int i = length; i > loc; --i) {
            data[i] = data[i - 1];
        }
		//插入该位置，并长度+1
        data[loc] = value;
        length++;
        return true;
    }
    void expand() {
        int * old_data = data;
        size = size * 2;
        data = new int[size];
        for (int i = 0; i < length; ++i) {
            data[i] = old_data[i];
        }
        delete[] old_data;
    }
    int search(int value) {
		for (int i = 0; i < length; i++) {
			if (data[i] == value) {
				return i;
			}else if (data[i] > value) {
				return -1;
			}
		}
		return -1;
    }
    bool remove(int index) {
        if (index < 0 || index >= length) {
            return false;
        }
        for (int i = index + 1; i < length; ++i) {
            data[i - 1] = data[i];
        }
        length = length - 1;
        return true;
    }
    void print() {
        for (int i = 0; i < length; ++i) {
            if (i > 0) {
                cout << " ";
            }
            cout << data[i];
        }
        cout << endl;
    }
};
int main() {
    Vector a(100);
    a.insert(0, 2);
    a.insert(1, 4);
    a.insert(2, 6);
    a.insert(3, 8);
    a.insert(4, 10);

    cout << a.search(4) << endl;
    cout << a.search(5) << endl;
    return 0;
}