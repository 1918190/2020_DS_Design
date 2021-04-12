#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

int randomArray[100000000] = { 0 };
int tempArray[100000000] = { 0 };
long long exchangeNum = 0;
long long compareNum = 0;

class MT19937
{
public:
	int extractNumber()
	{
		int y;
		if (index >= N)
		{
			twist();
			index = 0;
		}
		y = mt[index];
		y ^= (y >> U) & D;
		y ^= (y << S) & B;
		y ^= (y << T) & C;
		y ^= (y >> L);
		index = index + 1;
		return y;
	}
	void seedMt(const int seed)
	{
		mt[0] = seed;
		for (int i = 1; i < N; i++)
		{
			mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
		}
		index = N;
	}
private:
	enum
	{
		W = 32,
		N = 624,
		M = 397,
		R = 31,
		A = 0x9908B0DF,
		U = 11,
		D = 0xFFFFFFFF,
		S = 7,
		B = 0x9D2C5680,
		T = 15,
		C = 0xEFC60000,
		L = 18,
		F = 1812433253,
		MASK_LOWER = (1ull << R) - 1,
		MASK_UPPER = (1ull << R)
	};
	void twist()
	{
		int i, x, xA;
		for (i = 0; i < N; i++)
		{
			x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);
			xA = x >> 1;
			if (x & 0x1)
			{
				xA ^= A;
			}
			mt[i] = mt[(i + M) % N] ^ xA;
		}
	}
	int mt[N] = { 0 };
	int index = N + 1;
};

void swap(int& x, int& y)
{
	exchangeNum++;
	int temp = x;
	x = y;
	y = temp;
}

void bubbleSort(int tempArray[], int length)//如果排到一半发现后面已经排好了（flag=false）则直接退出就行
{
	int i, j;
	bool flag = false;
	for (i = 0; i < length - 1; i++)
	{
		flag = false;
		for (j = 0; j < length - i - 1; j++)
		{
			compareNum++;
			if (tempArray[j] > tempArray[j + 1])
			{
				swap(tempArray[j], tempArray[j + 1]);
				flag = true;
			}
		}
		if (flag == false)
		{
			return;
		}
	}
}

void selectionSort(int tempArray[], int length)//每次都找出最大值和最小值，只用一半的遍历
{
	int left = 0;
	int	right = length - 1;
	int min = left;
	int max = right;
	while (left < right) 
	{
		min = left;
		max = right;
		for (int i = left; i <= right; i++) 
		{
			compareNum += 2;
			if (tempArray[min] > tempArray[i])
			{
				min = i;
			}
			if (tempArray[max] < tempArray[i])
			{
				max = i;
			}
		}
		if (min != left)
		{
			swap(tempArray[min], tempArray[left]);
		}
		if (left == max)
		{
			max = min;
		}
		if (max != right)
		{
			swap(tempArray[max], tempArray[right]);
		}
		left++;
		right--;
	}
}

void insertionSort(int tempArray[], int length)
{
	int i, j;
	int temp = 0;
	for (i = 1; i < length; i++)
	{
		temp = tempArray[i];
		for (j = i; j > 0 && tempArray[j - 1] > temp; j--)
		{
			compareNum++;
			exchangeNum++;
			tempArray[j] = tempArray[j - 1];
		}
		compareNum++;
		tempArray[j] = temp;
	}
}

void shellSort(int tempArray[], int length)//使用了sedgewick排序
{
	int Sedgewick[29] =
	{ 0, 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769,
	  146305, 260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929,
	  37730305, 67084289, 150958081, 268386305, 603906049, 1073643521 };
	// 9×4^k-9×2^k+1(k=1,2,3,4,5…) 和 4^k-3×2^k+1(k=2,3,4,5,6…)综合得到
	int i, j;
	int temp = 0;
	int gap = 0;
	int initGap = 0;
	while (Sedgewick[initGap] < length / 2)
	{
		initGap++;
	}
	gap = Sedgewick[initGap];
	while (gap > 0)
	{
		for (i = gap; i < length; i++)
		{
			compareNum++;
			if (tempArray[i] < tempArray[i - gap])
			{
				temp = tempArray[i];
				for (j = i - gap; j >= 0 && temp < tempArray[j]; j -= gap)
				{
					compareNum++;
					exchangeNum++;
					tempArray[j + gap] = tempArray[j];
				}
				compareNum++;
				tempArray[j + gap] = temp;
			}
		}
		initGap--;
		gap = Sedgewick[initGap];
	}
}

