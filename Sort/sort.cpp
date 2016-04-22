#include <iostream>
#include <cstring>
using namespace std;
class Vector {
private:
    int size, length;
    int * data, *temp;
	//l:left,Ҫ�������˵�
	//r:right��Ҫ������Ҷ˵�
	void merge_sort(int l, int r){
		//���������ң�˵��ÿ������ֻʣ1��Ԫ���ˣ�������ɣ�ֱ�ӷ���
		if (l == r) {
			return;
		}
		//�����м�����������ж���
		int mid = (l + r) /2;
		//�ݹ���ã�����Χ����˵㵽�е�
		merge_sort(l, mid);
		//�ݹ���ã�����Χ���е㵽�Ҷ˵�
		merge_sort(mid+1, r);
		//x����¼��ߵĴ����ĸ�Ԫ���ˣ���ʼ��Ϊ��˵�
		//y����¼�ұߵĴ����ĸ�Ԫ���ˣ���ʼ��Ϊ�м�+1
		//loc����¼��ʱ�������ݵ����������λ�ã��������������������Ľ����
		int x = l, y = mid + 1, loc = l;
		//ѭ����������ߺ��ұߵ�Ԫ�ض�û�����꣬��xС�ڵ����м䣬yС�ڵ����Ҷ˵�
		while (x <= mid || y <= r) {
			//��xС�ڵ����м䣬�ң�y>r:�ұߴ������� �� ��ߵ�����С���ұ߶�Ӧ�����ݣ�
			if (x <= mid && (y > r || data[x] <= data[y])) {
				//��x��Ӧ�����ݷŵ���ʱ����Ķ�Ӧλ��
				temp[loc] = data[x];
				//λ�ú���
				x++;
			}else{
			//����,��ʵ��������	x>mid���ߣ�y<=r��data[x]>data[y]��
				temp[loc] = data[y];
				//λ�ú���
				y++;
			}
			//��ʱ����λ�ú���
			loc++;
		}
		//��������ǵ�ԭ����
		for (int i = l; i <= r; i++) {
			data[i] = temp[i];
		}
	}

