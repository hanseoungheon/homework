#pragma once

#include "Node.h"
#include <iostream>

template<typename T>
class BinaryTree
{
public:
	BinaryTree()
		: root(nullptr)
	{

	}

	BinaryTree(const T& data)
	{
		root = new Node<T>(data);
	}

	~BinaryTree()
	{
		if (root != nullptr)
		{
			root->Destroy();
		}
	}

	//�ڼ� �߰� �Լ�.
	void AddLeftChild(const T& parentData, const T& childData)
	{
		//1.�˻�(�θ�ã�� ����)
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		if (result == true)
		{
			parent->AddLeftChild(childData);
			return;
		}

		//�˻� ����
		std::cout << "�θ� ��带 ã�� ���߽��ϴ�.\n";
	}

	void AddRightChild(const T& parentData, const T& childData)
	{
		//1.�˻�(�θ�ã�� ����)
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		if (result == true)
		{
			parent->AddRightChild(childData);
			return;
		}

		//�˻� ����
		std::cout << "�θ� ��带 ã�� ���߽��ϴ�.\n";
	}

	//������ ã�� �Լ�
	bool Find(const T& data, Node<T>*& outNode)
	{
		//��� �˻� �Լ� ȣ��.
		return FindRecursive(data, root, outNode);
	}

	//���� ��ȸ �Լ�.
	void PreorderTraverse()
	{
		PreorderTraverseRecursive(root);
	}

	//����
	bool DeleteNode(const T& data)
	{
		//1. �˻�.
		Node<T>* deleteNode = nullptr;
		bool result = Find(data, deleteNode);

		//ã������ ����.
		if (result == true)
		{
			deleteNode->Destroy();
			
			return true;
		}

		//��ã������ �޽��� ����ϱ�.
		std::cout << "��� �˻��� �����Ͽ� ������ ���߽��ϴ�.\n";
		return false;
	}

	//Getter
	//����.������ �ڼ� ��ȯ �Լ�.
	Node<T>* GetLeft() const
	{
		return root->GetLeftChild();
	}

	Node<T>* GetRight() const
	{
		return root->GetRightChild();
	}


private:
	//��� �˻� �Լ�.
	bool FindRecursive(const T& data, Node<T>* node,Node<T>*& outNode)
	{
		//���� ����.
		if (node == nullptr)
		{
			//��¿� null����
			outNode = nullptr;
			return false;
		}

		//�˻� Ȯ�� �ܰ�
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		//���� �ڼ����� �˻� ����.
		bool result = FindRecursive(data, node->GetLeftChild(), outNode);

		if (result == true)
		{
			return true;
		}

		//������ �ڼ����� �˻� ����.
		result = FindRecursive(data, node->GetRightChild(), outNode);

		if (result == true)
		{
			return true;
		}

		//�˻� ����
		outNode = nullptr;

		return false;
	}

	//��� ���� ��ȸ �Լ�
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		//��������
		if (node == nullptr)
		{
			return;
		}

		//���� ���
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		//�θ� �湮.
		std::cout << node->GetData() << "\n";

		PreorderTraverseRecursive(node->GetLeftChild(), depth + 1);

		PreorderTraverseRecursive(node->GetRightChild(), depth + 1);
	}

private:
	//��Ʈ ���(������ ���)
	Node<T>* root = nullptr;
};