void partitionMedianOfThree(int tempArray[], int left, int right)
{
	compareNum += 3;
	int middle = (left + right) / 2;
	if (tempArray[right] < tempArray[middle])
	{
		swap(tempArray[right], tempArray[middle]);
	}
	if (tempArray[right] < tempArray[left])
	{
		swap(tempArray[right], tempArray[left]);
	}
	if (tempArray[left] < tempArray[middle])
	{
		swap(tempArray[left], tempArray[middle]);
	}
}

void qSort(int tempArray[], int left, int right)
{
	int i = 0, j = 0;
	int pivot = 0;
	if (left >= right)
	{
		return;
	}
	partitionMedianOfThree(tempArray, left, right);
	pivot = tempArray[left];
	if (left + 2 <= right)
	{
		i = left;
		j = right;
		while (true)
		{
			while (tempArray[++i] < pivot)
			{
				compareNum++;
			}
			compareNum++;
			while (tempArray[--j] > pivot)//[j]一定大
			{
				compareNum++;
			}
			compareNum++;
			if (i < j)
			{
				swap(tempArray[i], tempArray[j]);
			}
			else break;
		}
		swap(tempArray[j], tempArray[left]);
		qSort(tempArray, left, j - 1);
		qSort(tempArray, j + 1, right);
	}
}

void quickSort(int tempArray[], int length)//在序列长度达到一定大小的时候，使用插入排序效果更好(尾递归，多线程，聚集元素)
{
	qSort(tempArray, 0, length - 1);
}

void siftDown(int tempArray[], int start, int max)
{
	int current = start;
	int lessChild = 2 * current + 1;
	int temp = tempArray[current];
	while (lessChild <= max)
	{
		if (lessChild < max)
		{
			compareNum++;
			if (tempArray[lessChild] < tempArray[lessChild + 1])
			{
				lessChild++;
			}
		}
		compareNum++;
		if (temp >= tempArray[lessChild])
		{
			break;
		}
		else
		{
			exchangeNum++;
			tempArray[current] = tempArray[lessChild];
			current = lessChild;
			lessChild = 2 * lessChild + 1;
		}
	}
	tempArray[current] = temp;
}

void heapSort(int tempArray[], int length)
{
	int i;
	for (i = (length -2)/ 2; i >= 0; i--)
	{
		siftDown(tempArray, i, length - 1);
	}
	for (i = length - 1; i > 0; i--)
	{
		swap(tempArray[0], tempArray[i]);
		siftDown(tempArray, 0, i - 1);
	}
}

void merge(int tempArray[], int copyArray[], int left, int middle, int right)
{
	int temp1 = left;
	int temp2 = middle + 1;
	int current = left;
	while (temp1 <= middle && temp2 <= right)
	{
		exchangeNum++;
		compareNum++;
		if (copyArray[temp1] <= copyArray[temp2])
		{
			tempArray[current++] = copyArray[temp1++];
		}
		else 
		{
			tempArray[current++] = copyArray[temp2++];
		}
	}
	while (temp1 <= middle)
	{
		tempArray[current++] = copyArray[temp1++];
		exchangeNum++;
	}
	while (temp2 <= right)
	{
		tempArray[current++] = copyArray[temp2++];
		exchangeNum++;
	}
}

void mSort(int tempArray[], int copyArray[], int left, int right)//去除原数组序列到辅助数组的拷贝,测试待排序序列中左右半边是否已有序
{
	if (left >= right)
	{
		return;
	}
	int middle = (left + right) / 2;
	mSort(copyArray, tempArray, left, middle);
	mSort(copyArray, tempArray, middle + 1, right);
	compareNum++;
	if (copyArray[middle] <= copyArray[middle + 1])
	{
		for (int i = left; i <= right; i++)
		{
			tempArray[i] = copyArray[i];
			exchangeNum++;
		}
		return;
	}
	merge(tempArray, copyArray, left, middle, right);
}

