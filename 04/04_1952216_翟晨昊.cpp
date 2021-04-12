#include <iostream>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

#define ERROR 1e-6

template <typename ElementType> class Vector{
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

template <typename ElementType> class Stack
{
public:
	void push(ElementType input);
	void pop();
	ElementType top();
	bool isEmpty();
	int getSize();
	void clear();
private:
	Vector<ElementType> stack;
};

template<typename ElementType>
void Stack<ElementType>::push(ElementType input)
{
	stack.pushBack(input);
}

template<typename ElementType>
void Stack<ElementType>::pop()
{
	stack.popBack();
}

template<typename ElementType>
ElementType Stack<ElementType>::top()
{
	return stack[stack.getSize() - 1];
}

template<typename ElementType>
bool Stack<ElementType>::isEmpty()
{
	return stack.getSize() == 0;
}

template<typename ElementType>
int Stack<ElementType>::getSize()
{
	return stack.getSize();
}

template<typename ElementType>
void Stack<ElementType>::clear()
{
	stack.clear();
}

class CharData {
public:
	CharData() = default;
	CharData(char inputChar):character(inputChar){}
	int priority = 0;
	char character = 0;
	bool isNum = false;
};

class CalculateSystem {
public:
	void clear();
	void unaryAnalysis(string& s);
	bool analysis(const string& s);
	bool calculate();
	int calculateNum();
	bool operation();
	double getAnswer();
private:
	Vector<CharData> inputExpression;
	Stack<CharData> operatorStack;
	Stack<double> numStack;
	string eachNum = "";
	int current = 0;
	int left = 0;
};

void CalculateSystem::clear()
{
	inputExpression.clear();
	operatorStack.clear();
	numStack.clear();
	eachNum = "";
	current = 0;
	left = 0;
}

void CalculateSystem::unaryAnalysis(string& s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (i == 0)
		{
			if (s[i] == '+')
			{
				s[i] = 1;
			}
			else if (s[i] == '-')
			{
				s[i] = 2;
			}
		}
		else
		{
			if ((s[i - 1] != ')' && s[i - 1] != '.') && (s[i - 1] < '0' || s[i - 1] > '9'))
			{
				if (s[i] == '+')
				{
					s[i] = 1;
				}
				else if (s[i] == '-')
				{
					s[i] = 2;
				}
			}
		}
	}
}

bool CalculateSystem::analysis(const string& s)
{
	if (s.size() == 0)
	{
		cout << "未输入表达式！" << endl;
		return false;
	}
	size_t i = 0;
	for (i = 0; i < s.size() - 1; i++)
	{
		CharData temp(s[i]);
		if (s[i] < '0' || s[i] > '9')
		{
			switch (s[i])
			{
			case '.':
				temp.priority = 8;
				break;
			case 1:
				temp.priority = 7;
				break;
			case 2:
				temp.priority = 7;
				break;
			case '(':
				temp.priority = 6;
				left++;
				break;
			case '^':
				temp.priority = 5;
				break;
			case '%':
				temp.priority = 4;
				break;
			case '*':
				temp.priority = 4;
				break;
			case '/':
				temp.priority = 4;
				break;
			case '+':
				temp.priority = 3;
				break;
			case '-':
				temp.priority = 3;
				break;
			case ')':
				temp.priority = 1;
				if (s[i - 1] == '(')
				{
					cout << "出现空括号!" << endl;
					return false;
				}
				left--;
				break;
			default:
				cout << "出现未定义的符号！" << endl;
				return false;
			}
		}
		else
		{
			temp.isNum = true;
		}
		if (left < 0)
		{
			cout << "左括号和右括号未成功匹配！" << endl;
			return false;
		}
		inputExpression.pushBack(temp);
	}
	if (s[i] != '=')
	{
		cout << "表达式的结尾不为等号！" << endl;
		return false;
	}
	if (left != 0)
	{
		cout << "左括号和右括号数量未成功匹配！" << endl;
		return false;
	}
	return true;
}

