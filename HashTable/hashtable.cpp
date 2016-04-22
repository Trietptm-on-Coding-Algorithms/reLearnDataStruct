#include <iostream>
#include <string>
using namespace std;

//����˵�ù�ϣ�����elem��������ַ�����ָ�����
class HashTable{
private:
	//�����ַ�����ָ��
	string *elem;
	//��ϣ������
	int size;
public:
	HashTable(int input_size){
		size = input_size;
		elem = new string[size];
		//��ʼ��ÿ���ַ���
		for (int i = 0; i < size; i++) {
			elem[i] = "#";
		}
	}
	~HashTable(){
		delete[] elem;
	}
	//��ϣ�������������ڶ��������˵��f()����
	//����˵���Ǽ����������ַ���Ҫ�����ҹ�ϣ�����飩���ĸ�λ��
	int hash(string& index){
		int code = 0;
		//����ı��� i ������ int ���ͣ���Ӧ���� size_t ���ͣ���Ϊ�ַ����� string ���ͣ������ int ���ͻ��о��档
		for (size_t i = 0; i < index.length(); i++) {
			//�з��ŵ��ַ���Χ�⣨ASCII���Ǵ� -128 �� 127��Ҳ����һ���� 256 ��
			//index[i] + 128�ǽ����Ƕ�ת��������
			//code * 256������Ϊ���ò����ַ�����Զ�� 
			//�����ַ���ת����ASCII��-128��-127�������code=1����λ��Ϊ1
			//�����ַ���ת����ASCII��-127��-126�������code=258����λ��Ϊ258
			//Ϊ�˷�ֹ���ݹ����µ������������ӵĽ���ٶԹ�ϣ��ĳ��� size ȡ��
			code = (code * 256 + index[i] + 128) % size;
		}
		return code;
	}
	//��ϣ��Ĳ��Һ���
	//index:����Ҫ���ҵ��ַ���
	//pos�����ǵĹ�ϣ���п��Բ���index����ַ�����λ��
	//times����ͻ�Ĵ���
	bool search(string &index, int &pos, int &times){
		pos = hash(index);
		times = 0;
		
		//��Ϊ���ǳ�ʼ��elemÿ��Ԫ��Ϊ"#"
		//elem[pos] != "#"		��˵����ǰhash��posλ������Ԫ��
		//elem[pos] != index	���Ҹ�λ���ϵ�ֵ������index�ַ�����˵����ͻ�����ˣ������������ַ�����Ӧ��ϣ���ͬһ��λ��pos��
		while (elem[pos] != "#" && elem[pos] != index) {
			//�ҵ���ͻ����ͻ����+1
			times++;
			//������ͻ��������Ҫ����һ���洢��ַ��
			//��������Ҫ�����ͻ���� times ҪС�ڹ�ϣ��ĳ��� size������������Ϊ��ϣ���Ѿ������ؼ����ˣ�û�п���ĵ�ַ���Դ洢��
			if (times < size) {
				//���ÿ��ŵ�ַ��������̽������ͻ
				pos = (pos + 1) % size;
			}else{
				//��ϣ���Ѿ������ؼ���,�Ҳ���index����ַ��������ϣ���λ��
				return false;
			}
		}
		//��λ���ϵ�ֵ����index�ַ�����˵���ҵ���
		if (elem[pos] == index) {
			return true;
		}else{
			//�����Ҳ���
			return false;
		}
	}
	//�����ַ�������ϣ����
	int insert(string &index){
		int pos, times;
		//����ǰ�����Ƿ��Ѿ��ڹ�ϣ����
		if (search(index, pos, times)) {
			return 2;
		}else if (times < size/2) {
		//����ͻ�������ڹ�ϣ���ȵ�һ��
			//�����search�����Ѿ��ҵ����Բ����λ��pos�ˣ�ֱ�Ӹ�ֵ�Ϳ�����
			elem[pos] = index;
			return 1;
		}else{
			//��ͻ���࣬Ϊ����߲���Ч�ʣ��ؽ���ϣ��
			//��Ϊ��ͻ���࣬search��whileѭ���Ĵ�����ܶ࿩
			recreate();
			return 0;
		}
	}
	//�ؽ���ϣ��
	void recreate(){
	//���Ƚ�ԭ���Ĺ�ϣ���ֵ��ʱ��������	
		string *temp_elem;
		temp_elem = new string[size];
		for (int i = 0; i < size; i++) {
			temp_elem[i] = elem[i];
		}
	//�����ϣ��
		int copy_size = size;
		//��������
		size = size * 2;
		//����ǰ���ͷ�֮ǰ�Ŀռ�
		delete[] elem;
		elem = new string[size];
		//�ȸ���ֵ ��"#"
		for ( i = 0; i < size; i++) {
			elem[i] = "#";
		}
		for ( i = 0; i < copy_size; i++) {
			if (temp_elem[i] != "#") {
				insert(temp_elem[i]);
			}
		}		
		delete[] temp_elem;		
	}
};

int main() {
	HashTable hashtable(200000);
	string buffer;
	//�����Ҫ������ٸ��ַ���
	int n;
	cin>>n;
	for (int i = 1; i <= n; i++) {
		cin>>buffer;
		//ת��ΪСд
		for (int j = 0; j < buffer.length(); j++) {
			if (buffer[j] >= 65 && buffer[j] <=90) {
				buffer[j] = char(buffer[j]+32);
			}
		}
		int ans = hashtable.insert(buffer);
		if (ans == 0) {
			cout<<"insert failed!"<<endl;
		}else if (ans == 1) {
			cout<<"���û���û�����ǵ�������"<<endl;
		}else if (ans == 2) {
			cout<<"���û��Ѵ��ڣ��뷢�ʼ����������û���"<<endl;
		}
	}
    return 0;
}



