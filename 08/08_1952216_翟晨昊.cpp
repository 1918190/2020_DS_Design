#include <iostream>
#include <limits>

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
		/*ElementType* p = &myVector[size];
		delete p;
		p = nullptr;*/
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

template <typename Key, typename ElementType>
class AVLTree;

template <typename Key, typename ElementType>
class AVLTree;

template <typename Key, typename ElementType>
class AVLTreeNode {
public:
	friend class AVLTree<Key, ElementType>;
	AVLTreeNode() = default;
	AVLTreeNode(Key inputKey, ElementType inputData) :
		dataKey(inputKey), data(inputData) {}
	~AVLTreeNode() = default;
private:
	Key dataKey;
	ElementType data;
	int height = 0;
	AVLTreeNode<Key, ElementType>* left = nullptr;
	AVLTreeNode<Key, ElementType>* right = nullptr;
};

template <typename Key, typename ElementType>
class AVLTree {
public:
	friend class Genealogy;
	AVLTree() :root(nullptr), size(0) {}
	~AVLTree();
	ElementType getData(AVLTreeNode<Key, ElementType>* ptr);
	void makeEmpty();
	AVLTreeNode<Key, ElementType>* find(Key findK);
	AVLTreeNode<Key, ElementType>* insert(Key insertK, ElementType insertData);
	bool remove(Key removeK);
	void change(Key changeOldK, Key changeNewK);
private:
	int  max(int x, int y);
	int  getHeight(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* findPriorNode(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* findNextNode(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* rotateL(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* rotateR(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* rotateLR(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* rotateRL(AVLTreeNode<Key, ElementType>* ptr);
	void makeEmpty(AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* find(Key findK, AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* insert(Key insertK, ElementType insertData, AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* remove(Key removeK, AVLTreeNode<Key, ElementType>* ptr);
	AVLTreeNode<Key, ElementType>* root;
	int size;
};

template<typename Key, typename ElementType>
AVLTree<Key, ElementType>::~AVLTree()
{
	makeEmpty();
}

template<typename Key, typename ElementType>
ElementType AVLTree<Key, ElementType>::getData(AVLTreeNode<Key, ElementType>* ptr)
{
	return ptr->data;
}

template<typename Key, typename ElementType>
void AVLTree<Key, ElementType>::makeEmpty()
{
	makeEmpty(root);
	root = nullptr;
	size = 0;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::find(Key findK)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	return find(findK, root);
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::insert(Key insertK, ElementType insertData)
{
	size++;
	root = insert(insertK, insertData, root);
	return root;
}

template<typename Key, typename ElementType>
bool AVLTree<Key, ElementType>::remove(Key removeK)
{
	if (root != nullptr)
	{
		size--;
		root = remove(removeK, root);
		return true;
	}
	return false;
}

template<typename Key, typename ElementType>
void AVLTree<Key, ElementType>::change(Key changeOldK, Key changeNewK)
{
	AVLTreeNode<Key, ElementType>* changeNode = find(changeOldK, root);
	if (changeNode != nullptr)
	{
		ElementType tempData = changeNode->data;
		AVLTreeNode<Key, ElementType>* newRoot = insert(changeNewK, tempData, root);
		root = remove(changeOldK, newRoot);
	}
}

template<typename Key, typename ElementType>
int AVLTree<Key, ElementType>::max(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}

template<typename Key, typename ElementType>
int AVLTree<Key, ElementType>::getHeight(AVLTreeNode<Key, ElementType>* ptr)
{
	if (ptr != nullptr)
	{
		return ptr->height;
	}
	return 0;
};

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::findPriorNode(AVLTreeNode<Key, ElementType>* ptr)
{
	ptr = ptr->left;
	if (ptr != nullptr)
	{
		while (ptr->right != nullptr)
		{
			ptr = ptr->right;
		}
	}
	return ptr;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::findNextNode(AVLTreeNode<Key, ElementType>* ptr)
{
	ptr = ptr->right;
	if (ptr != nullptr)
	{
		while (ptr->left != nullptr)
		{
			ptr = ptr->left;
		}
	}
	return ptr;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::rotateL(AVLTreeNode<Key, ElementType>* ptr)
{
	AVLTreeNode<Key, ElementType>* pNewRoot = ptr->right;
	ptr->right = pNewRoot->left;
	pNewRoot->left = ptr;
	ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
	pNewRoot->height = max(getHeight(pNewRoot->left), getHeight(pNewRoot->right)) + 1;
	return pNewRoot;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::rotateR(AVLTreeNode<Key, ElementType>* ptr)
{
	AVLTreeNode<Key, ElementType>* pNewRoot = ptr->left;
	ptr->left = pNewRoot->right;
	pNewRoot->right = ptr;
	ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
	pNewRoot->height = max(getHeight(pNewRoot->left), getHeight(pNewRoot->right)) + 1;
	return pNewRoot;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::rotateLR(AVLTreeNode<Key, ElementType>* ptr)
{
	ptr->left = rotateL(ptr->left);
	return rotateR(ptr); ptr = ptr->left;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::rotateRL(AVLTreeNode<Key, ElementType>* ptr)
{
	ptr->right = rotateR(ptr->right);
	return rotateL(ptr);
}

template<typename Key, typename ElementType>
void AVLTree<Key, ElementType>::makeEmpty(AVLTreeNode<Key, ElementType>* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	if (ptr->left != nullptr)
	{
		makeEmpty(ptr->left);
	}
	if (ptr->right != nullptr)
	{
		makeEmpty(ptr->right);
	}
	delete ptr;
	ptr = nullptr;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::find(Key findK, AVLTreeNode<Key, ElementType>* ptr)
{
	if (ptr == nullptr)
	{
		return nullptr;
	}
	if (findK < ptr->dataKey)
	{
		return find(findK, ptr->left);
	}
	else if (findK > ptr->dataKey)
	{
		return find(findK, ptr->right);
	}
	else return ptr;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::insert(Key insertK, ElementType insertData, AVLTreeNode<Key, ElementType>* ptr)
{
	if (ptr == nullptr)//寻找到插入的位置
	{
		ptr = new AVLTreeNode<Key, ElementType>(insertK, insertData);
	}
	else if (insertK > ptr->dataKey)//插入值比当前结点值大，插入到当前结点的右子树上
	{
		ptr->right = insert(insertK, insertData, ptr->right);
		if (getHeight(ptr->right) - getHeight(ptr->left) == 2)//插入后出现失衡
		{
			if (insertK > ptr->right->dataKey)//情况一：插入右子树的右节点，进行左旋
			{
				ptr = rotateL(ptr);
			}
			else if (insertK < ptr->right->dataKey)//情况三：插入右子树的左节点,进行先右再左旋转(=hao)
			{
				ptr = rotateRL(ptr);
			}
		}
	}
	else if (insertK < ptr->dataKey)//插入值比当前节点值小，插入到当前结点的左子树上
	{
		ptr->left = insert(insertK, insertData, ptr->left);
		if (getHeight(ptr->left) - getHeight(ptr->right) == 2)//如果插入导致失衡
		{
			if (insertK < ptr->left->dataKey)//情况二：插入到左子树的左孩子节点上，进行右旋
			{
				ptr = rotateR(ptr);
			}
			else if (insertK > ptr->left->dataKey)//情况四：插入到左子树的右孩子节点上，进行先左后右旋转(=hao)
			{
				ptr = rotateLR(ptr);
			}
		}
	}
	ptr->height = max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
	return ptr;
}

template<typename Key, typename ElementType>
AVLTreeNode<Key, ElementType>* AVLTree<Key, ElementType>::remove(Key removeK, AVLTreeNode<Key, ElementType>* ptr)
{
	if (ptr != nullptr)
	{
		if (removeK == ptr->dataKey)//找到删除的节点
		{
			//因AVL也是二叉排序树，删除节点要维护其二叉排序树的条件
			if (ptr->left != nullptr && ptr->right != nullptr)//若左右都不为空
			{
				// 左子树比右子树高,在左子树上选择节点进行替换
				if (getHeight(ptr->left) > getHeight(ptr->right))
				{
					//使用左子树最大节点来代替被删节点，而删除该最大节点
					AVLTreeNode<Key, ElementType>* pPrior = findPriorNode(ptr);//左子树最大节点
					ptr->dataKey = pPrior->dataKey;
					ptr->data = pPrior->data;//将最大节点的值覆盖当前结点
					ptr->left = remove(pPrior->dataKey, ptr->left);//递归地删除最大节点
				}
				else//在右子树上选择节点进行替换
				{
					//使用最小节点来代替被删节点，而删除该最小节点
					AVLTreeNode<Key, ElementType>* pNext = findNextNode(ptr);//右子树的最小节点
					ptr->dataKey = pNext->dataKey;
					ptr->data = pNext->data;//将最小节点值覆盖当前结点
					ptr->right = remove(pNext->dataKey, ptr->right);//递归地删除最小节点
				}

			}
			else
			{
				AVLTreeNode<Key, ElementType>* pTemp = ptr;
				if (ptr->left != nullptr)
				{
					ptr = ptr->left;
				}
				else if (ptr->right != nullptr)
				{
					ptr = ptr->right;
				}
				else
				{
					ptr = nullptr;
				}
				delete pTemp;
				pTemp = nullptr;
			}

		}
		else if (removeK > ptr->dataKey)//要删除的节点比当前节点大，则在右子树进行删除
		{
			ptr->right = remove(removeK, ptr->right);
			//删除右子树节点导致不平衡:相当于情况二或情况四
			if (getHeight(ptr->left) - getHeight(ptr->right) == 2)
			{
				//相当于在左子树上插入右节点造成的失衡（情况四）
				if (getHeight(ptr->left->right) > getHeight(ptr->left->left))
				{
					ptr = rotateLR(ptr);
				}
				else//相当于在左子树上插入左节点造成的失衡（情况二）
				{
					ptr = rotateR(ptr);
				}
			}
		}
		else if (removeK < ptr->dataKey)//要删除的节点比当前节点小，则在左子树进行删除
		{
			ptr->left = remove(removeK, ptr->left);
			//删除左子树节点导致不平衡：相当于情况三或情况一
			if (getHeight(ptr->right) - getHeight(ptr->left) == 2)
			{
				//相当于在右子树上插入左节点造成的失衡（情况三）
				if (getHeight(ptr->right->left) > getHeight(ptr->right->right))
				{
					ptr = rotateRL(ptr);
				}
				else//相当于在右子树上插入右节点造成的失衡（情况一）
				{
					ptr = rotateL(ptr);
				}
			}
		}
		return ptr;
	}
	return nullptr;
}

template<typename ElementType> class Greater {
public:
	bool operator()(const ElementType& E1, const ElementType& E2)
	{
		return *E1 > *E2;
	}
};

template<typename ElementType> class Less {
public:
	bool operator()(const ElementType& E1, const ElementType& E2)
	{
		return *E1 < *E2;
	}
};

template<typename ElementType, typename Comparator> class Heap {
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

template<typename NameType, typename ElementType>
class Edge {
public:
	Edge() = default;
	Edge(int vertex1, int vertex2, ElementType weight) :
		current(vertex1), dest(vertex2), cost(weight) {}
	friend bool operator<(const Edge<NameType, ElementType>& rhs1,const Edge<NameType, ElementType>& rhs2)
	{
		return rhs1.cost < rhs2.cost;
	}
	friend bool operator>(const Edge<NameType, ElementType>& rhs1,const Edge<NameType, ElementType>& rhs2)
	{
		return rhs1.cost > rhs2.cost;
	}
	int current;
	int dest;
	ElementType cost;
	Edge<NameType, ElementType>* next = nullptr;
};

template<typename NameType, typename ElementType>
class Graph;

template<typename NameType, typename ElementType>
class Vertex {
public:
	friend class Graph<NameType, ElementType>;
	Vertex() = default;
	Vertex(int inputOrder, NameType inputName) :
		order(inputOrder), name(inputName) {}
private:
	int order;
	NameType name;
	Edge<NameType, ElementType>* head = nullptr;
};

class PowerGridSystem;

template<typename NameType, typename ElementType>
class Graph {
public:
	friend class PowerGridSystem;
	Graph() = default;
	~Graph();
	void clear();
	NameType getName(int order);
	Edge<NameType, ElementType>* getFirstEdge(int order);
	Edge<NameType, ElementType>* getNextEdge(Edge<NameType, ElementType>* curEdge);
	void insertVertex(NameType inputVertex);
	void insertEdge(int order1, int order2, ElementType weight);
private:
	bool checkEdge(int order1, int order2);
	Vector<Vertex<NameType, ElementType>*> vertexTable;
};

template<typename NameType, typename ElementType>
Graph<NameType, ElementType>::~Graph()
{
	clear();
}

template<typename NameType, typename ElementType>
bool Graph<NameType, ElementType>::checkEdge(int order1, int order2)
{
	Vertex<NameType, ElementType>* pFirst = vertexTable[order1];
	Edge<NameType, ElementType>* pTemp = pFirst->head;
	while (pTemp != nullptr)
	{
		if (pTemp->dest == order2)
		{
			return false;
		}
		pTemp = pTemp->next;
	}
	return true;
}

template<typename NameType, typename ElementType>
void Graph<NameType, ElementType>::clear()
{
	Vertex<NameType, ElementType>* pTemp = nullptr;
	Edge<NameType, ElementType>* pCurrent = nullptr;
	Edge<NameType, ElementType>* pNext = nullptr;
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

template<typename NameType, typename ElementType>
NameType Graph<NameType, ElementType>::getName(int order)
{
	Vertex<NameType, ElementType>* pTemp = vertexTable[order];
	return pTemp->name;
}

template<typename NameType, typename ElementType>
Edge<NameType, ElementType>* Graph<NameType, ElementType>::getFirstEdge(int order)
{
	Vertex<NameType, ElementType>* pTemp = vertexTable[order];
	Edge<NameType, ElementType>* pHead = pTemp->head;
	if (pHead != nullptr)
	{
		return pHead;
	}
	else
	{
		return nullptr;
	}
}

template<typename NameType, typename ElementType>
Edge<NameType, ElementType>* Graph<NameType, ElementType>::getNextEdge(Edge<NameType, ElementType>* curEdge)
{
	return curEdge->next;
}

template<typename NameType, typename ElementType>
void Graph<NameType, ElementType>::insertVertex(NameType inputName)
{
	Vertex<NameType, ElementType>* newVertex = new Vertex<NameType, ElementType>(vertexTable.getSize(), inputName);
	vertexTable.pushBack(newVertex);
}

template<typename NameType, typename ElementType>
void Graph<NameType, ElementType>::insertEdge(int order1, int order2, ElementType weight)
{
	Vertex<NameType, ElementType>* pFirst = vertexTable[order1];
	Vertex<NameType, ElementType>* pSecond = vertexTable[order2];
	Edge<NameType, ElementType>* pTemp = pFirst->head;
	if (pTemp == nullptr)
	{
		pFirst->head = new Edge<NameType, ElementType>(order1, order2, weight);
	}
	else
	{
		while (pTemp->next != nullptr)
		{
			pTemp = pTemp->next;
		}
		pTemp->next = new Edge<NameType, ElementType>(order1, order2, weight);
	}
	pTemp = pSecond->head;
	if (pTemp == nullptr)
	{
		pSecond->head = new Edge<NameType, ElementType>(order2, order1, weight);
	}
	else
	{
		while (pTemp->next != nullptr)
		{
			pTemp = pTemp->next;
		}
		pTemp->next = new Edge<NameType, ElementType>(order2, order1, weight);
	}
}

class PowerGridSystem {
public:
	void menu();
	void build();
	void addEdge();
	void buildPrim();
	void display();
private:
	int getOrder();
	int getMaxAddEdge();
	bool checkName(Vector<string>& nodeName);
	int curEdgeNum = 0;
	Graph<string, int> powerGrid;
	AVLTree<string, int> vertexTree;
	Vector<Edge<string, int>*> result;
};

int PowerGridSystem::getOrder()
{
	return powerGrid.vertexTable.getSize();
}

int PowerGridSystem::getMaxAddEdge()
{
	return getOrder() * (getOrder() - 1) / 2;
}

bool PowerGridSystem::checkName(Vector<string>& nodeName)
{
	for (int i = 0; i < nodeName.getSize() - 1; i++)
	{
		for (int j = i + 1; j < nodeName.getSize(); j++)
		{
			if (nodeName[i] == nodeName[j])
			{
				cout << "创建的新顶点中含有重复的名称!" << endl;
				return false;
			}
		}
	}
	for (int i = 0; i < nodeName.getSize(); i++)
	{
		if (vertexTree.find(nodeName[i]) != nullptr)
		{
			cout << "存在新顶点名称与系统中已存在的顶点名称重复!" << endl;
			return false;
		}
	}
	return true;
}

void PowerGridSystem::menu()
{
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA---创建电网顶点\t\t**" << endl;
	cout << "**\t\tB---添加电网的边\t\t**" << endl;
	cout << "**\t\tC---构造最小生成树\t\t**" << endl;
	cout << "**\t\tD---显示最小生成树\t\t**" << endl;
	cout << "**\t\tE---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void PowerGridSystem::build()
{
	int vertexNum = 0;
	Vector<string> vertexName;
	cout << "请输入顶点的个数:";
	cin >> vertexNum;
	while (vertexNum <= 0 || cin.fail())
	{
		cout << "顶点的个数只能是正整数!" << endl;
		cout << "请重新输入顶点个数:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> vertexNum;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vertexName.reSize(vertexNum);
	cout << "请依次输入各顶点的名称:" << endl;
	for (int i = 0; i < vertexNum; i++)
	{
		cin >> vertexName[i];
	}
	while (!checkName(vertexName))
	{
		cout << "请重新依次输入各顶点的名称:" << endl;
		for (int i = 0; i < vertexNum; i++)
		{
			cin >> vertexName[i];
		}
	}
	for (int i = 0; i < vertexNum; i++)
	{
		vertexTree.insert(vertexName[i], getOrder());
		powerGrid.insertVertex(vertexName[i]);
	}
}

void PowerGridSystem::addEdge()
{
	string name1;
	string name2;
	AVLTreeNode<string, int>* vertex1 = nullptr;
	AVLTreeNode<string, int>* vertex2 = nullptr;
	int order1 = 0;
	int order2 = 0;
	int weight = 0;
	int edgeNum = 0;
	if (curEdgeNum >= getMaxAddEdge())
	{
		cout << "目前边的个数已至最大值，无法再添加！" << endl;
		return;
	}
	cout << "请输入添加边的个数:";
	cin >> edgeNum;
	while (edgeNum <= 0 || cin.fail() || edgeNum > (getMaxAddEdge() - curEdgeNum))
	{
		if (edgeNum <= 0 || cin.fail())
		{
			cout << "边的个数只能是正整数!" << endl;
		}
		else
		{
			cout << "输入后边的数量会超过最大值!" << endl;
		}
		cout << "请重新输入边个数:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> edgeNum;
	}
	curEdgeNum += edgeNum;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < edgeNum; i++)
	{
		cout << "请输入两个顶点及边:";
		while (true)
		{
			cin >> name1 >> name2 >> weight;
			vertex1 = vertexTree.find(name1);
			vertex2 = vertexTree.find(name2);
			if (name1 == name2)
			{
				cout << "输入的两个顶点相同!";
			}
			else if (vertex1 == nullptr)
			{
				cout << "第一个顶点不存在!";
			}
			else if (vertex2 == nullptr)
			{
				cout << "第二个顶点不存在!";
			}
			else if (weight <= 0 || cin.fail())
			{
				cout << "每一条边的花费必须是正整数!";
			}
			else
			{
				order1 = vertexTree.getData(vertex1);
				order2 = vertexTree.getData(vertex2);
				if (powerGrid.checkEdge(order1, order2))
				{
					powerGrid.insertEdge(order1, order2, weight);
					break;
				}
				else
				{
					cout << "此两个顶点之间已经存在边!";
				}
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl;
			cout << "请重新输入两个顶点及边:";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void PowerGridSystem::buildPrim()
{
	if (getOrder() == 0)
	{
		cout << "系统中没有顶点!" << endl;
		return;
	}
	else if (getOrder() == 1)
	{
		cout << "系统中没有边!" << endl;
		return;
	}
	int num = getOrder();
	int count = 1;
	int order = 0;
	Edge<string, int>* nextEdge = nullptr;
	Edge<string, int>* minEdge = nullptr;
	string init;
	Heap<Edge<string,int>*,Greater<Edge<string, int>*> > heap;
	AVLTreeNode<string, int>* initVertex = nullptr;
	bool* isIn = new bool[num];
	result.clear();
	cout << "请输入起始顶点:";
	cin >> init;
	initVertex = vertexTree.find(init);
	while (initVertex == nullptr)
	{
		cout << "此顶点不在系统之中!" << endl;
		cout << "请重新输入：";
		cin >> init;
		initVertex = vertexTree.find(init);
	}
	for (int i = 0; i < num; i++)
	{
		isIn[i] = false;
	}
	order = vertexTree.getData(initVertex);
	isIn[order] = true;
	while (count < num)
	{
		nextEdge = powerGrid.getFirstEdge(order);
		while (nextEdge != nullptr)
		{
			if (isIn[nextEdge->dest] == false)
			{
				heap.insert(nextEdge);
			}
			nextEdge = powerGrid.getNextEdge(nextEdge);
		}
		if (heap.getSize() == 0)
		{
			cout << "目前的电力系统并未连通!" << endl;
			delete[] isIn;
			isIn = nullptr;
			return;
		}
		while (heap.getSize() != 0)
		{
			minEdge = heap.getTop();
			if (isIn[minEdge->dest] == false)
			{
				isIn[minEdge->dest] = true;
				order = minEdge->dest;
				result.pushBack(minEdge);
				heap.pop();
				count++;
				break;
			}
			else
			{
				heap.pop();
			}
		}
	}
	delete[] isIn;
	isIn = nullptr;
	cout << "Prim算法成功!" << endl;
}

void PowerGridSystem::display()
{
	Vertex<string, int>* pCurrent = nullptr;
	Vertex<string, int>* pDest = nullptr;
	if ((result.getSize() != (getOrder() - 1)) || (getOrder() == 1))
	{
		cout << "最小生成树未成功生成!" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为:" << endl;
	for (int i = 0; i < result.getSize(); i++)
	{
		if (i % 4 == 0)
		{
			cout << endl;
		}
		cout << powerGrid.getName(result[i]->current) << "-<" << result[i]->cost << ">-" << powerGrid.getName(result[i]->dest) << "    ";
	}
}

int main()
{
	PowerGridSystem system;
	system.menu();
	string Cmd;
	while (true)
	{
		cout << endl;
		cout << "请选择操作：";
		cin >> Cmd;
		switch (Cmd[0])//string类型不能用于switch
		{
		case 'A':
			system.build();
			break;
		case 'B':
			system.addEdge();
			break;
		case 'C':
			system.buildPrim();
			break;
		case 'D':
			system.display();
			break;
		case 'E':
			cout << "成功退出系统！" << endl;
			return 0;
		default:
			cout << "操作数输入不正确，请重新输入!";
			break;
		}
	}
	return 0;
}