#include <iostream>
#include <string>
using namespace std;

//下面说得哈希表就是elem这个储存字符串的指针变量
class HashTable{
private:
	//储存字符串的指针
	string *elem;
	//哈希表容量
	int size;
public:
	HashTable(int input_size){
		size = input_size;
		elem = new string[size];
		//初始化每个字符串
		for (int i = 0; i < size; i++) {
			elem[i] = "#";
		}
	}
	~HashTable(){
		delete[] elem;
	}
	//哈希函数，就是我在定义里随便说得f()函数
	//简单来说就是计算出你这个字符串要放在我哈希表（数组）的哪个位置
	int hash(string& index){
		int code = 0;
		//这里的变量 i 不能用 int 类型，而应该用 size_t 类型，因为字符串是 string 类型，如果用 int 类型会有警告。
		for (size_t i = 0; i < index.length(); i++) {
			//有符号的字符范围这（ASCII）是从 -128 到 127，也就是一共有 256 种
			//index[i] + 128是将他们都转换成正数
			//code * 256估计是为了让差不多的字符相差更远， 
			//比如字符串转化成ASCII是-128，-127，算出的code=1，即位置为1
			//比如字符串转化成ASCII是-127，-126，算出的code=258，即位置为258
			//为了防止数据过大导致的数据溢出，相加的结果再对哈希表的长度 size 取余
			code = (code * 256 + index[i] + 128) % size;
		}
		return code;
	}
	//哈希表的查找函数
	//index:我们要查找的字符串
	//pos：我们的哈希表中可以插入index这个字符串的位置
	//times：冲突的次数
	bool search(string &index, int &pos, int &times){
		pos = hash(index);
		times = 0;
		
		//因为我们初始化elem每个元素为"#"
		//elem[pos] != "#"		这说明当前hash表pos位置上有元素
		//elem[pos] != index	并且该位置上的值不等于index字符串，说明冲突产生了，（两个以上字符串对应哈希表的同一个位置pos）
		while (elem[pos] != "#" && elem[pos] != index) {
			//找到冲突，冲突次数+1
			times++;
			//发生冲突后，我们需要找下一个存储地址，
			//首先我们要满足冲突次数 times 要小于哈希表的长度 size，否则我们认为哈希表已经填满关键字了，没有空余的地址可以存储。
			if (times < size) {
				//利用开放地址法的线性探测解决冲突
				pos = (pos + 1) % size;
			}else{
				//哈希表已经填满关键字,找不到index这个字符串插入哈希表的位置
				return false;
			}
		}
		//该位置上的值等于index字符串，说明找到了
		if (elem[pos] == index) {
			return true;
		}else{
			//否则找不到
			return false;
		}
	}
	//插入字符串到哈希表中
	int insert(string &index){
		int pos, times;
		//插入前看看是否已经在哈希表中
		if (search(index, pos, times)) {
			return 2;
		}else if (times < size/2) {
		//若冲突次数少于哈希表长度的一半
			//上面的search函数已经找到可以插入的位置pos了，直接赋值就可以了
			elem[pos] = index;
			return 1;
		}else{
			//冲突过多，为了提高查找效率，重建哈希表
			//因为冲突过多，search的while循环的次数会很多咯
			recreate();
			return 0;
		}
	}
	//重建哈希表
	void recreate(){
	//首先将原来的哈希表的值临时储存起来	
		string *temp_elem;
		temp_elem = new string[size];
		for (int i = 0; i < size; i++) {
			temp_elem[i] = elem[i];
		}
	//扩大哈希表
		int copy_size = size;
		//扩大两倍
		size = size * 2;
		//申请前先释放之前的空间
		delete[] elem;
		elem = new string[size];
		//先赋初值 ："#"
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
	//这个是要输入多少个字符串
	int n;
	cin>>n;
	for (int i = 1; i <= n; i++) {
		cin>>buffer;
		//转换为小写
		for (int j = 0; j < buffer.length(); j++) {
			if (buffer[j] >= 65 && buffer[j] <=90) {
				buffer[j] = char(buffer[j]+32);
			}
		}
		int ans = hashtable.insert(buffer);
		if (ans == 0) {
			cout<<"insert failed!"<<endl;
		}else if (ans == 1) {
			cout<<"此用户名没在我们的数据中"<<endl;
		}else if (ans == 2) {
			cout<<"此用户已存在，请发邮件叫他更改用户名"<<endl;
		}
	}
    return 0;
}



