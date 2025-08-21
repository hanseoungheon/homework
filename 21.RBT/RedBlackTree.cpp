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

Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	//�ʱ⼳��.
	if (nil == nullptr)
	{
		//Nil ��带 ����.
		nil = new Node(0, Color::Black);
	}

	root = nil;
}
RedBlackTree::~RedBlackTree()
{
	//Todo: ��������� ��� ��带 �����ϴ� �Լ� �ۼ� �� ȣ��.
	//Nil ��� ����,
	SafeDelete(nil);
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
			if (newNode == newNode->GetParent()->GetRightChild());
			{
				//ȸ��.(��ȸ��)

			}

			//Case3: �θ�� ���� ��ġ�� �������϶�.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

		}

		else
		{
			//������ ������ ����
			Node* uncle = newNode->GetParent()->GetParent()->GetRightChild();

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
			if (newNode == newNode->GetParent()->GetRightChild());
			{
				//ȸ��.(��ȸ��)

			}

			//Case3: �θ�� ���� ��ġ�� �������϶�.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);


			//��ȸ��.
		}

	}


}

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

void RedBlackTree::RotateToRight(Node* node)
{
	//���� �ڼ� ���.
	Node* left = node->GetLeftChild();

	node->SetLeftChild(left->GetRightChild());
}

