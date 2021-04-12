#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

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
	void deQueue();
	ElementType getFront();
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
void LinkedQueue<ElementType>::deQueue()
{
	if (isEmpty())
	{
		return;
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
}

template<typename ElementType>
ElementType LinkedQueue<ElementType>::getFront()
{
	return front->next->number;
}

class CourseSystem;

class Course {
public:
	friend class CourseSystem;
	Course() = default;
	Course(string inputNumber, string inputName, int inputDegree, int inputTime, int inputSemester) :
		number(inputNumber), name(inputName), degree(inputDegree), time(inputTime), semester(inputSemester) {}
	Course& operator =(const Course& temp)
	{
		number = temp.number;
		name = temp.name;
		degree = temp.degree;
		time = temp.time;
		semester = temp.semester;
		orderInGraph = temp.orderInGraph;
		preCourse = temp.preCourse;
		return *this;
	}
	void clear();
private:
	string number;
	string name = "null";
	int degree = 0;
	int time = 0;
	int semester = 0;
	int orderInGraph = -1;
	Vector<int> preCourse;
};

void Course::clear()
{
	number = "";
	name = "null";
	degree = 0;
	time = 0;
	semester = 0;
	orderInGraph = -1;
	preCourse.clear();
}

class Edge {
public:
	Edge() = default;
	Edge(int vertex1, int vertex2) :
		current(vertex1), dest(vertex2) {}
	int current;
	int dest;
	Edge* next = nullptr;
};

template<typename NameType>
class Graph;

template<typename NameType>
class Vertex {
public:
	friend class Graph<NameType>;
	Vertex() = default;
	Vertex(int inputOrder, NameType inputName) :
		order(inputOrder), name(inputName) {}
private:
	int order;
	NameType name;
	Edge* head = nullptr;
};

template<typename NameType>
class Graph {
public:
	friend class CourseSystem;
	Graph() = default;
	~Graph();
	void clear();
	NameType getName(int order);
	Edge* getFirstEdge(int order);
	Edge* getNextEdge(Edge* curEdge);
	void insertVertex(NameType inputVertex);
	void insertEdge(int order1, int order2);
private:
	bool checkEdge(int order1, int order2);
	Vector<Vertex<NameType>*> vertexTable;
};

template<typename NameType>
Graph<NameType>::~Graph()
{
	clear();
}

template<typename NameType>
bool Graph<NameType>::checkEdge(int order1, int order2)
{
	if (order1 == order2)
	{
		return false;
	}
	Vertex<NameType>* pFirst = vertexTable[order1];
	Edge* pTemp = pFirst->head;
	while (pTemp != nullptr)
	{
		if (pTemp->dest == order2)
		{
			return true;
		}
		pTemp = pTemp->next;
	}
	return false;
}

template<typename NameType>
void Graph<NameType>::clear()
{
	Vertex<NameType>* pTemp = nullptr;
	Edge* pCurrent = nullptr;
	Edge* pNext = nullptr;
	for (int i = 0; i < vertexTable.getSize(); i++)
	{
		pTemp = vertexTable[i];
		pCurrent = pTemp->head;
		if (pCurrent != nullptr)
		{
			pNext = pCurrent->next;
			delete pCurrent;
			pCurrent = pNext;
		}
	}
}

template<typename NameType>
NameType Graph<NameType>::getName(int order)
{
	Vertex<NameType>* pTemp = vertexTable[order];
	return pTemp->name;
}

template<typename NameType>
Edge* Graph<NameType>::getFirstEdge(int order)
{
	Vertex<NameType>* pTemp = vertexTable[order];
	Edge* pHead = pTemp->head;
	if (pHead != nullptr)
	{
		return pHead;
	}
	else
	{
		return nullptr;
	}
}

template<typename NameType>
Edge* Graph<NameType>::getNextEdge(Edge* curEdge)
{
	return curEdge->next;
}

template<typename NameType>
void Graph<NameType>::insertVertex(NameType inputName)
{
	Vertex<NameType>* newVertex = new Vertex<NameType>(vertexTable.getSize(), inputName);
	vertexTable.pushBack(newVertex);
}

template<typename NameType>
void Graph<NameType>::insertEdge(int order1, int order2)
{
	Vertex<NameType>* pFirst = vertexTable[order1];
	Edge* pTemp = pFirst->head;
	if (pTemp == nullptr)
	{
		pFirst->head = new Edge(order1, order2);
	}
	else
	{
		while (pTemp->next != nullptr)
		{
			pTemp = pTemp->next;
		}
		pTemp->next = new Edge(order1, order2);
	}
}

class CourseSystem {
public:
	CourseSystem() = default;
	~CourseSystem();
	int stringToInt(string& str);
	bool inputData(fstream& in);
	bool outputData(fstream& out);
	void topologicalSort();
	bool selectCourse();
	void arrangeCourse(int semester);
private:
	bool judgeFixCourse(int semester, int& curScheduleTime);
	void arrangeThreeClass(int day, int first, Course& data);
	void arrangeTwoClass(int day, int first, Course& data);
	bool arrangeFiveClass(int day, int first, Course& data);
	bool arrangeFourClass(int day, int first, Course& data);
	int maxCourseNum[8] = { 0 };
	int scheduleMaxTime = 50;
	Vector<Vector<Course> > courseSchedule;
	Course courseTable[5][10];
	Vector<Course> allCourse;
	Vector<Course> fixCourse;
	Vector<Course> autoCourse;
	Graph<string> system;
	bool* isInSchedule = nullptr;
	int* inDegree = nullptr;
};

CourseSystem::~CourseSystem()
{
	delete[] inDegree;
	inDegree = nullptr;
	delete[] isInSchedule;
	isInSchedule = nullptr;
}

bool CourseSystem::judgeFixCourse(int semester, int& curScheduleTime)
{
	for (int i = 0; i < fixCourse.getSize(); i++)
	{
		if (fixCourse[i].semester == semester)
		{
			courseSchedule[semester - 1].pushBack(fixCourse[i]);
			curScheduleTime += fixCourse[i].time;
		}
	}
	if (courseSchedule[semester - 1].getSize() > maxCourseNum[semester - 1])
	{
		cout << "输入的学期课程数不合理!" << endl;
		return false;
	}
	else if (curScheduleTime > scheduleMaxTime)
	{
		cout << "课程设计存在问题" << endl;
		return false;
	}
	return true;
}

void CourseSystem::arrangeThreeClass(int day, int first, Course& data)
{
	courseTable[day][first] = data;
	courseTable[day][first + 1] = data;
	courseTable[day][first + 2] = data;
}

void CourseSystem::arrangeTwoClass(int day, int first, Course& data)
{
	courseTable[day][first] = data;
	courseTable[day][first + 1] = data;
}

bool CourseSystem::arrangeFiveClass(int day, int first, Course& data)
{
	for (int j = day + 2; j < 5; j++)
	{
		if (courseTable[j][0].time == 0)
		{
			arrangeThreeClass(day, first, data);
			arrangeTwoClass(j, 0, data);
			return true;
		}
		else if (courseTable[j][5].time == 0)
		{
			arrangeThreeClass(day, first, data);
			arrangeTwoClass(j, 5, data);
			return true;
		}
	}
	for (int j = day - 2; j >= 0; j--)
	{
		if (courseTable[j][0].time == 0)
		{
			arrangeThreeClass(day, first, data);
			arrangeTwoClass(j, 0, data);
			return true;
		}
		else if (courseTable[j][5].time == 0)
		{
			arrangeThreeClass(day, first, data);
			arrangeTwoClass(j, 5, data);
			return true;
		}
	}
	return false;
}

bool CourseSystem::arrangeFourClass(int day, int first, Course& data)
{
	for (int j = day + 2; j < 5; j++)
	{
		if (courseTable[j][0].time == 0)
		{
			arrangeTwoClass(day, first, data);
			arrangeTwoClass(j, 0, data);
			return true;
		}
		else if (courseTable[j][5].time == 0)
		{
			arrangeTwoClass(day, first, data);
			arrangeTwoClass(j, 5, data);
			return true;
		}
	}
	for (int j = day - 2; j >= 0; j--)
	{
		if (courseTable[j][0].time == 0)
		{
			arrangeTwoClass(day, first, data);
			arrangeTwoClass(j, 0, data);
			return true;
		}
		else if (courseTable[j][5].time == 0)
		{
			arrangeTwoClass(day, first, data);
			arrangeTwoClass(j, 5, data);
			return true;
		}
	}
	return false;
}

int CourseSystem::stringToInt(string& str)
{
	int cur = 0;
	int sum = 0;
	int multiple = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] == 'c')
		{
			break;
		}
		cur = 0 + str[i] - '0';
		sum += (cur * multiple);
		multiple *= 10;
		cur = 0;
	}
	return sum;
}

