#include <iostream>
#include <string>

using namespace std;

template <typename ElementType> class Vector {
public:
	~Vector<ElementType>();
	Vector<ElementType>();
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

class Point {
public:
	Point(int inputX, int inputY) :x(inputX), y(inputY) {}
	Point() : x(0), y(0) {}
	friend ostream& operator<<(ostream& os, const Point& temp);
	friend class Maze;
private:
	int x;
	int y;
};

ostream& operator<<(ostream& os, const Point& temp)
{
	os << '(' << temp.x << ',' << temp.y << ')';
	return os;
}

class Maze {
public:
	Maze(int size):mazeSize(size){}
	void printMap();
	bool DFS(Point &curPoint);
	void outputPath();
	void findPath();
private:
	char mazeMap[30][30] = {
		{"#########################"},
		{"#S0#####00#0000######000#"},
		{"#0000##0####000000000000#"},
		{"####0##0##0#0##0#######0#"},
		{"#0000#0##00#0###0000###0#"},
		{"#0##00##000000###0000000#"},
		{"#0##00000##0#0###0#######"},
		{"#0#####000#####00000#0###"},
		{"#0000000####00####000000#"},
		{"###0######0##0#0#0#0##0##"},
		{"###0####00##00000000##0##"},
		{"#0##00000###0####0#000###"},
		{"#0##########0#00##0######"},
		{"#0#0000000000####00000###"},
		{"#0#0#############0#0#0###"},
		{"###0000000000000#0#0#0###"},
		{"###############0#0###000#"},
		{"#00#0000000####000#####0#"},
		{"#00#0#####000#######0000#"},
		{"#00#0##000##000000000####"},
		{"###000##0############000#"},
		{"##00#0##0##0000##000#####"},
		{"##0000000000##0##0#00000#"},
		{"#000#0#00#####0000#####E#"},
		{"#########################"},
	};
	int knightMove[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	Vector<Point> path;
	int hasPassed[25][25] = { 0 };
	int mazeSize;
	int curSize = 0;
	Point start = Point(1, 1);
};

void Maze::printMap()
{
	cout << "迷宫地图为（S为起点，E为终点，X为路径上经过的点）：" << endl;
	for (int i = 0; i < mazeSize; i++)
	{
		cout << mazeMap[i] << endl;
	}
}

void Maze::findPath()
{
	DFS(start);
}

bool Maze::DFS(Point &curPoint)
{
	Point temp;
	path.pushBack(curPoint);
	curSize++;
	if (mazeMap[curPoint.x][curPoint.y] == 'E')
	{
		return true;
	}
	for (int i = 0; i < 4; i++)
	{
		temp.x = curPoint.x + knightMove[i][0];
		temp.y = curPoint.y + knightMove[i][1];
		if (mazeMap[temp.x][temp.y] != '#' && hasPassed[temp.x][temp.y] == 0)
		{
			hasPassed[temp.x][temp.y] = 1;
			if (DFS(temp))
			{
				mazeMap[curPoint.x][curPoint.y] = 'X';
				return true;
			}
		}
	}
	curSize--;
	path.popBack();
	return false;
}

void Maze::outputPath()
{
	if (curSize == 0)
	{
		cout << "迷宫的入口与出口不通!" << endl;
		return;
	}
	mazeMap[start.x][start.y] = 'S';
	printMap();
	cout << endl;
	cout << "迷宫路径：" << endl;
	for (int i = 0; i < curSize; i++)
	{
		cout << path[i];
		if (path[i].x < 10)
		{
			cout << ' ';
		}
		if (path[i].y < 10)
		{
			cout << ' ';
		}
		if (i != curSize - 1)
		{
			cout << "--→";
		}
		if ((i + 1) % 8 == 0)
		{
			cout << '\n';
		}
	}
}

int main()
{
	string input;
	Maze map(25);
	cout << "按任意键出现地图:";
	getline(cin, input);
	map.printMap();
	map.findPath();
	cout << "按任意键生成结果:";
	getline(cin, input);
	map.outputPath();
	return 0;
}