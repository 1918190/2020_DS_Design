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

template <typename ElementType>
class LinkedQueue;

template<typename ElementType>
class LinkedNode {
public:
	friend class LinkedQueue<ElementType>;
	LinkedNode() = default;
	LinkedNode(const ElementType& inputNum) : number(inputNum) {};
private:
	LinkedNode<ElementType>* next = nullptr;
	ElementType number = 0;
};

template<typename ElementType>
class LinkedQueue {
public:
	LinkedQueue();
	~LinkedQueue();
	void makeEmpty();
	int getSize();
	bool isEmpty();
	void enQueue(const ElementType& inputData);
	bool deQueue();
	ElementType getFront();
	bool checkNumber(ElementType curNum);
private:
	int size;
	LinkedNode<ElementType>* front;
	LinkedNode<ElementType>* rear;
};

template<typename ElementType>
LinkedQueue<ElementType>::LinkedQueue()
{
	front = rear = new LinkedNode<ElementType>();
	size = 0;
}

template<typename ElementType>
LinkedQueue<ElementType>::~LinkedQueue()
{
	makeEmpty();
	front = nullptr;
	rear = nullptr;
}

template<typename ElementType>
void LinkedQueue<ElementType>::makeEmpty()
{
	LinkedNode<ElementType>* temp = nullptr;
	while (size > 0)
	{
		temp = front->next;
		delete front;
		front = temp;
		size--;
	}
	delete temp;
}

template<typename ElementType>
int LinkedQueue<ElementType>::getSize()
{
	return size;
}

template<typename ElementType>
bool LinkedQueue<ElementType>::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
}

template<typename ElementType>
void LinkedQueue<ElementType>::enQueue(const ElementType& inputData)
{
	LinkedNode<ElementType>* temp = new LinkedNode<ElementType>(inputData);
	rear->next = temp;
	rear = rear->next;
	size++;
}

template<typename ElementType>
bool LinkedQueue<ElementType>::deQueue()
{
	if (isEmpty())
	{
		return false;
	}
	LinkedNode<ElementType>* temp = front->next;
	front->next = temp->next;
	delete temp;
	temp = nullptr;
	size--;
	if (size == 0)
	{
		rear = front;
	}
	return true;
}

template<typename ElementType>
ElementType LinkedQueue<ElementType>::getFront()
{
	return front->next->number;
}

template<typename ElementType>
bool LinkedQueue<ElementType>::checkNumber(ElementType curNum)
{
	LinkedNode<int>* temp = front;
	for (int i = 0; i < size; i++)
	{
		temp = temp->next;
		if (temp->number == curNum)
		{
			return false;
		}
	}
	return true;
}

void init(int& customerNum)
{
	cout << "请在一行内输入顾客的总数和每位顾客的编号(录入等于总数后将不再录入）:" << endl;
	cin >> customerNum;
	while (customerNum <= 0 || customerNum > 1000)
	{
		cout << "输入人数数量不正确或超出上限！" << endl;
		cout << "请重新输入：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> customerNum;
	}
}

bool customerClassification(LinkedQueue<int>& oddA, LinkedQueue<int>& evenB, int customerNum)
{
	int curNum = 0;
	for (int i = 0; i < customerNum; i++)
	{
		cin >> curNum;
		if (curNum <= 0 || cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入不合法！！！";
			return false;
		}
		if (curNum % 2 == 1)
		{
			if (!oddA.checkNumber(curNum))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "序列中存在两个编号相同的客户!";
				return false;
			}
			oddA.enQueue(curNum);
		}
		else if (curNum % 2 == 0)
		{
			if (!evenB.checkNumber(curNum))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "序列中存在两个编号相同的客户!";
				return false;
			}
			evenB.enQueue(curNum);
		}
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
}

void businessProcessing(LinkedQueue<int>& oddA, LinkedQueue<int>& evenB, Vector<int>&output)
{
	while (!oddA.isEmpty() && !evenB.isEmpty())
	{
		output.pushBack(oddA.getFront());
		if (!oddA.deQueue())
		{
			break;
		}
		if (!oddA.isEmpty())
		{
			output.pushBack(oddA.getFront());
			if (!oddA.deQueue())
			{
				break;
			}
		}
		output.pushBack(evenB.getFront());
		if (!evenB.deQueue())
		{
			break;
		}
	}
	while (!oddA.isEmpty())
	{
		output.pushBack(oddA.getFront());
		if (!oddA.deQueue())
		{
			break;
		}
	}
	while (!evenB.isEmpty())
	{
		output.pushBack(evenB.getFront());
		if (!evenB.deQueue())
		{
			break;
		}
	}
}

int main()
{
	string judge = "Y";
	int customerNum = 0;
	cout << "欢迎使用银行业务办理系统！" << endl;
	while (judge == "Y")
	{
		LinkedQueue<int> oddA;
		LinkedQueue<int> evenB;
		Vector<int> output;
		init(customerNum);
		if (customerClassification(oddA, evenB, customerNum))
		{
			businessProcessing(oddA, evenB, output);
			cout << "业务处理序列为：" << endl;
			for (int i = 0; i < output.getSize(); i++)
			{
				cout << output[i];
				if (i != output.getSize() - 1)
				{
					cout << ' ';
				}
			}
		}
		cout << endl;
		cout << "是否要再进行一组录入(Y为是):";
		cin >> judge;
	}
	cout << "欢迎再次使用！" << endl;
	return 0;
}