bool CourseSystem::inputData(fstream& in)
{
	int allCourseNum = 0;
	int sumCourseNum = 0;
	in.open("./in.txt", ios_base::in | ios_base::binary);
	if (in.is_open() == false)
	{
		cout << "文件打开失败，请检查文件是否存在！" << endl;
		return false;
	}
	cout << "请输入总课程数：";
	cin >> allCourseNum;
	if (allCourseNum <= 0 || in.fail())
	{
		cout << "总课程数不合法，排课软件将退出！" << endl;
		return false;
	}
	cout << "请输入每学期课程数：" << endl;
	for (int i = 0; i < 8; i++)
	{
		cin >> maxCourseNum[i];
		if (maxCourseNum[i] <= 0 || in.fail())
		{
			cout << "存在学期课程数不合法，排课软件将退出！" << endl;
			return false;
		}
		sumCourseNum += maxCourseNum[i];
	}
	while (cin.get() != '\n') continue;
	if (sumCourseNum != allCourseNum)
	{
		cout << "每学期所开的课程数值和与课程总数不相等，排课软件将退出！" << endl;
		return false;
	}
	for (int i = 0; i < allCourseNum; ++i)
	{
		Course curCourse;
		string s;
		getline(in, s);
		stringstream ss(s);
		ss >> curCourse.number;
		ss >> curCourse.name;
		ss >> curCourse.time;
		ss >> curCourse.semester;
		while (ss >> s)
		{
			curCourse.preCourse.pushBack(stringToInt(s) - 1);
			curCourse.degree++;
		}
		curCourse.orderInGraph = i;
		system.insertVertex(curCourse.number);
		allCourse.pushBack(curCourse);
		if (curCourse.semester == 0)
		{
			autoCourse.pushBack(curCourse);
		}
		else
		{
			fixCourse.pushBack(curCourse);
		}
	}
	in.close();
	for (int i = 0; i < allCourse.getSize(); i++)
	{
		for (int j = 0; j < allCourse[i].preCourse.getSize(); j++)
		{
			system.insertEdge(allCourse[i].preCourse[j], allCourse[i].orderInGraph);
		}
	}
	isInSchedule = new bool[allCourseNum];
	for (int i = 0; i < allCourseNum; i++)
	{
		isInSchedule[i] = false;
	}
	return true;
}

