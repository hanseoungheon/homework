#pragma once

//���� Ʈ���� ���� ��� Ŭ����
template<typename T>
class Node
{
	template<typename T>
	friend class BinaryTree;

	//public �Լ� = �������̽�
public:

	// ������
	Node()
		: data(), parent(nullptr), left(nullptr), right(nullptr)
	{

	}

	Node(const T& data)
		: data(data), parent(nullptr), left(nullptr), right(nullptr)
	{

	}

	//�⺻ �Ҹ��ڸ� ��������� ����!
	~Node() = default;

	//-----------------------------------------------------------------------------//
	//�ڼ� �߰� �Լ� (AddChild<Left,Right>)
	void AddLeftChild(const T& data)
	{
		//��带 �����ؼ� �ٸ� �Լ� ȣ��.
		AddLeftChild(new Node<T>(data));
	}
	void AddLeftChild(Node<T>* child) //�����ε�
	{
		child->SetParent(this);

		left = child;
	}

	void AddRightChild(const T& data)
	{
		//��带 �����ؼ� �ٸ� �Լ� ȣ��.
		AddRightChild(new Node<T>(data));
	}
	void AddRightChild(Node<T>* child)
	{
		child->SetParent(this);

		right = child;
	}

	//�����Լ�
	void Destroy()
	{
		//�θ� ��� ����.
		if (parent != nullptr)
		{
			//�� ��尡 �θ� ���� �������� Ȯ��.
			if (parent->GetLeftChild() == this)
			{
				parent->left = nullptr;
			}

			//�� ��尡 �θ� ���� ���������� Ȯ��.
			else if (parent->GetRightChild() == this)
			{
				parent->right = nullptr;
			}
		}

		//�ڼձ��� �湮�ؼ� ��� �����ع�����.
		DestroyRecursive(this);
	}

	//Getter & Setter-------------------------------------------------------------//
	T GetData() const
	{
		return data;
	}

	Node<T>* GetParent() const
	{
		return parent;
	}

	void SetParent(Node<T>* newParent)
	{
		parent = newParent;
	}

	Node<T>* GetLeftChild() const
	{
		return left;
	}

	Node<T>* GetRightChild() const
	{
		return right;
	}

private:
	void DestroyRecursive(Node<T>* node)
	{
		//���� �ִ��� ���ǹ����� Ȯ���� ��� �������ٰ� ���������� �������� ����
		//�� �� �ö���鼭 ������ Ȯ���� �������� �ٽ� ���� Ȯ��
		//�̷������� �Ʒ��� ���� ��������� ����.
		
		//Ż�� ����
		if (node == nullptr)
		{
			return;
		}

		//�ڼ� ��� ���� Ȯ��
		Node<T>* leftChild = node->GetLeftChild();
		Node<T>* rightChild = node->GetRightChild();

		//����� �� 1. �ڼ��� ���� ���
		if (leftChild == nullptr && rightChild == nullptr)
		{
			delete node;
			node = nullptr;
			return;
		}

		//����� �� 2: �ڼ��� �ִ� ���=> ��������� �ڼ� ��� ����.
		DestroyRecursive(leftChild);
		DestroyRecursive(rightChild);

		delete node;
		node = nullptr;
	}

private:
	//������
	T data;

	//�θ���
	Node<T>* parent = nullptr;
	//����, ������ �ڼ�
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};