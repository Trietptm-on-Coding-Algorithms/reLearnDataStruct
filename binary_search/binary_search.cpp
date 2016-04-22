#include <iostream>
#include <cstring>
#include <vector>
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
        if (loc < 0 || loc > length) {
            return false;
        }
        if (length >= size) {
            expand();
        }
        for (int i = length; i > loc; --i) {
            data[i] = data[i - 1];
        }
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
		/*//初始化二分查找的左右范围
		int left = 0, right = length -1;
		//左边必须小于等于右边
		while (left <= right) {
			int mid = (left + right) / 2;
			if (data[mid] == value) {
				return mid;
			}
			//暂时找不到就相应更新左或右的范围
			else if (data[mid] < value) {
				left = mid + 1;
			}else{
				right = mid -1;
			}
		}
		//来到这说明left > right，查找不成功
		return -1;
		*/
		for (int i = 0; i < length; i++) {  
			if(data[i] > value) {  
                return i-1;  
            }  
        }  
        return length-1; 
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
	int get(int index){
		return data[index];
	}
};
int main() {
    vector<int> a;
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		a.push_back(tmp);
	}
	/*for (int k = 0; k < n; k++) {
		cout<<a[k];
	}*/
	int find, flag = false;
	for (int j = 0; j < m; j++) {
		scanf("%d", &find);
		if (j != 0) {
			printf(" ");
		}
		if (a[0] > find) {
			printf("%d", a[0]);
			flag = true;
			continue;
		}
		for (int i = 0; i < n; i++) { 
			if(a[i] > find) {  
                printf("%d", a[i-1]); 
				flag = true;
				break;
            }else if(a[i] == find){
                printf("%d", a[i]); 
				flag = true;
				break;
            }  
        }
		if (!flag) {
			printf("%d", a[n-1]); 
		}
		flag = false;
	}
    return 0;
}