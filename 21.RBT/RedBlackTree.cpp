#include "RedBlackTree.h"

//�޸� ���� �Լ�.
template<typename T>
void SafeDelete(T*& resource)
{
	if (resource != nullptr)
	{
		delete resource;
		resource = nullptr;
	}
}

//Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	//�ʱ⼳��.
	if (nil == nullptr)
	{
		//Nil ��带 ����.
		nil = new Node(0, Color::Black);
	}

	//��Ʈ ��带 Nil�� ����(�⺻�� Ʈ���� �� ���·� ����).
	root = nil;
}
RedBlackTree::~RedBlackTree()
{
	//��������� ��� ��带 �����ϴ� �Լ� �ۼ� �� ȣ��.
	DestroyRecursive(root);
	//Nil ��� ����,
	SafeDelete(nil);
	//�Ʒ� �ڵ带 ĸ��ȭ�Ѱ�.
	//if (nil != nullptr)
	//{
	//	delete nil;
	//	nil = nullptr;
	//}
}

bool RedBlackTree::Find(int data, Node*& outNode)
{
	if (root == nil)
	{
		return false;
	}

	return FindRecursive(data, root, outNode);
}

//�޽���.
bool RedBlackTree::Insert(int data)
{
	//�ߺ� ��� x
	Node* currentNode = nullptr;
	if (Find(data, currentNode) == true)
	{
		std::cout << "�̹� ���� ���� �ֽ��ϴ�.\n";
		return false;
	}

	//���� ó��.
	//return InsertRecusive(currentNode,);

	//Ʈ���� ������� ��Ʈ�� �߰�
	if (root == nil)
	{
		//��Ʈ�� �ݵ�� ��
		root = CreateNode(data, Color::Black);
		return true;
	}

	//��������� ������ ��ġ �˻� �� ���� ó��.
	Node* newNode = CreateNode(data, Color::Red);
	InsertRecusive(root, newNode);

	//���� �� ��� ����.
	newNode->SetColor(Color::Red);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	//���� �� ����.
	RestructeAfterInsert(newNode);

	return true;
}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
}

Node* RedBlackTree::CreateNode(int data, Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	return newNode;
}

bool RedBlackTree::FindRecursive(int data, Node* currentNode, Node*& outNode)
{
	//���� ����.
	if (currentNode == nil)
	{
		outNode = nullptr;
		return false;
	}

	//�� Ȯ�� > �˻� ���� Ȯ��.
	if (currentNode->GetData() == data)
	{
		outNode = currentNode;
		return true;
	}

	//���� ���.
	if (currentNode->GetData() > data)
	{
		return FindRecursive(data, currentNode->GetLeftChild(), outNode);
	}

	//ū ���
	return FindRecursive(data, currentNode->GetRightChild(), outNode);

	return false;
}

void RedBlackTree::InsertRecusive(Node* currentNode, Node* newNode)
{
	//������ ���� ���� Ʈ���� ����.
	if (currentNode->GetData() > newNode->GetData())
	{
		//���� ���� �ڼ��� ������, ���� �ڼ����� �߰�.
		if (currentNode->GetLeftChild() == nil)
		{
			currentNode->SetLeftChild(newNode);

			newNode->SetParent(currentNode);

			return;
		}

		InsertRecusive(currentNode->GetLeftChild(), newNode);
	}

	else //ũ�ų� ������ ������ ���� Ʈ���� ����.
	{
		//������ ���� �ڼ��� ������, ������ �ڼ����� �߰�.
		if (currentNode->GetRightChild() == nil)
		{
			currentNode->SetRightChild(newNode);

			newNode->SetParent(currentNode);

			return;
		}

		InsertRecusive(currentNode->GetRightChild(), newNode);
	}
}

void RedBlackTree::RestructeAfterInsert(Node* newNode)
{
	//�θ� ��尡 �������� ���(Red-Red-Conflict).
	while (newNode != root && newNode->GetParent()->GetColor() == Color::Red)
	{
		//�θ�� ������ Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ��� �������� �ٽ� �˻�
		//���� ��������-> �θ��� ��ġ�� ���� �޶���.
		if (newNode->GetParent() 
			== newNode->GetParent()->GetParent()->GetLeftChild()) //�θ��� �θ��� �ڽĴ� ����
		{
			//������ ������ ����
			Node* uncle = newNode->GetParent()->GetParent()->GetRightChild();

			//Cas1. ���̵� ����.
			//�θ�� ������ ������, �Ҿƹ����� ��������.
			if (uncle->GetColor() == Color::Red)
			{
				// �θ�� ������ ���������� ����.
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				//�Ҿƹ����� ���������� ����.
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				//������ �Ҿƹ����� ����.
				newNode = newNode->GetParent()->GetParent();
				continue;
			}

			//������ �������϶�.
			//�θ� Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ����� �������� ȸ��

			//CASE2. �������
			//Case3. ���������� ���� �� ���� �ذ� �õ�.
			if (newNode == newNode->GetParent()->GetRightChild())
			{
				//ȸ��.(��ȸ��)
				newNode = newNode->GetParent(); //�θ� �޾Ƽ�.
				RotateToLeft(newNode); //��ȸ�� ��Ű��.
			}

			//Case3: �θ�� ���� ��ġ�� �������϶�.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//��ȸ��.
			RotateToRight(newNode->GetParent()->GetParent());

		}

		else
		{
			//������ ������ ����
			Node* uncle = newNode->GetParent()->GetParent()->GetLeftChild();

			//Cas1. ���̵� ����.
			//�θ�� ������ ������, �Ҿƹ����� ��������.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				//�Ҿƹ����� ���������� ����.
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				//������ �϶������� ����.
				newNode = newNode->GetParent()->GetParent();
				continue;
			}

			//������ �������϶�.
			//�θ� Black, �Ҿƹ����� Red�� ���� ��, �Ҿƹ����� �������� ȸ��

			//CASE2. �������
			//Case3. ���������� ���� �� ���� �ذ� �õ�.
			if (newNode == newNode->GetParent()->GetLeftChild())
			{
				//ȸ��.(��ȸ��)
				newNode = newNode->GetParent(); // �θ� �޾Ƽ�.
				RotateToRight(newNode);
			}

			//Case3: �θ�� ���� ��ġ�� �������϶�.
			//�θ� Black���� �Ҿƹ����� Red��.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//��ȸ��.
			RotateToLeft(newNode->GetParent()->GetParent());
		}

	}

	//���������� ��Ʈ ��� ������ ����.
	root->SetColor(Color::Black);
}


