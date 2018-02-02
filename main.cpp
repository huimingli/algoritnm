#include<iostream>
#include<algorithm>
using namespace std;
void selectSort(int data[], int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (data[j] < data[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(data[minIndex], data[i]);
		}
	}
}

void insertSort(int data[], int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j >= 0 && data[j] < data[j - 1]; j--) {
			swap(data[j], data[j - 1]);
		}
	}
}

void bubbleSort(int data[], int n) {
	bool isSwaped = false;
	do {
		for (int i = 1; i < n; i++) {
			if (data[i] < data[i - 1]) {
				swap(data[i], data[i - 1]);
				isSwaped = true;
			}
		}
		n--;
	} while (n > 0 && isSwaped);
}

void shiftDown(int data[], int k, int n) {
	while (2 * k + 1 < n) {
		int j = 2 * k + 1;
		if (j + 1 < n&&data[j] < data[j + 1])
			j++;
		if (data[k] > data[j])
			break;
		swap(data[k], data[j]);
		k = j;
	}
}

void heapSort(int data[], int n) {
	for (int i = (n - 1) / 2; i >= 0; i--) {
		shiftDown(data, i, n);
	}

	for (int i = n - 1; i > 0; i--) {
		swap(data[0], data[i]);
		shiftDown(data, 0, i);
	}
}

void _quick(int data[], int low, int high) {
	if (low >= high)
		return;
	int v = data[low];
	int i = low + 1;
	int lt = low;
	int gt = high + 1;
	while (i < gt) {
		if (data[i] < v) {
			swap(data[i], data[lt + 1]);
			lt++;
			i++;
		}
		else if (data[i > v]) {
			swap(data[i], data[gt - 1]);
			gt--;
		}
		else {
			i++;
		}
	}
	swap(data[low], data[lt]);
	_quick(data, low, lt - 1);
	_quick(data, lt + 1, high);
}

void quickSort(int data[], int n) {
	_quick(data, 0, n-1);
}

void __merge(int data[], int low, int mid, int high) {
	int *arr = new int[high - low + 1];
	for (int i = low; i <= high; i++) {
		arr[i - low] = data[i];
	}
	int i = low, j = mid + 1;
	for (int k = low; k <= high; k++) {
		if (i > mid) {
			data[k] = arr[j - low];
			j++;
		}
		else if (j > high) {
			data[k] = arr[i - low];
			i++;
		}
		else if (arr[i - low] < arr[j - low]) {
			data[k] = arr[i - low];
			i++;
		}
		else {
			data[k] = arr[j - low];
			j++;
		}
	}
}

void _merge(int data[], int low, int high) {
	if (low >= high)
		return;
	int mid = (high - low) / 2 + low;
	_merge(data, low, mid);
	_merge(data, mid + 1, high);
	if (data[mid] > data[mid + 1])
		__merge(data, low, mid, high);
}

void mergeSort(int data[], int n) {
	_merge(data, 0, n - 1);
}

void mergeBottom(int data[], int n) {
	for (int sz = 1; sz <= n; sz += sz) {
		for (int i = 0; i < n; i += sz + sz) {
			__merge(data, i, i + sz - 1, min(n - 1, i + sz + sz - 1));
		}
	}
}

int *nexta = nullptr;
void getNext(const string & pattern) {
	int m = pattern.length();

	nexta = new int[m];
	int j = -1;
	nexta[0] = -1;

	for (int i = 1; i < m; i++) {
		while (j != -1 && pattern[i] != pattern[j + 1])
			j = nexta[j];
		if (pattern[i] == pattern[j + 1])
			j++;
		nexta[i] = j;
	}
}
 

int KMP(const string text, const  string &pattern) {
	int numcount = 0;
	int m = pattern.length(), n = text.length();
	int j = -1;
	getNext(pattern);
	for (int i = 0; i < n; i++) {
		while (j != -1 && text[i] != pattern[j + 1])
			j = nexta[j];
		if (text[i] == pattern[j + 1])
			j++;
		if (j == m - 1) {
			numcount++;
			j = nexta[j];
		}
	}
	return numcount;
}
/*
*求数据的最大位数,决定排序次数
*/
int maxbit(int data[], int n)
{
	int d = 1; //保存最大的位数  
	int p = 10;
	for (int i = 0; i < n; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}
void radixsort(int data[],  int n) //基数排序  
{
	int d = maxbit(data, n);
	int *tmp = new int[n];
	int count[10]; //计数器  
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序  
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器  
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数  
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶  
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中  
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中  
			data[j] = tmp[j];
		radix = radix * 10;
	}
}
void shellSort(int list[],int n) {
	int gap = n / 2;

	while (1 <= gap) {
		// 把距离为 gap 的元素编为一个组，扫描所有组
		for (int i = gap; i < n; i++) {
			int j = 0;
			int temp = list[i];

			// 对距离为 gap 的元素组进行排序
			for (j = i - gap; j >= 0 && temp < list[j]; j = j - gap) {
				list[j + gap] = list[j];
			}
			list[j + gap] = temp;
		}
		gap = gap / 2; // 减小增量
	}
}
int main() {
	int data[] = { 21,2,33,12,1,21,100,67,56,444,231,890 };
	shellSort(data, 12);
	for (int d : data) {
		cout << d << " ";
	}
	cout << endl;
	string text = "sdhsdkjkj";
	 
	string pattern = "kj";
	cout << KMP(text, pattern) << endl;
	 
	system("pause");
	return EXIT_SUCCESS;
}
