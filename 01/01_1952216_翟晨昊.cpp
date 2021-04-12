#include<iostream>
#include<string>
#include<limits>
using namespace std;

class Student {
public:
	Student() = default;
	Student(string tempID, string tempN, string tempS, string tempA, string tempC):
		ID(tempID),name(tempN),sex(tempS),age(tempA),applicationCategory(tempC){}
	string getID();
	Student& operator =(const Student& temp);
	friend ostream& operator<<(ostream& os, const Student& temp);
	friend istream& operator>>(istream& is, Student& temp);
private:
	string ID;
	string name;
	string sex;
	string age;
	string applicationCategory;
};

string Student::getID()
{
	return ID;
}

Student& Student::operator =(const Student& temp)
{
	ID = temp.ID;
	name = temp.name;
	sex = temp.sex;
	age = temp.age;
	applicationCategory = temp.applicationCategory;
	return *this;
}

ostream& operator<<(ostream& os, const Student& temp)
{
	os << temp.ID << '\t' << temp.name << '\t' << temp.sex << '\t' << temp.age << '\t' << temp.applicationCategory;
	return os;
}

istream& operator>>(istream& is, Student& temp)
{
	is >> temp.ID >> temp.name >> temp.sex >> temp.age >> temp.applicationCategory;
	return is;
}

template <typename ElementType>
class LinkList;

template <typename ElementType>
class InformationSystem;

template <typename ElementType>
class Node {
public:
	Node() = default;
	Node(ElementType& inputStu) :data(inputStu) {}
	friend class LinkList<ElementType>;
	friend class InformationSystem<ElementType>;
private:
	ElementType data;
	Node<ElementType>* next = nullptr;
	Node<ElementType>* prev = nullptr;
};

template <typename ElementType>
class LinkList {
public:
	LinkList()
	{
		head = new Node<ElementType>;
		size = 0;
	}
	~LinkList();
	int getSize();
	void append(ElementType& inputStu, int position);
	Node<ElementType>* findByID(string studentID);
	Node<ElementType>* findByLocation(int position);
	void pop(Node<ElementType>* deleteStu);
	void change(ElementType& changeStu, int position);
	void display();
private:
	Node<ElementType>* head;
	int size;
};

template <typename ElementType>
LinkList<ElementType>::~LinkList()
{
	while (size > 0)
	{
		head = head->next;
		delete head->prev;
		size--;
	}
	delete head;
}

template <typename ElementType>
int LinkList<ElementType>::getSize()
{
	return size;
}

template <typename ElementType>
void LinkList<ElementType>::append(ElementType& inputStu, int position)
{
	Node<ElementType>* insert = new Node<ElementType>(inputStu);
	Node<ElementType>* current = head;
	for (int i = 1; i < position; i++)
	{
		current = current->next;
	}
	if (position != size + 1)
	{
		current->next->prev = insert;
		insert->next = current->next;
	}
	insert->prev = current;
	current->next = insert;
	size++;
}

template <typename ElementType>
Node<ElementType>* LinkList<ElementType>::findByID(string studentID)
{
	Node<ElementType>* current = head;
	for (int i = 0; i < size; i++)
	{
		current = current->next;
		if (studentID == current->data.getID())
		{
			return current;
		}
	}
	return nullptr;
}

template <typename ElementType>
Node<ElementType>* LinkList<ElementType>::findByLocation(int position)
{
	Node<ElementType>* current = head;
	for (int i = 0; i < position; i++)
	{
		current = current->next;
	}
	return current;
}

template <typename ElementType>
void LinkList<ElementType>::pop(Node<ElementType>* deleteStu)
{
	if (deleteStu->next == nullptr)
	{
		deleteStu->prev->next = nullptr;
	}
	else
	{
		deleteStu->prev->next = deleteStu->next;
		deleteStu->next->prev = deleteStu->prev;
	}
	delete deleteStu;
	size--;
}

template <typename ElementType>
void LinkList<ElementType>::change(ElementType& changeStu, int position)
{
	Node<ElementType>* current = head;
	for (int i = 0; i < position; i++)
	{
		current = current->next;
	}
	current->data = changeStu;
}

template <typename ElementType>
void LinkList<ElementType>::display()
{
	Node<ElementType>* current = head;
	for (int i = 0; i < size; i++)
	{
		current = current->next;
		cout << current->data << endl;
	}
}

template <typename ElementType>
class InformationSystem {
public:
	void init();
	void append();
	void popByID();
	void popByLocation();
	void findByID();
	void findByLocation();
	void change();
	void display();
private:
	ElementType headline;
	LinkList<ElementType> studentInformation;
};

