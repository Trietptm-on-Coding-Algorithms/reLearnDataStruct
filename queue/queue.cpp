#include <iostream>  
#include <cassert>  
  
using namespace std;  
  
class Queue{  
private:  
    //保存队列的具体数据的  
    int* data;  
    //头 尾 队列长度  
    int head, tail, length;  
public:  
    //构造函数 length_input：初始队列长度  
    Queue(int length_input){  
        data = new int[length_input];  
        length = length_input;  
        //一开始队列为空，头为0，尾设置为-1  
        //只有一个元素时，头尾都是它，head=tail=0  
        head = 0;  
        tail = -1;  
    }  
    //析构函数  
    ~Queue(){  
        delete[] data;  
    }  
    //加入队列  
    void push(int element){  
        //队列不能满了，因为tail一般是从0到length-1，空队列就-1  
        //若tail + 1 == length，说明队列的尾是第length个元素了，已经没位置了  
        if (tail + 1 < length) {  
            //尾部移动，将元素放到相应位置  
            tail++;  
            data[tail] = element;  
        }  
    }  
    //队列元素的输出  
    void output(){  
        //从头遍历到尾输出  
        for (int i = head; i <= tail; i++) {  
            cout<<data[i]<<" ";  
        }  
        cout<<endl;  
    }  
    //返回队首元素  
    int front(){  
        //判断队列不为空，为空则退出  
        //这是宏断言，条件为true，继续执行，否则退出程序  
        assert(head <= tail);  
        return data[head];  
    }  
      
    //删除队首元素  
    void pop(){  
        assert(head <= tail);  
        //head往后移动一位就表示删除队首元素  
        head++;  
    }  
  
};  
  
int main(){  
    Queue queue(100);  
    for (int i = 1; i <= 10; i++) {  
        queue.push(i);  
    }  
    queue.output();  
    cout<<queue.front()<<endl;  
    queue.pop();  
    queue.output();  
    return 0;  
}  