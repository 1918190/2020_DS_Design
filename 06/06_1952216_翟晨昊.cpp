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

class Genealogy;

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

template <typename ElementType>
class FamilyTree;

template<typename ElementType>
class FamilyTreeNode {
public:
	friend class Genealogy;
	friend class FamilyTree<ElementType>;
	FamilyTreeNode() = default;
	FamilyTreeNode(const ElementType& inputData) :data(inputData) {}
	~FamilyTreeNode() = default;
private:
	ElementType data;
	FamilyTreeNode<ElementType>* firstChild = nullptr;
	FamilyTreeNode<ElementType>* nextSibling = nullptr;
	FamilyTreeNode<ElementType>* parent = nullptr;
};

template<typename ElementType>
class FamilyTree {
public:
	friend class Genealogy;
	FamilyTree() :root(nullptr) {}
	~FamilyTree();
	FamilyTreeNode<ElementType>* getLastChild(FamilyTreeNode<ElementType>* ptr);
	void makeEmpty(FamilyTreeNode<ElementType>* ptr);
	void clear(Vector<ElementType>& vec, FamilyTreeNode<ElementType>* ptr);
private:
	FamilyTreeNode<ElementType>* root;
};

template<typename ElementType>
FamilyTree<ElementType>::~FamilyTree()
{
	makeEmpty(root);
}

template<typename ElementType>
FamilyTreeNode<ElementType>* FamilyTree<ElementType>::getLastChild(FamilyTreeNode<ElementType>* ptr)
{
	FamilyTreeNode<ElementType>* lastSon = ptr->firstChild;
	if (lastSon == nullptr)
	{
		return nullptr;
	}
	else
	{
		while (lastSon->nextSibling != nullptr)
		{
			lastSon = lastSon->nextSibling;
		}
		return lastSon;
	}
}

template<typename ElementType>
void FamilyTree<ElementType>::makeEmpty(FamilyTreeNode<ElementType>* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	makeEmpty(ptr->firstChild);
	makeEmpty(ptr->nextSibling);
	delete ptr;
	ptr = nullptr;
}

template<typename ElementType>
void FamilyTree<ElementType>::clear(Vector<ElementType>& vec, FamilyTreeNode<ElementType>* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	clear(vec, ptr->firstChild);
	clear(vec, ptr->nextSibling);
	vec.pushBack(ptr->data);
	delete ptr;
	ptr = nullptr;
}

class Genealogy
{
public:
	void menu();
	void init();
	void build();
	void add();
	void destroy();
	void change();
	void show(FamilyTreeNode<string>* parent);
private:
	bool checkChild(Vector<string>& child);
	bool checkChild(string& child);
	void addNewChild(FamilyTreeNode<string>* parent, string& child);
	void addNewChild(FamilyTreeNode<string>* parent, Vector<string>& child);
	FamilyTree<string> family;
	AVLTree<string, FamilyTreeNode<string>*> familyAVLTree;
};

void Genealogy::menu()
{
	cout << "**\t\t家谱管理系统\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA---完善家谱\t\t\t**" << endl;
	cout << "**\t\tB---添加家庭成员\t\t**" << endl;
	cout << "**\t\tC---解散局部家庭\t\t**" << endl;
	cout << "**\t\tD---更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void Genealogy::init()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string ancestor;
	cin >> ancestor;
	family.root = new FamilyTreeNode<string>(ancestor);
	familyAVLTree.insert(ancestor, family.root);
	cout << "此家谱的祖先是：" << ancestor << endl;
}

