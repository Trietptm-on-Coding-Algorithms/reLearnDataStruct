#include <iostream>  
#include <cassert>  
  
using namespace std;  
  
class Queue{  
private:  
    //������еľ������ݵ�  
    int* data;  
    //ͷ β ���г���  
    int head, tail, length;  
public:  
    //���캯�� length_input����ʼ���г���  
    Queue(int length_input){  
        data = new int[length_input];  
        length = length_input;  
        //һ��ʼ����Ϊ�գ�ͷΪ0��β����Ϊ-1  
        //ֻ��һ��Ԫ��ʱ��ͷβ��������head=tail=0  
        head = 0;  
        tail = -1;  
    }  
    //��������  
    ~Queue(){  
        delete[] data;  
    }  
    //�������  
    void push(int element){  
        //���в������ˣ���Ϊtailһ���Ǵ�0��length-1���ն��о�-1  
        //��tail + 1 == length��˵�����е�β�ǵ�length��Ԫ���ˣ��Ѿ�ûλ����  
        if (tail + 1 < length) {  
            //β���ƶ�����Ԫ�طŵ���Ӧλ��  
            tail++;  
            data[tail] = element;  
        }  
    }  
    //����Ԫ�ص����  
    void output(){  
        //��ͷ������β���  
        for (int i = head; i <= tail; i++) {  
            cout<<data[i]<<" ";  
        }  
        cout<<endl;  
    }  
    //���ض���Ԫ��  
    int front(){  
        //�ж϶��в�Ϊ�գ�Ϊ�����˳�  
        //���Ǻ���ԣ�����Ϊtrue������ִ�У������˳�����  
        assert(head <= tail);  
        return data[head];  
    }  
      
    //ɾ������Ԫ��  
    void pop(){  
        assert(head <= tail);  
        //head�����ƶ�һλ�ͱ�ʾɾ������Ԫ��  
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