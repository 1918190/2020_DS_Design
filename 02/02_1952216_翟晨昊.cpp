#include<iostream>
#include<string>
#include<limits>
using namespace std;

template <typename ElementType>
class LinkList;

template <typename ElementType>
class Node {
public:
	friend class LinkList<ElementType>;
	Node() = default;
	Node(ElementType& inputData) :data(inputData) {}
	ElementType getData();
private:
	ElementType data;
	Node<ElementType>* next = nullptr;
};

template <typename ElementType>
ElementType Node<ElementType>::getData()
{
	return data;
}

template <typename ElementType>
class LinkList {
public:
	LinkList();
	~LinkList();
	void append(ElementType inputData);
	void deleteList();
	void goToNext();
	bool readAndCheck();
	Node<ElementType>* getCurrent();
	void display();
private:
	Node<ElementType>* head;
	Node<ElementType>* current;
	int size;
};

template <typename ElementType>
LinkList<ElementType>::LinkList()
{
	head = new Node<ElementType>;
	current = head;
	size = 0;
}

template <typename ElementType>
LinkList<ElementType>::~LinkList()
{
	deleteList();
}

template <typename ElementType>
void LinkList<ElementType>::append(ElementType inputData)
{
	Node<ElementType>* insert = new Node<ElementType>(inputData);
	current->next = insert;
	current = insert;
	size++;
}

template <typename ElementType>
void LinkList<ElementType>::deleteList()
{
	Node<ElementType>* temp = nullptr;
	while (size > 0)
	{
		temp = head->next;
		delete head;
		head = temp;
		size--;
	}
	delete temp;
}

template <typename ElementType>
void LinkList<ElementType>::goToNext()
{
	current = current->next;
}

template <typename ElementType>
Node<ElementType>* LinkList<ElementType>::getCurrent()
{
	return current;
}

template <typename ElementType>
bool LinkList<ElementType>::readAndCheck()
{
	int prevNum = 1;
	int curNum = 0;
	while (cin >> curNum)
	{
		if (curNum == -1)
		{
			append(curNum);
			current = head->next;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else if (curNum < prevNum)
		{
			cout << "输入不满足是正整数非降序序列" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}
		else
		{
			append(curNum);
			prevNum = curNum;
		}
	}
	if (curNum == 0 || curNum == prevNum || cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "输入不合法！！！" << endl;
		return false;
	}
	return true;
}

template <typename ElementType>
void LinkList<ElementType>::display()
{
	if (size == 0)
	{
		cout << "NULL" << endl;
	}
	else
	{
		current = head;
		while (current->next != nullptr)
		{
			goToNext();
			cout << current->getData() << ' ';
		}
	}

}

template <typename ElementType>
LinkList<ElementType>* takeIntersection(LinkList<ElementType>* list1, LinkList<ElementType>* list2)
{
	LinkList<ElementType>* intersectionList = new LinkList<ElementType>;
	while (list1->getCurrent()->getData() != -1 && list2->getCurrent()->getData() != -1)
	{
		if (list1->getCurrent()->getData() < list2->getCurrent()->getData())
		{
			list1->goToNext();
		}
		else if (list1->getCurrent()->getData() > list2->getCurrent()->getData())
		{
			list2->goToNext();
		}
		else if (list1->getCurrent()->getData() == list2->getCurrent()->getData())
		{
			intersectionList->append(list1->getCurrent()->getData());
			list1->goToNext();
			list2->goToNext();
		}
    }
	return intersectionList;
}

int main()
{
	cout << "使用本程序可以来求出两个链表的交集" << endl;
	cout << "输入分2行，分别在每行给出由若干个正整数构成的非降序序列，"
		 <<"用-1表示序列的结尾（-1不属于这个序列）。数字用空格间隔。" 
		 << endl;
	cout << "输入Y来开始程序，输入N退出程序" << endl;
	bool isRead1 = false;
	bool isRead2 = false;
	string judge = "";
	cin >> judge;
	while (judge == "Y")
	{

		LinkList<int> list1, list2;
		LinkList<int>* intersection;
		cout << "请输入第一个序列:" << endl;
		isRead1 = list1.readAndCheck();
		cout << "请输入第二个序列:" << endl;
		isRead2 = list2.readAndCheck();
		if (isRead1 && isRead2)
		{
			intersection = takeIntersection(&list1, &list2);
			cout << "两个非降序序列的交集序列为:" << endl;
			intersection->display();
			cout << endl;
			intersection->deleteList();
		}
		else
		{
			cout << "两个序列并未全部合法输入！" << endl;
		}
		cout << "是否要再进行一组求链表的交集（Y为是，N为否）：";
		cin >> judge;
		list1.deleteList();
		list2.deleteList();
	}
	if (judge != "Y" && judge != "N")
	{
		cout << "输入不符合要求，将会退出程序！" << endl;
	}
	cout << "成功退出程序！" << endl;
	return 0;
}