void Genealogy::build()
{
	int childNum = 0;
	string parentName;
	Vector<string> child;
	AVLTreeNode<string, FamilyTreeNode<string>*>* parent = nullptr;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> parentName;
	parent = familyAVLTree.find(parentName);
	while (parent == nullptr || familyAVLTree.getData(parent)->firstChild != nullptr)
	{
		if (parent == nullptr)
		{
			cout << "此人不在家谱中！" << endl;
		}
		else
		{
			cout << "此人已经建立家庭！" << endl;
		}
		cout << "请重新输入：";
		cin >> parentName;
		parent = familyAVLTree.find(parentName);
	}
	cout << "请输入" << parentName << "的儿女的人数：";
	cin >> childNum;
	while (cin.fail() || childNum <= 0)
	{
		cout << "请输入一个正整数！" << endl;
		cout << "请重新输入：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> childNum;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "请依次输入" << parentName << "的儿女的姓名：";
	child.reSize(childNum);
	for (int i = 0; i < childNum; i++)
	{
		cin >> child[i];
	}
	while (!checkChild(child))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请重新依次输入" << parentName << "的儿女的姓名：";
		for (int i = 0; i < childNum; i++)
		{
			cin >> child[i];
		}
	}
	FamilyTreeNode<string>* pParent = familyAVLTree.getData(parent);
	addNewChild(pParent, child);
	show(pParent);
}

void Genealogy::add()
{
	string parentName;
	string addChild;
	AVLTreeNode<string, FamilyTreeNode<string>*>* parent = nullptr;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> parentName;
	parent = familyAVLTree.find(parentName);
	while (parent == nullptr)
	{
		cout << "此人不在家谱中！" << endl;
		cout << "请重新输入：";
		cin >> parentName;
		parent = familyAVLTree.find(parentName);
	}
	cout << "请输入" << parentName << "新添加儿子（或女儿）的姓名：";
	cin >> addChild;
	while (!checkChild(addChild))
	{
		cout << "请重新输入：";
		cin >> addChild;
	}
	FamilyTreeNode<string>* pParent = familyAVLTree.getData(parent);
	addNewChild(pParent, addChild);
	show(pParent);
}

void Genealogy::destroy()
{
	string ancestorName;
	Vector<string> deleteNode;
	AVLTreeNode<string, FamilyTreeNode<string>*>* ancestor = nullptr;
	if (familyAVLTree.size == 1)
	{
		cout << "家谱中只有第一代祖先！无法解散家庭" << endl;
		return;
	}
	cout << "请输入要解散家庭的人的姓名：";
	cin >> ancestorName;
	ancestor = familyAVLTree.find(ancestorName);
	while (ancestor == nullptr || familyAVLTree.getData(ancestor)->data == family.root->data)
	{
		if (ancestor == nullptr)
		{
			cout << "此人不在家谱中！" << endl;
		}
		else
		{
			cout << "不能解散第一代祖先的家庭！" << endl;
		}
		cout << "请重新输入：";
		cin >> ancestorName;
		ancestor = familyAVLTree.find(ancestorName);
	}
	FamilyTreeNode<string>* pAncestor = familyAVLTree.getData(ancestor);
	cout << "要解散家庭的人是：" << pAncestor->data << endl;
	show(pAncestor);
	if (pAncestor->parent != nullptr)
	{
		if (pAncestor->parent->firstChild == pAncestor)
		{
			pAncestor->parent->firstChild = pAncestor->nextSibling;
		}
		else
		{
			FamilyTreeNode<string>* current = pAncestor->parent->firstChild;
			while (current->nextSibling != pAncestor)
			{
				current = current->nextSibling;
			}
			current->nextSibling = pAncestor->nextSibling;
		}
	}
	deleteNode.pushBack(pAncestor->data);
	family.clear(deleteNode, pAncestor->firstChild);
	delete pAncestor;
	pAncestor = nullptr;
	for (int i = 0; i < deleteNode.getSize(); i++)
	{
		familyAVLTree.remove(deleteNode[i]);
	}
}