void mergeSort(int tempArray[], int length)
{
	int* copyArray = new int[length];
	for (int i = 0; i < length; i++)
	{
		copyArray[i] = tempArray[i];
		exchangeNum++;
	}
	mSort(tempArray, copyArray, 0, length - 1);
	delete[] copyArray;
	copyArray = nullptr;
}

int getPart(int curData, int move)
{
	return (curData >> move) & 2047;
}

void radixSort(int tempArray[], int length)//基数2048
{
	int radix = 2048;
	int move[4] = { 0,11,22 };
	int* bucket = new int[length];
	int* count = new int[radix];
	int i, j, k;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < radix; j++)
		{
			count[j] = 0;
		}
		for (j = 0; j < length; j++)
		{
			count[getPart(tempArray[j], move[i])]++;
		}
		for (j = 1; j < radix; j++)
		{
			count[j] += count[j - 1];
		}
		for (j = length - 1; j >= 0; j--)
		{
			int k = getPart(tempArray[j], move[i]);
			bucket[count[k] - 1] = tempArray[j];
			exchangeNum++;
			count[k]--;
		}
		for (j = 0; j < length; j++)
		{
			tempArray[j] = bucket[j];
			exchangeNum++;
		}
	}
	delete[] bucket;
	delete[] count;
}

void menu()
{
	cout << "**\t\t排序算法比较\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t1---冒泡排序\t\t\t**" << endl;
	cout << "**\t\t2---选择排序\t\t\t**" << endl;
	cout << "**\t\t3---直接插入排序\t\t**" << endl;
	cout << "**\t\t4---希尔排序\t\t\t**" << endl;
	cout << "**\t\t5---快速排序\t\t\t**" << endl;
	cout << "**\t\t6---堆排序\t\t\t**" << endl;
	cout << "**\t\t7---归并排序\t\t\t**" << endl;
	cout << "**\t\t8---基数排序\t\t\t**" << endl;
	cout << "**\t\t9---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void copy(int num)
{
	for (int i = 0; i < num; i++)
	{
		tempArray[i] = randomArray[i];
	}
}

void creatRandomNum(int num)
{
	MT19937 M;
	M.seedMt(random_device{}());
	for (int i = 0; i < num; ++i)
	{
		randomArray[i] = M.extractNumber();
	}
}

bool check(int tempArray[], int length)
{
	int i;
	for (i = 0; i < length - 1; i++)
	{
		if (tempArray[i] > tempArray[i + 1])
		{
			cout << "排序出错！" << endl;
			return false;
		}
	}
	cout << "排序完成！" << endl;
	return true;
}

int main()
{
	menu();
	int num = 0;
	int choice = 0;
	string sortName = "";
	clock_t start = 0, end = 0;
	cout << "请输入要产生的随机数个数：";
	cin >> num;
	creatRandomNum(num);
	while (true)
	{
		cout << endl;
		cout << "请选择排序算法：" << "\t";
		cin >> choice;
		copy(num);
		sortName = "";
		exchangeNum = 0;
		compareNum = 0;
		start = clock();
		switch (choice)
		{
		case 1:
			bubbleSort(tempArray, num);
			sortName = "冒泡排序";
			break;
		case 2:
			selectionSort(tempArray, num);
			sortName = "选择排序";
			break;
		case 3:
			insertionSort(tempArray, num);
			sortName = "直接插入排序";
			break;
		case 4:
			shellSort(tempArray, num);
			sortName = "希尔排序";
			break;
		case 5:
			quickSort(tempArray, num);
			sortName = "快速排序";
			break;
		case 6:
			heapSort(tempArray, num);
			sortName = "堆排序";
			break;
		case 7:
			mergeSort(tempArray, num);
			sortName = "归并排序";
			break;
		case 8:
			radixSort(tempArray, num);
			sortName = "基数排序";
			break;
		default:
			return 0;
		}
		end = clock();
		cout << endl;
		if (check(tempArray, num))
		{
			cout << sortName << "所用时间是：" << "\t" << end - start << "毫秒" << endl;
			cout << sortName << "交换次数是：" << "\t" << exchangeNum << "次" << endl;
			cout << sortName << "比较次数是：" << "\t" << compareNum << "次" << endl;
		}
	}
	return 0;
}