	void quick_sort(int l, int r){
		//pivot:��׼(Ĭ������Ϊ����ĵ�һ��Ԫ�ص�ֵ) i,j:�������������	(���洦����ɺ�j:��С��pivotԪ�ص��Ҷˣ�i������pivotԪ�ص����)
		int pivot = data[l], i = l, j = r;
		do {
			//������߿�ʼ���ҵ���һ�����ڵ��ڻ�׼Ԫ�ص��±꣨��ʵ���ǻ�׼Ԫ�ص��±꣩
			//��Ϊ���ڵ���pivotʱ��ѭ����������ʱ��i��������±�
			while (i <= j && data[i] < pivot) {
				i++;
			}
			//�����ұ߿�ʼ���ҵ���һ��С�ڵ��ڻ�׼Ԫ�ص��±�
			//��ΪС�ڵ���pivotʱ��ѭ����������ʱ��j��������±�
			while (i <= j && data[j] > pivot ) {
				j--;
			}
			//i<=j˵������ҵ��˱�pivot���ұ߱�pivotС��Ԫ�أ������Է�ΪС��pivot�ʹ���pivot������
			if (i <= j) {
				swap(data[i], data[j]);
				i++;
				j--;
			}
		} while(i <= j);
		//�����do while���������������Ѿ���ΪС��pivot�ʹ���pivot������(i����ߣ�������pivot������С��pivot��i���ұ߾��Ǵ���pivot��Ԫ�أ������Լ���ͼ���һ��)
		//�����С��pivot���ֵ�Ԫ�صĸ�������1����lС��j����Ϊj��С��pivotԪ�ص��Ҷˣ�����ݹ����
		if (l < j) {
			quick_sort(l, j);
		}
		//���ұߴ���pivot���ֵ�Ԫ�صĸ�������1����r����i����Ϊi�Ǵ���pivotԪ�ص���ˣ�����ݹ����
		if (r > i) {
			quick_sort(i, r);
		}
	}
public:
    Vector(int input_size) {
        size = input_size;
        length = 0;
        data = new int[size];
		temp = new int[size];
    }
    ~Vector() {
        delete[] data;
		delete[] temp;
    }
    bool insert(int loc, int value) {
        if (loc < 0 || loc > length) {
            return false;
        }
        if (length >= size) {
            return false;
        }
        for (int i = length; i > loc; --i) {
            data[i] = data[i - 1];
        }
        data[loc] = value;
        length++;
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
	//��������
    /*void sort() {
		//���ѭ����0������
		for (int i = 0; i < length; i++) {
			//�ڲ�ѭ���ʹ�i��ǰһ����0����Ϊi��ǰһ�����Ѿ��ź���ġ���һ����ǰһ���Ͳ��ù��ˡ������ԣ����ǵĵ�i��Ҫ��ǰi-1����һ�ȽϽ�����ֱ��λ�ú���[������]��
			for (int j = i -1; j >= 0; j--) {
				//���ǰ��Ĵ��ں���ͽ����������Ż�����������
				if (data[j] > data[j+1] ) {
					swap(data[j], data[j+1]);
				}else{
				//����˵���Ѿ�����ȷ��λ�����ˣ��˳��ڲ�ѭ��������������һ��Ԫ��
					break;
				}
			}
		}
    }*/
	//ð������
	/*
	void sort(){
		//���ѭ����Ϊ�ڲ����ģ�����j < length - i -1��Ҳ���Ǵ�i=1ʱ���ڲ�ѭ��������j<length-1�������i=length-2,�ڲ�ѭ��������j<1
		for (int i = 0; i < length - 1; i++) {
			for (int j = 0; j < length - i -1; j++ ) {
				if (data[j] > data[j+1]) {
					swap(data[j], data[j+1]);
				}
			}
		}
	}*/
	/*
	//�鲢����
	void sort(){
		merge_sort(0, length-1);
	}
	*/
	//****************���ȶ�����***************************
	//ѡ������
	/*
	void sort(){
		//���ѭ���������Ϊ�Ե�iλ���д���������:data[i]���ǵ�i+1С�ģ�i��0��ʼ����Ϊ��
		for (int i = 0; i < length -1; i++) {
			for (int j = i + 1; j < length; j++) {
				//data[i]�����Ĳ��ϱȽϣ��൱���ҵ��Լ�������ķ�Χ����Сֵ�ŵ�data[i]��
				if (data[i] > data[j]) {
					swap(data[i], data[j]);
				}
			}
		}
	}
	*/
	//��������
	/*
	void sort(){
		quick_sort(0, length-1);
	}
	*/
	//ϣ������
	/*
	void sort(){
		//gap�����  swapped���ڴ�ѭ�����޽�������Ĭ��Ϊ0����û�н���
		int gap = length/2, swapped;
		do{
			do{
				swapped=0;
				//size-gap:���ǱȽϵĴ������������ǿ����һ��Ԫ�أ���Ӧ�ø���ǰ����gapλ��Ԫ�رȽϣ�����ǰ����gapλ��Ԫ��֮ǰ��Ԫ�ض���Ҫ�Ƚ��ˣ���ô��ʵ�Ƚϵ�ʱ����Ǻ����gapλ���ñȽϣ�
				//�ٸ����ӣ�size=8��gap=2��λ������0,1,2,3,4,5��ֵ����Ҫ�������2λ�����αȽϣ�6�Ļ���+2����8����������������ˣ������������Ǻ����gap��2��λ��6��7���ñȽ�
				for(int i = 0; i < length-gap ; i++){
					if(data[i]>data[i+gap])
					{
						swap(data[i], data[i+gap]);
						swapped=1;
					}
				}		
			}while(swapped);	//����һ��ѭ����û�н���������˵��ǰ�벿�ֶ���С�ڡ���벿�֣�����ǰ��gap����������Ѿ������򡱣������Խ�����һ�ֵ�gap
			//Ϊʲôͬһ��gap������Ҫ���ܽ��ж���أ����� 5 2 1 3 4��gap=2����һ�ν��ʱ1 2 5 3 4��swapped=1;���еڶ���gap=2ѭ����1 2 4 3 5������4,5�����ˣ���ѭ����û�н�����swapped=0��������һ��gap=2/2= 1��ѭ����
		}while(gap=gap/2);//���ϳ���2����gap����1������2�͵���0 ��ѭ��������������gap����1�����һ��ѭ����
	}*/
	int maxbit() //���������������ݵ����λ��
	{
		int d = 1; //��������λ��,��ʼ��Ϊ1
		int p = 10; // ÿ�γ���10���ǰ٣�ǧ����......
		for(int i = 0; i < length-1; ++i)
		{
			while(data[i] >= p)
			{
				p *= 10;
				++d;
			}
		}
		return d;
	}
		//��������
	void sort() 
	{
		int d = maxbit();
		int *tmp = new int[length];
		int *count = new int[10]; //������
		int i, j, k;
		int radix = 1; //���������ڻ�ȡ��Ӧλ�����Ĵ�С
		for(i = 1; i <= d; i++) //����λ��Ϊd�����Խ���d������
		{
			//ÿ�η���ǰ��ռ�����
			for(j = 0; j < 10; j++)
				count[j] = 0;

			//ͳ��ÿ��Ͱ(����ӦΪ��0��9)�еļ�¼�������Ǹ�λ��0���ж��٣���1���ж���........
			for(j = 0; j < length; j++) {
				k = (data[j] / radix) % 10; 
				count[k]++;
			}

			//���ݼ�¼���������i��Ͱ���ұ߽����������������ֵ���������������1��������һ��forѭ����tmp[count[k] - 1]
			//�����λ��ʱ�򣬸�λΪ0 ���ұ߽���count[0],��λΪ1���ұ߽����count[0]+count[1]����Ϊcountֻ�Ǽ���������ǰ��Ĳ���֪���Լ���������ұ߽硿
			for(j = 1; j < 10; j++)
				count[j] = count[j - 1] + count[j];
			
			//��������ı߽���������¼�����ռ���tmp������
			//��Ϊcount[k]���ұ߽磬�������ǴӺ���ǰ����
			for(j = length - 1; j >= 0; j--) {
				k = (data[j] / radix) % 10;
				tmp[count[k] - 1] = data[j];
				count[k]--;
			}
			
			//��ʱ����������ȡ��ԭ������
			for(j = 0; j < length; j++) 
				data[j] = tmp[j];

			//�´�ѭ������һ��λ
			radix = radix * 10;
		}
		//�ͷ��ڴ�
		delete[]tmp;
		delete[]count;
	}
};
int main() {
    int n;
    cin >> n;
    Vector arr(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        arr.insert(i, x);
    }
    arr.sort();
    arr.print();
    return 0;
}