// ȸ��: �θ�� �ڼ��� ��ġ�� �ٲٴ� ���.
// ��ȸ�� -> �������� ȸ��. ������ �ڼհ� �θ��� ��ġ�� ��ȯ.
void RedBlackTree::RotateToLeft(Node* node)
{
	//������ �ڼ� ���.
	Node* right = node->GetRightChild();

	node->SetRightChild(right->GetLeftChild());


	//�θ� ����.
	if (right->GetLeftChild() != nil)
	{
		right->GetLeftChild()->SetParent(node);
	}

	//�θ� root�� ���.
	if (right->GetParent() == root)
	{
		//��Ʈ ����.
		root = right;
		right->SetParent(nullptr);
	}
	//�θ� root�� �ƴ� ���.
	else
	{
		//���θ� �������� �θ� ��� �־����� Ȯ��.
		if (node == node->GetParent()->GetLeftChild())
		{
			node->GetParent()->SetLeftChild(right);
		}
		else
		{
			node->GetParent()->SetRightChild(right);
		}
	}

	//������ �ڼ��� ���� �ڼ����� �θ� ��� ���.
	right->SetLeftChild(node);

	//������ �ڼ��� �θ� ���θ�� ����.
	right->SetParent(node->GetParent());

	//�θ��� �θ� ������ �ڼ����� ����.
	node->SetParent(right);
}


// ȸ��: �θ�� �ڼ��� ��ġ�� �ٲٴ� ���.
// ��ȸ�� -> ���������� ȸ��. ���� �ڼհ� �θ��� ��ġ�� ��ȯ.
void RedBlackTree::RotateToRight(Node* node)
{
	//���� �ڼ� ���.
	Node* left = node->GetLeftChild();

	//���� �ڼ��� ������ �ڼ� ��带 �θ��� ���� �ڼ����� ���.
	node->SetLeftChild(left->GetRightChild());

	//�θ� ����.
	if (left->GetRightChild() != nil)
	{
		left->GetRightChild()->SetParent(node);
	}

	//�θ� root�� ���.
	if (left->GetParent() == root)
	{
		//��Ʈ ����.
		root = left;
		left->SetParent(nullptr);
	}
	//�θ� root�� �ƴ� ���.
	else
	{
		//���θ� �������� �θ� ��� �־����� Ȯ��.
		if (node == node->GetParent()->GetLeftChild())
		{
			node->GetParent()->SetLeftChild(left);
		}
		else
		{
			node->GetParent()->SetRightChild(left);
		}
	}

	//���� �ڼ��� ������ �ڼ����� �θ� ��� ���.
	left->SetRightChild(node);

	//���� �ڼ��� �θ� ���θ�� ����.
	left->SetParent(node->GetParent());

	//�θ��� �θ� ���� �ڼ����� ����.
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// Ż�� ����.
	if (node == nil)
	{
		return;
	}

	// ��� ������ �����̸� blackCount ����.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// �θ� ǥ�� ���ڿ� ����.
	int parentData = 0;
	const char* position = "Root";

	// �θ� ��尡 �ִ��� Ȯ��.
	if (node->GetParent())
	{
		// �θ� ����� ������ ����.
		parentData = node->GetParent()->GetData();

		// �θ� ���κ��� ���� ����� ��ġ ����.
		if (node == node->GetParent()->GetLeftChild())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// ������ �� ����� ���� ���ڿ�.
	char blackCountString[50] = { };

	// �ڼ��� ������ ��������� ������ ��� �� ����.
	if (node->GetLeftChild() == nil && node->GetRightChild() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth ���.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << "  ";
	}

	// ��� ���� ���� �ܼ� ����.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// ���� ��� �� ���.
	std::cout
		<< node->GetData() << " "
		<< node->GetColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// ��带 ����� �ڿ��� �ܼ� �������.
	SetTextColor(TextColor::White);

	// ���� ��� ���.
	PrintRecursive(node->GetLeftChild(), depth + 1, blackCount);
	PrintRecursive(node->GetRightChild(), depth + 1, blackCount);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// ��� Ż�� ����.
	if (node == nil)
	{
		return;
	}

	// �ڽ��� �ִ� ���.
	DestroyRecursive(node->GetLeftChild());
	DestroyRecursive(node->GetRightChild());

	// ��� ����.
	SafeDelete(node);
}

void SetTextColor(TextColor color)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}


