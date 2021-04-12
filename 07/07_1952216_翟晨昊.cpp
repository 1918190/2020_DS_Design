#include<iostream>
#include<limits>

using namespace std;

template <typename ElementType> class Vector {
public:
	~Vector();
	Vector();
	ElementType& operator[](const int x);
	const ElementType& operator[](const int x)const;
	Vector<ElementType>(const Vector<ElementType>& rhs);
	Vector<ElementType>& operator=(const Vector<ElementType>& rhs);
	bool isFull();
	bool isEmpty();
	void pushBack(const ElementType& temp);
	void popBack();
	void clear();
	int getSize();
	void reSize(int newSize);
private:
	void extendSize();
	int size;
	int maxSize;
	ElementType* myVector;
};

template<typename ElementType>
Vector<ElementType>::Vector()
{
	size = 0;
	maxSize = 0;
	myVector = nullptr;
}

template<typename ElementType>
Vector<ElementType>::~Vector()
{
	clear();
}

template<typename ElementType>
ElementType& Vector<ElementType>::operator[](const int index)
{
	return *(myVector + index);
}


template<typename ElementType>
const ElementType& Vector<ElementType>::operator[](const int index)const
{
	return *(myVector + index);
}

template<typename ElementType>
Vector<ElementType>::Vector(const Vector<ElementType>& rhs)
{
	operator=(rhs);
}

template<typename ElementType>
Vector<ElementType>& Vector<ElementType>::operator=(const Vector<ElementType>& rhs)
{
	size = rhs.size;
	maxSize = rhs.maxSize;
	myVector = new ElementType[maxSize];
	for (int i = 0; i < size; i++)
	{
		myVector[i] = rhs[i];
	}
	return *this;
}

template<typename ElementType>
void Vector<ElementType>::extendSize()
{
	ElementType* temp = new ElementType[maxSize * 2 + 1];
	maxSize = maxSize * 2 + 1;
	for (int i = 0; i < size; i++)
	{
		temp[i] = myVector[i];
	}
	delete[]myVector;
	myVector = temp;
}

template<typename ElementType>
bool Vector<ElementType>::isFull()
{
	if (size == maxSize)
	{
		return true;
	}
	return false;
}

template<typename ElementType>
bool Vector<ElementType>::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
}


template<typename ElementType>
void Vector<ElementType>::pushBack(const ElementType& temp)
{
	if (isFull())
	{
		extendSize();
	}
	myVector[size++] = temp;
}

template<typename ElementType>
void Vector<ElementType>::popBack()
{
	if (!isEmpty())
	{
		size--;
	}
}

template<typename ElementType>
void Vector<ElementType>::clear()
{
	delete[] myVector;
	myVector = nullptr;
	size = 0;
	maxSize = 0;
}

template<typename ElementType>
int Vector<ElementType>::getSize()
{
	return size;
}

template<typename ElementType>
void Vector<ElementType>::reSize(int newSize)
{
	ElementType* temp = new ElementType[newSize + 1];
	if (newSize >= size)
	{
		for (int i = 0; i < size; i++)
		{
			temp[i] = myVector[i];
		}
	}
	else
	{
		for (int i = 0; i < newSize; i++)
		{
			temp[i] = myVector[i];
		}
	}
	clear();
	myVector = temp;
	maxSize = newSize + 1;
	size = newSize;
}

template<typename ElementType> class Greater{
public:
	bool operator()(const ElementType& E1, const ElementType& E2)
	{
		return  E1 > E2;
	}
};

template<typename ElementType> class Less{
public:
	bool operator()(const ElementType& E1, const ElementType& E2)
	{
		return E1 < E2;
	}
};

template<typename ElementType, typename Comparator> class Heap{
public:
	Heap() = default;
	~Heap();
	int getSize();
	void build(Vector<ElementType>& everyLength);
	void insert(const ElementType& inputData);
	bool pop();
	ElementType getTop();
	void makeEmpty();
private:
	Vector<ElementType> data;
	void siftDown(int start, int max);
	void siftUp(int start);
};

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::siftUp(int start)
{
	Comparator dataGreater;
	int current = start;
	int parent = (current - 1) / 2;
	ElementType temp = data[current];
	while (current > 0)
	{
		if (!dataGreater(data[parent], temp))
		{
			break;
		}
		else
		{
			data[current] = data[parent];
			current = parent;
			parent = (parent - 1) / 2;
		}
	}
	data[current] = temp;
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::siftDown(int start, int max)
{
	Comparator dataGreater;
	int current = start;
	int lessChild = 2 * current + 1;
	ElementType temp = data[current];
	while (lessChild <= max)
	{
		if (lessChild < max)
		{
			if (dataGreater(data[lessChild], data[lessChild + 1]))
			{
				lessChild++;
			}
		}
		if (!dataGreater(temp, data[lessChild]))
		{
			break;
		}
		else
		{
			data[current] = data[lessChild];
			current = lessChild;
			lessChild = 2 * lessChild + 1;
		}
	}
	data[current] = temp;
}

template<typename ElementType, typename Comparator>
Heap<ElementType, Comparator>::~Heap()
{
	makeEmpty();
}

template<typename ElementType, typename Comparator>
int Heap<ElementType, Comparator>::getSize()
{
	return data.getSize();
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::build(Vector<ElementType>& everyLength)
{
	for (int i = 0; i < everyLength.getSize(); i++)
	{
		data.pushBack(everyLength[i]);
	}
	int currentPos = (getSize() - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, getSize() - 1);
		currentPos--;
	}
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::insert(const ElementType& inputData)
{
	data.pushBack(inputData);
	siftUp(getSize() - 1);
}

template<typename ElementType, typename Comparator>
bool Heap<ElementType, Comparator>::pop()
{
	if (getSize() == 0)
	{
		return false;
	}
	data[0] = data[getSize() - 1];
	data.popBack();
	siftDown(0, getSize() - 1);
	return true;
}

template<typename ElementType, typename Comparator>
ElementType Heap<ElementType, Comparator>::getTop()
{
	return data[0];
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::makeEmpty()
{
	data.clear();
}

void input(Vector<int>& everyLength)
{
	int num = 0;
	int inputLength = 0;
	cout << "请输入木块数量：" << endl;
	cin >> num;
	while (cin.fail() || num <= 0 || num > 10000)
	{
		cout << "木块数量只能是正整数且不能超过10000!" << endl;
		cout << "请重新输入数量：" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> num;
	}
	cout << "请输入每块木头的长度：" << endl;
	for (int i = 0; i < num; i++)
	{
		cin >> inputLength;
		if (cin.fail() || inputLength <= 0)
		{
			cout << "木块长度只能是正整数!" << endl;
			cout << "请重新输入长度：" << endl;
			everyLength.clear();
			i = 0;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> inputLength;
		}
		everyLength.pushBack(inputLength);
	}
}

void calculate(Vector<int>& everyLength)
{
	Heap<int,Greater<int> > minHeap;
	int sum = 0;
	int newLength = 0;
	minHeap.build(everyLength);
	while (minHeap.getSize() > 1)
	{
		int length1 = minHeap.getTop();
		if (!minHeap.pop())
		{
			cout << "删除失败！";
			return;
		}
		int length2 = minHeap.getTop();
		if (!minHeap.pop())
		{
			cout << "删除失败！";
			return;
		}
		newLength = length1 + length2;
		sum += newLength;
		minHeap.insert(newLength);
	}
	cout << "最小花费为：" << sum << endl;
}

int main()
{
	Vector<int> everyLength;
	input(everyLength);
	calculate(everyLength);
	return 0;
}