template <typename ElementType>
void InformationSystem<ElementType>::init()
{
	int studentNum = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	cin >> studentNum;
	while (studentNum <= 0 || cin.fail())
	{
		cout << "考生人数只能是正整数！" << endl;
		cout << "请重新输入考生人数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin >> studentNum;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	for (int i = 0; i < studentNum; i++)
	{
		ElementType inputStu;
		cin >> inputStu;
		studentInformation.append(inputStu, i + 1);
	}
	headline = ElementType(string("考号"), string("姓名"), string("性别"), string("年龄"), string("报考类别"));
}

template <typename ElementType>
void InformationSystem<ElementType>::append()
{
	cout << "请输入你要插入的考生位置：";
	int position = 0;
	cin >> position;
	while (position <= 0 || position > studentInformation.getSize() + 1 || cin.fail())
	{
		cout << "插入位置不正确！" << endl;
		cout << "请重新输入插入位置：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> position;
	}
	cout << "请依次输入要插入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	ElementType inputStu;
	cin >> inputStu;
	while (studentInformation.findByID(inputStu.getID()) != nullptr)
	{
		cout << "该考号已被其他考生使用，请检查是否录入错误并重新输入！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> inputStu;
	}
	studentInformation.append(inputStu, position);
	cout << "插入完成！" << endl;
}

template <typename ElementType>
void InformationSystem<ElementType>::popByID()
{
	cout << "请输入要删除考生的考号：" << endl;
	string inputID = "";
	cin >> inputID;
	Node<ElementType>* deleteStu = studentInformation.findByID(inputID);
	if (deleteStu == nullptr)
	{
		cout << "该考号对应考生不存在，请检查是否输入错误！" << endl;
		return;
	}
	else 
	{
		cout << "你删除的考生的信息为：" << endl;
		cout << deleteStu->data << endl;
		studentInformation.pop(deleteStu);
		cout << "删除成功！" << endl;
	}
}

template <typename ElementType>
void InformationSystem<ElementType>::popByLocation()
{
	cout << "请输入要删除考生的位置：" << endl;
	int inputLocation = 0;
	cin >> inputLocation;
	if (inputLocation > studentInformation.getSize() || inputLocation <= 0 || cin.fail())
	{
		cout << "该位置对应考生不存在，请检查是否输入错误！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	else
	{
		Node<ElementType>* deleteStu = studentInformation.findByLocation(inputLocation);
		cout << "你删除的考生的信息为：" << endl;
		cout << deleteStu->data << endl;
		studentInformation.pop(deleteStu);
		cout << "删除成功！" << endl;
	}
}

template <typename ElementType>
void InformationSystem<ElementType>::findByID()
{
	cout << "请输入要查找的考生的考号：" << endl;
	string findID = "";
	cin >> findID;
	Node<ElementType>* findStu = studentInformation.findByID(findID);
	if (findStu == nullptr)
	{
		cout << "该考号对应考生不存在，请检查是否输入错误！" << endl;
		return;
	}
	else
	{
		cout << headline << endl;
		cout << findStu->data << endl;
		cout << "查找成功！" << endl;
	}
}

template <typename ElementType>
void InformationSystem<ElementType>::findByLocation()
{
	cout << "请输入要查找的考生的位置：" << endl;
	int findLocation = 0;
	cin >> findLocation;
	if (findLocation > studentInformation.getSize() || findLocation <= 0 || cin.fail())
	{
		cout << "该位置对应考生不存在，请检查是否输入错误！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	else
	{
		Node<ElementType>* findStu = studentInformation.findByLocation(findLocation);
		cout << headline << endl;
		cout << findStu->data << endl;
		cout << "查找成功！" << endl;
	}
}

template <typename ElementType>
void InformationSystem<ElementType>::change()
{
	cout << "请输入你要修改的考生的位置：";
	int position = 0;
	cin >> position;
	while (position <= 0 || position > studentInformation.getSize() || cin.fail())
	{
		cout << "位置输入不正确！" << endl;
		cout << "请重新输入位置：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> position;
	}
	cout << "请依次输入修改后的考号，姓名，性别，年龄及报考类别：" << endl;
	ElementType changeStu;
	cin >> changeStu;
	if (studentInformation.findByID(changeStu.getID()) != nullptr)
	{
		cout << "该考号已被其他考生使用，请检查是否录入错误！" << endl;
		return;
	}
	else
	{
		studentInformation.change(changeStu, position);
		cout << "修改完成" << endl;
	}
}

template <typename ElementType>
void InformationSystem<ElementType>::display()
{
	cout << "目前考生数量：" << studentInformation.getSize() << endl;
	cout << headline << endl;
	studentInformation.display();
}

int main()
{
	InformationSystem<Student> testSystem;
	testSystem.init();
	while (true)
	{
		cout << "请选择您要进行的操作（1为插入，2为按考号删除，3为按位置删除，"
			 << "4为按考号查找，5为按位置查找，6为修改，7为统计，0为取消操作）:" 
			 << endl;
		int operater;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> operater;
		switch (operater)
		{
		case 1:
			testSystem.append();
			break;
		case 2:
			testSystem.popByID();
			break;
		case 3:
			testSystem.popByLocation();
			break;
		case 4:
			testSystem.findByID();
			break;
		case 5:
			testSystem.findByLocation();
			break;
		case 6:
			testSystem.change();
			break;
		case 7:
			break;
		case 0:
			cout << "成功退出系统！" << endl;
			return 0;
		default:
			cout << "操作数输入不正确，请重新输入！" << endl;
			break;
		}
		cout << '\n';
		testSystem.display();
		cout << '\n';
	}
	return 0;
}