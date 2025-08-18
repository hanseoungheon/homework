#pragma once

#include <iostream>
#include "Node.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
		:root(nullptr)
	{

	}

	~BinarySearchTree()
	{
		//Destroy();
	}

	//����
	//��Ģ
	//0. �ߺ��� �� ��� x
	// 1. ���� - ��Ʈ�������� �� ����.
	// 1-1 ��Ʈ�� null�̸� �� ��带 ��Ʈ�� �����Ѵ�.
	// 2. ���� �߰��ϴ� ���� ���ϴ� ��庸�� ������ ���� ���� Ʈ���� �񱳸� �̾��.
	// 3. ���� �߰��ϴ� ���� ���ϴ� ��庸�� ũ�� ������ ���� Ʈ���� �񱳸� �̾��.

	bool InsertNode(const T& newData)
	{
		//�˻�(�ߺ��� ���� �ִ��� Ȯ��, �� �̹� �ش� ���� ���ȿ� �ִ��� Ȯ��)
		if (SearchNode(newData) == true)
		{
			std::cout << "Error:: �̹� �ߺ��� ���� �����Ƿ�  �߰��� �� ����";
			return false;
		}

		if (root == nullptr) //��Ʈ�� ��������� ��Ʈ�� ����
		{
			root = new Node<T>(newData);
			return true;
		}

		root 
	}

	void DeleteNode(const T& deleteData)
	{
		//��������� �����ϴ� �Լ��� ȣ��
		//���� ������ ������ root
		//���� ���������� ���������� ���鼭 ��������� ����
		
		root = DeleteNodeRecursive(root, deleteData);
	}

	Node<T>* SerachMinValue(Node<T>* Node)
	{
		while (data->left != nullptr) //�������� ��� �̵��ϸ鼭 nullptr�϶����� Ž��
		{
			node = node->left;
		}
		
		return node; //���� ���ʿ� �ִ� ���� �� ��ȯ.
	}

	bool SearchNode(const T& data)
	{
		SearchNodeRecursive(root, data);
	}

	bool SearchNodeRecursive(Node<T>* node, const T& data)
	{
		if (node == nullptr) //�˻�����
		{
			return false;
		}

		if (node->data == data) //����� data�� ���ڷ� ���� data�� ������ ��
		{
			return true;
		}
		else if (node->data > data) //����� �����Ͱ� ���ڷ� ���� �����ͺ��� ũ�� ��������
		{
			return SearchNodeRecursive(node->left, data);
		}
		else //�ݴ� ���� node->data < data
		{
			return SearchNodeRecursive(node->right, data);
		}
	}

	void PreorderTraverse(int depth = 0)
	{
		std::cout << "========== ���� ��ȸ ���� ==========\n";

		PreorderTraverseRecursive(root, depth);

		std::cout << "========== ���� ��ȸ ���� ==========\n";
	}


	void InorderTraverse(int depth = 0)
	{
		std::cout << "========== ���� ��ȸ ���� ==========\n";

		// ����� ���� ���� ��ȸ ������� ��� �Լ��� ȣ��.
		// Ž�� ������ ��Ʈ ��Ʈ���� ����.
		InorderTraverseRecursive(root, depth);

		std::cout << "========== ���� ��ȸ ���� ==========\n";
	}

	// ��� (���� ��ȸ).
	void PostorderTraverse(int depth = 0)
	{
		std::cout << "========== ���� ��ȸ ���� ==========\n";

		// ����� ���� ���� ��ȸ ������� ��� �Լ��� ȣ��.
		// Ž�� ������ ��Ʈ ��Ʈ���� ����.
		PostorderTraverseRecursive(root, depth);

		std::cout << "========== ���� ��ȸ ���� ==========\n";
	}