void Genealogy::change()
{
	string oldName, newName;
	AVLTreeNode<string, FamilyTreeNode<string>*>* oldPeople = nullptr;
	AVLTreeNode<string, FamilyTreeNode<string>*>* newPeople = nullptr;
	cout << "请输入要更改姓名的人的目前姓名：";
	cin >> oldName;
	oldPeople = familyAVLTree.find(oldName);
	while (oldPeople == nullptr)
	{
		cout << "此人不在家谱中！" << endl;
		cout << "请重新输入：";
		cin >> oldName;
		oldPeople = familyAVLTree.find(oldName);
	}
	FamilyTreeNode<string>* pPeople = familyAVLTree.getData(oldPeople);
	cout << "请输入更改后的姓名：";
	cin >> newName;
	newPeople = familyAVLTree.find(newName);
	while (newPeople != nullptr)
	{
		cout << "此姓名已存在于家谱中！" << endl;
		cout << "请重新输入：";
		cin >> newName;
		newPeople = familyAVLTree.find(newName);
	}
	familyAVLTree.change(oldName, newName);
	pPeople->data = newName;
	cout << oldName << "已更名为" << newName << endl;
}

void Genealogy::show(FamilyTreeNode<string>* parent)
{
	if (parent->firstChild == nullptr)
	{
		cout << parent->data << "该人没有子孙！" << endl;
		return;
	}
	else
	{
		cout << parent->data << "的第一代子孙是：";
		FamilyTreeNode<string>* first = parent->firstChild;
		cout << first->data << ' ';
		while (first->nextSibling != nullptr)
		{
			first = first->nextSibling;
			cout << first->data << ' ';
		}
		cout << endl;
	}
}

bool Genealogy::checkChild(Vector<string>& child)
{
	for (int i = 0; i < child.getSize() - 1; i++)
	{
		for (int j = i + 1; j < child.getSize(); j++)
		{
			if (child[i] == child[j])
			{
				cout << "输入的儿女中存在姓名相同的人！" << endl;
				return false;
			}
		}
	}
	for (int i = 0; i < child.getSize(); i++)
	{
		if (familyAVLTree.find(child[i]) != nullptr)
		{
			cout << "存在儿女姓名与家谱中已存在人姓名相同！" << endl;
			return false;
		}
	}
	return true;
}

bool Genealogy::checkChild(string& child)
{
	if (familyAVLTree.find(child) != nullptr)
	{
		cout << "新的儿女姓名已在家谱中已经存在！" << endl;
		return false;
	}
	return true;
}

void Genealogy::addNewChild(FamilyTreeNode<string>* parent, string& child)
{
	if (parent == nullptr)
	{
		return;
	}
	FamilyTreeNode<string>* pChild = new FamilyTreeNode<string>(child);
	familyAVLTree.insert(child, pChild);
	FamilyTreeNode<string>* lastChild = family.getLastChild(parent);
	if (lastChild == nullptr)
	{
		parent->firstChild = pChild;
	}
	else
	{
		lastChild->nextSibling = pChild;
	}
	pChild->parent = parent;
}

void Genealogy::addNewChild(FamilyTreeNode<string>* parent, Vector<string>& child)
{
	if (parent == nullptr || child.isEmpty())
	{
		return;
	}
	FamilyTreeNode<string>* pChild = new FamilyTreeNode<string>(child[0]);
	familyAVLTree.insert(child[0], pChild);
	parent->firstChild = pChild;
	pChild->parent = parent;
	for (int i = 1; i < child.getSize(); i++)
	{
		pChild->nextSibling = new FamilyTreeNode<string>(child[i]);
		pChild->nextSibling->parent = parent;
		pChild = pChild->nextSibling;
		familyAVLTree.insert(child[i], pChild);
	}
}

int main(void)
{
	Genealogy MyGenealogy;
	MyGenealogy.menu();
	MyGenealogy.init();
	string operation;
	while (true)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "请输入要执行的操作：";
		cin >> operation;
		switch (operation[0])//string类型不能用于switch
		{
		case 'A':
			MyGenealogy.build();
			break;
		case 'B':
			MyGenealogy.add();
			break;
		case 'C':
			MyGenealogy.destroy();
			break;
		case 'D':
			MyGenealogy.change();
			break;
		case 'E':
			cout << "成功退出系统！" << endl;
			return 0;
		default:
			cout << "操作数输入不正确，请重新输入!" << endl;
		}
	}
	return 0;
}