bool CourseSystem::outputData(fstream& out)
{
	out.open("./out.txt", ios_base::out | ios_base::binary);
	if (out.is_open() == false)
	{
		cout << "文件打开失败，请检查文件是否存在！" << endl;
		return false;
	}
	for (int i = 0; i < 8; i++)
	{
		arrangeCourse(i);
		out << "第" << i + 1 << "学期课表如下:" << endl;
		for (int hour = 0; hour < 10; hour++)
		{
			for (int day = 0; day < 5; day++)
			{
				out << courseTable[day][hour].name << '\t';
				if (courseTable[day][hour].name.size() <= 8)
				{
					out << '\t';
				}
				courseTable[day][hour].clear();
			}
			out << endl;
		}
		out << endl;
	}
	out.close();
	return true;
}

void CourseSystem::topologicalSort()
{
	int current = 0;
	LinkedQueue<int> temp;
	Vector<Course> sortVec;
	int num = autoCourse.getSize();
	inDegree = new int[num + 4];
	for (int i = 0; i < num; i++)
	{
		inDegree[i] = 0;
	}
	for (int i = 0; i < 3; i++)//将c01，c02，c03提前排进去
	{
		temp.enQueue(autoCourse[i].orderInGraph);
	}
	for (int i = 3; i < autoCourse.getSize(); i++)
	{
		inDegree[i] = autoCourse[i].degree;
		if (inDegree[i] == 0)
		{
			temp.enQueue(autoCourse[i].orderInGraph);
		}
	}
	while (!temp.isEmpty())
	{
		current = temp.getFront();
		temp.deQueue();
		for (int i = 0; i < autoCourse.getSize(); i++)
		{
			if (system.checkEdge(current, autoCourse[i].orderInGraph))
			{
				inDegree[i]--;
				if (inDegree[i] == 0)
				{
					temp.enQueue(autoCourse[i].orderInGraph);
				}
			}
		}
		sortVec.pushBack(allCourse[current]);
	}
	if (sortVec.getSize() != autoCourse.getSize())
	{
		cout << "课程中存在有向循环!" << endl;
		return;
	}
	else
	{
		autoCourse = sortVec;
	}
}