private:
	// ��������� ������ ó���ϴ� �Լ�.
	// node: ���� ���ϴ� ���.
	// parent: node�� �θ� ���.
	// newData: �����Ϸ��� �� ������.
	Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& newData)
	{
		if (node == nullptr) //��尡 nullptr�̸� ���� ������ ��带 ��ȯ
		{
			return new Node<T>(newData, parent);
		}

		// �߰��Ϸ��� ���� �� ��庸�� ������, ���� ���� Ʈ���� Ž��.
		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}

		// �߰��Ϸ��� ���� �� ��庸�� ũ��, ������ ���� Ʈ���� Ž��.
		else
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	//���� ����Լ�
	Node<T>* DeleteNodeRecursive(Node<T>* node, const T& deleteData)
	{
		if (node == nullptr) 
		{
			std::cout << "������ �����͸� ã�� ����";
			return nullptr;
		}

		if (node->data > deleteData) //�����Ϸ��� �����Ͱ� �� �����ͺ��� ������ �������� �̵�
		{
			node->left = DeleteNodeRecursive(node->left, deleteData);
		}
		// �����Ϸ��� �����Ͱ� �� �����ͺ��� ũ�� ������ ���� Ʈ���� �̵�.
		else if (node->data < deleteData)
		{
			node->right = DeleteNodeRecursive(node->right, deleteData);
		}


		// ã����, ���� ó��.
		else
		{
			// ���1 - �ڽ��� ���� ���. (�� ��� null�� ���)
			if (node->left == nullptr && node->right == nullptr)
			{
				// ��� ���� �� �Լ� ����.
				delete node;
				return nullptr;
			}

			// ���3 - �ڽ��� �� �� �ִ� ���. (�� ��� null�� �ƴ� ���).
			if (node->left != nullptr && node->right != nullptr)
			{
				// �����Ǵ� ����� ������ ���� Ʈ������ ���� ���� ���� �˻��ؼ� �����ϴ�
				// ����� ���� ������Ʈ.
				node->data = SearchMinValue(node->right)->data;

				// ������ ���� ������ ���� Ʈ������ ���� ���� ���� ���� ��带 ����.
				node->right = DeleteNodeRecursive(node->right, node->data);
			}
			else
			{
				// ���2 - �ڽ��� �ϳ��� �ִ� ��� (�� �� �ϳ��� null�� ���).
				if (node->left == nullptr)
				{
					// ������ �ڼ��� ��ȯ�ϱ� ���� �ӽ÷� ������ ����.
					Node<T>* right = node->right;

					// ��� ����.
					delete node;

					// ������ �ڼ� ��ȯ.
					return right;
				}

				else if (node->right == nullptr)
				{
					// ���� �ڼ��� ��ȯ�ϱ� ���� �ӽ÷� ������ ����.
					Node<T>* left = node->left;

					// ��� ����.
					delete node;

					// ���� �ڼ� ��ȯ.
					return left;
				}
			}
		}

	}

	// ���� ��ȸ ��� �Լ�.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		if (node == nullptr) //���� ����
		{
			//Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << " ";
			}

			std::cout << "null\n";

			return;
		}


		// Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		std::cout << node->data << "\n";

		// ���� ���� Ʈ���� ���� ��ȸ.
		PreorderTraverseRecursive(node->left, depth + 1);

		// ������ ���� Ʈ���� ���� ��ȸ.
		PreorderTraverseRecursive(node->right, depth + 1);
	}

	void InorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// ���� ����.
		if (node == nullptr)
		{
			// Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// ���� ���� Ʈ���� ���� ��ȸ.
		InorderTraverseRecursive(node->left, depth + 1);

		// Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// �θ� ��� ó��.
		std::cout << node->data << "\n";

		// ������ ���� Ʈ���� ���� ��ȸ.
		InorderTraverseRecursive(node->right, depth + 1);
	}

	// ���� ��ȸ ��� �Լ�.
	void PostorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// ���� ����.
		if (node == nullptr)
		{
			// Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// ���� ���� Ʈ���� ���� ��ȸ.
		PostorderTraverseRecursive(node->left, depth + 1);

		// ������ ���� Ʈ���� ���� ��ȸ.
		PostorderTraverseRecursive(node->right, depth + 1);

		// Ʈ�� ��带 ����� �� ������ �����ֱ� ���� �� ���� ���.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// �θ� ��� ó��.
		std::cout << node->data << "\n";
	}

private:
	// ��� ��带 ������ �� ����ϴ� �Լ�.
	void Destroy()
	{
		// ��Ʈ ��尡 null�̸� ����.
		if (root == nullptr)
		{
			return;
		}

		// ���� �ڼ� > ������ �ڼ� > ��Ʈ ������ ����.
		DestroyRecursive(root);
	}

	void DestroyRecursive(Node<T>* node)
	{
		// ����Լ� ���� ����.
		if (node == nullptr)
		{
			return;
		}

		// ���� �ڼ� / ������ �ڼ� Ȯ��.
		Node<T>* left = node->left;
		Node<T>* right = node->right;

		// �ڼ��� ���� ���.
		if (left == nullptr && right == nullptr)
		{
			// ��� ���� �� �Լ� ����.
			delete node;
			return;
		}

		DestroyRecursive(left);
		DestroyRecursive(right);

		delete node;
	}


private:
	Node<T>* root;

};