bool CalculateSystem::calculate()
{
	for (current = 0; current < inputExpression.getSize(); current++)
	{
		if (inputExpression[current].isNum)
		{
			eachNum += inputExpression[current].character;
		}
		else
		{
			if (eachNum != "")
			{
				numStack.push(calculateNum());
			}
			while (!operatorStack.isEmpty())
			{
				if (inputExpression[current].priority <= operatorStack.top().priority)
				{
					if (inputExpression[current].priority == 7 && operatorStack.top().priority == 7)
					{
						break;
					}
					if (!operation())
					{
						cout << "在解析第" << current + 1 << "位字符时出现问题！" << endl;
						cout << "输入的表达式不合法或遇到未知错误！" << endl;
						return false;
					}
				}
				else
				{
					break;
				}
			}
			if (inputExpression[current].character == '(')
			{
				inputExpression[current].priority = 2;
			}
			operatorStack.push(inputExpression[current]);
			eachNum = "";
		}
	}
	if (eachNum != "")
	{
		numStack.push(calculateNum());
	}
	while (!operatorStack.isEmpty() && !numStack.isEmpty())
	{
		if (!operation())
		{
			cout << "输入的表达式不合法或遇到未知错误！" << endl;
			return false;
		}
	}
	if (operatorStack.getSize() != 0 || numStack.getSize() != 1)
	{
		cout << "输入的表达式不合法!" << endl;
		return false;
	}
	return true;
}

int CalculateSystem::calculateNum()
{
	int multiple = 1;
	int sum = 0;
	for (size_t i = eachNum.size(); i > 0; i--)
	{
		sum += ((eachNum[i - 1] - '0') * multiple);
		multiple *= 10;
	}
	return sum;
}

bool CalculateSystem::operation()
{
	if (numStack.isEmpty())
	{
		return false;
	}
	double temp1 = numStack.top();
	double temp2 = 0.0;
	switch (operatorStack.top().character)
	{
	case 1:
		if (numStack.getSize() >= 1)
		{
			temp1 = temp1;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		if (numStack.getSize() >= 1)
		{
			temp1 = -temp1;
			numStack.pop();
			numStack.push(temp1);
		}
		else
		{
			return false;
		}
		break;
	case '.':
		if (numStack.getSize() >= 2)
		{
			if (current != inputExpression.getSize())
			{
				if (inputExpression[current].character == '.')
				{
					return false;
				}
			}
			if (eachNum.size() == 0)
			{
				return false;
			}
			for (size_t i = 0; i < eachNum.size(); i++)
			{
				temp1 = temp1 / 10;
			}
			numStack.pop();
			temp2 = numStack.top();
			temp2 += temp1;
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '^'://x不能为负数且y为小数，或者x为0且y小于等于0
		if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			if ((temp2 < 0) && (static_cast<int>(temp1) != temp1))
			{
				return false;
			}
			else if ((temp2 == 0) && (temp1 <= 0))
			{
				return false;
			}
			temp2 = pow(temp2, temp1);
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '%':
		if (abs(temp1) < ERROR)
		{
			cout << "除数不能是0!" << endl;
			return false;
		}
		else if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			temp2 = static_cast<int>(temp2) % static_cast<int>(temp1);
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '*':
		if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			temp2 = temp2 * temp1;
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '/':
		if (abs(temp1)<ERROR)
		{
			cout << "除数不能是0!" << endl;
			return false;
		}
		else if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			temp2 = temp2 / temp1;
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '+':
		if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			temp2 = temp2 + temp1;
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '-':
		if (numStack.getSize() >= 2)
		{
			numStack.pop();
			temp2 = numStack.top();
			temp2 = temp2 - temp1;
			numStack.pop();
			numStack.push(temp2);
		}
		else
		{
			return false;
		}
		break;
	case '(':
		inputExpression[current].priority = 10;
		break;
	case ')':
		break;
	}
	operatorStack.pop();
	return true;
}

double CalculateSystem::getAnswer()
{
	return numStack.top();
}

int main()
{
	CalculateSystem arithmetic;
	string expression = "";
	string judge = "Y";
	cout << "本程序为算术表达式求解程序，支持包括加减，乘除取余，乘方和括号等操作符。" << endl;
	cout << "如果取模运算中含有小数，则会忽略小数点及小数点后的数。" << endl;
	while (judge == "Y")
	{
		cout<<"请输入您要计算的表达式：" << endl;
		cin >> expression;
		arithmetic.unaryAnalysis(expression);
		if (arithmetic.analysis(expression))
		{
			if (arithmetic.calculate())
			{
				cout << "算术表达式的结果为：";
				cout << arithmetic.getAnswer() << endl;
			}
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "程序执行完毕，是否还要重新计算新的表达式（Y为是）：";
		cin >> judge;
		arithmetic.clear();
	}
	cout << "程序即将退出，欢迎下次使用！" << endl;
	return 0;
}