bool CourseSystem::selectCourse()
{
	bool canBeAdd = true;
	int lastLocation = 0;
	int curLocation = 0;
	int addCourseNum = 0;
	int curScheduleTime = 0;
	LinkedQueue<int> remainCourse;
	int remainNum = 0;
	courseSchedule.reSize(8);
	for (int i = 0; i < 8; i++)
	{
		remainNum = remainCourse.getSize();
		if (!judgeFixCourse(i + 1, curScheduleTime))
		{
			return false;
		}
		addCourseNum = maxCourseNum[i] - courseSchedule[i].getSize();
		while (addCourseNum > 0)
		{
			if (remainNum > 0)
			{
				curLocation = remainCourse.getFront();
				remainCourse.deQueue();
				remainNum--;
			}
			else if (remainNum == 0)
			{
				curLocation = lastLocation;
				remainNum--;
			}
			if (curLocation >= autoCourse.getSize())
			{
				cout << "无法成功按要求排课!" << endl;
				return false;
			}
			if ((curScheduleTime + autoCourse[curLocation].time) <= scheduleMaxTime)
			{
				for (int j = 0; j < autoCourse[curLocation].preCourse.getSize(); j++)
				{
					if (isInSchedule[autoCourse[curLocation].preCourse[j]] == false)
					{
						remainCourse.enQueue(curLocation);
						canBeAdd = false;
						break;
					}
				}
				if (canBeAdd)
				{
					courseSchedule[i].pushBack(autoCourse[curLocation]);
					curScheduleTime += autoCourse[curLocation].time;
					addCourseNum--;
				}
			}
			else
			{
				cout << "一学期安排的学时过多，请妥善安排课程!" << endl;
				return false;
			}
			canBeAdd = true;
			curLocation++;
		}
		if (curLocation > lastLocation)
		{
			lastLocation = curLocation;
		}
		while (remainNum > 0)
		{
			int temp = 0;
			temp = remainCourse.getFront();
			remainCourse.deQueue();
			remainCourse.enQueue(temp);
			remainNum--;
		}
		for (int j = 0; j < courseSchedule[i].getSize(); j++)
		{
			isInSchedule[courseSchedule[i][j].orderInGraph] = true;
		}
		curScheduleTime = 0;
		addCourseNum = 0;
	}
	return true;
}

void CourseSystem::arrangeCourse(int semester)
{
	Course temp;
	Vector<Course> notInSchedule;
	int threeClassNum = 0;
	int threeToTwo = 0;
	int sixTimeClass = 0;
	bool isInTable = false;
	int i, j;
	if (courseSchedule[semester][0].time != 4)
	{
		threeClassNum += (courseSchedule[semester][0].time / 3);
	}
	for (i = 1; i < courseSchedule[semester].getSize(); i++)
	{
		temp = courseSchedule[semester][i];
		if (courseSchedule[semester][i].time != 4)
		{
			threeClassNum += (courseSchedule[semester][i].time / 3);
			sixTimeClass += (courseSchedule[semester][i].time / 3 - 1);
		}
		for (j = i; j > 0 && courseSchedule[semester][j - 1].time > temp.time; j--)
		{
			courseSchedule[semester][j] = courseSchedule[semester][j - 1];
		}
		courseSchedule[semester][j] = temp;
	}
	if (threeClassNum > 10)
	{
		threeToTwo = (threeClassNum - 9) / 2;//threeToTwo不会超过三
	}
	while (sixTimeClass - threeToTwo > 4)
	{
		threeToTwo++;
	}
	for (i; i > 0; i--)
	{
		temp = courseSchedule[semester][i - 1];
		if (temp.time == 6)//七门六学时课
		{
			if (threeToTwo > 0)
			{
				if (threeToTwo == 3)
				{
					arrangeTwoClass(1, 0, temp);
					arrangeTwoClass(3, 0, temp);
					arrangeTwoClass(3, 5, temp);
				}
				else if (threeToTwo == 2)
				{
					arrangeTwoClass(0, 0, temp);
					arrangeTwoClass(2, 0, temp);
					arrangeTwoClass(4, 0, temp);
				}
				else if (threeToTwo == 1)
				{
					arrangeTwoClass(0, 5, temp);
					arrangeTwoClass(2, 5, temp);
					arrangeTwoClass(4, 5, temp);
				}
				threeToTwo--;
			}
			else 
			{
				for (int k = 0; k < 3; k++)
				{
					if (courseTable[k][2].time == 0)
					{
						arrangeThreeClass(k, 2, temp);
						arrangeThreeClass(k + 2, 2, temp);
						break;
					}
					else if (courseTable[k][7].time == 0)
					{
						arrangeThreeClass(k, 7, temp);
						arrangeThreeClass(k + 2, 7, temp);
						break;
					}
				}
			}
		}
		else if (temp.time == 5)
		{
			for (int k = 0; k < 5; k++)
			{
				if (courseTable[k][2].time == 0)
				{
					if (arrangeFiveClass(k, 2, temp))
					{
						break;
					}
				}
				else if (courseTable[k][7].time == 0)
				{
					if (arrangeFiveClass(k, 7, temp))
					{
						break;
					}
				}
				if (k == 4)
				{
					notInSchedule.pushBack(temp);
				}
			}
		}
		else if (temp.time == 4)//5门四学时课
		{
			for (int k = 0; k < 5; k++)
			{
				if (courseTable[k][0].time == 0)
				{
					if (arrangeFourClass(k, 0, temp))
					{
						break;
					}
				}
				else if (courseTable[k][5].time == 0)
				{
					if (arrangeFourClass(k, 5, temp))
					{
						break;
					}
				}
				if (k == 4)
				{
					notInSchedule.pushBack(temp);
				}
			}
		}
		else if (temp.time == 3)
		{
			for (int k = 0; k < 5; k++)
			{
				if (courseTable[k][2].time == 0)
				{
					arrangeThreeClass(k, 2, temp);
					break;
				}
				else if (courseTable[k][7].time == 0)
				{
					arrangeThreeClass(k, 7, temp);
					break;
				}
				if (k == 4)
				{
					notInSchedule.pushBack(temp);
				}
			}
		}
	}
	int num = 0;
	i = 0;
	if (notInSchedule.getSize() > 0)
	{
		temp = notInSchedule[i];
		for (j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (courseTable[j][k].time == 0)
				{
					courseTable[j][k] = temp;
					num++;
				}
				if (num == temp.time)
				{
					i++;
					if (i == notInSchedule.getSize())
					{
						return;
					}
					temp = notInSchedule[i];
					num = 0;
				}
			}
		}
	}
}

int main()
{
	fstream in, out;
	CourseSystem myCourseSystem;
	if (myCourseSystem.inputData(in))
	{
		myCourseSystem.topologicalSort();
		if (myCourseSystem.selectCourse())
		{
			myCourseSystem.outputData(out);
		}
	}
	return 0;
}

/*
课表中学期为0且前置课程不要求c03的一共有12门课，而c03最早也只能在
第三学期才能学，前三个学期的指定课程有三节英语和一节语文，共四节，
因此可以得出前三学期安排的最多课程数目为12+4=16节，超过这个数目就无法进行排课。
拓展可以得到：
c03课所在学期n与之前学期课程总和不能超过13+n节，否则排课失败。
为了使该限制对课表的影响最小，在拓扑排序时将它们三个优先加入队列，
将c01，c02，c03分别优先安排在第一学期，第二学期与第三学期。
这样就使得只有前三学期有影响。

第一学期最多八节课
*/