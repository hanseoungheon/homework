#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = default;

	~BinarySearchTree()
	{
		//Todo: �����ϴ� �Լ� ���� �� �� ȣ���ؾ���.
		Destroy();
	}

	//����
	//-��Ģ-
	//1. �ߺ��� ���� ������� �ʴ´�.
	//2. ��Ʈ�������� �� ����. 2-1 ��Ʈ�� null�̸� �� ��带 ��Ʈ�� ����.
	//3. ���� �߰��ϴ� ���� �� ��庸�� ������ ���� ����Ʈ���� �� �̾.
	//4. ���� �߰��ϴ� ���� �� ��庸�� ũ�� ������ ���� Ʈ���� �� �̾.

	bool Insert(const T& newData)
	{
		//�ߺ� ���� Ȯ��.
		Node<T>* outNode = nullptr;
		if (Find(newData, outNode) == true)
		{
			//�ߺ������� ����
			std::cout << "Error: �̹� ���� ���� ��忡 �ֽ��ϴ�.";
			return false;
		}
		
		//��Ʈ�� null�̸� ��Ʈ�� ����.
		if (root == nullptr)
		{
			root = new Node<T>(newData);
			return true;
		}

		//Todo: ���� ����Լ� �ۼ� �� ȣ��.

		root = InsertRecusive(newData, root, nullptr);
		return true;
	}
	

	//�˻�
	bool Find(const T& data, Node<T>* outNode) const
	{
		Node<T>* currentNode = root;

		//��������� �˻��ϴ� �Լ�.
		return FindRecusive(data, currentNode, outNode);
	}



	

	//����
	bool Delete(const T& data)
	{
		//�˻�
		Node<T>* deleteNode = nullptr;
		if (Find(data, deleteNode) == false)
		{
			std::cout << "������ ��带 ã�� ���߽��ϴ�.";
			return false;
		}

		//��������� �����ϴ� �Լ� ȣ��.
		root = DeleteRecursive(data,root);
		return true;
	}

	//���� ��ȸ(���ĵ� ������� ��� ������.)

	//�ּڰ� �˻�
	Node<T>* FindMinValue(Node<T>* currentNode)
	{
		//���� ���� ���� �ִ� ��� �˻�.
		while (currentNode->GetLeftChild() != nullptr)
		{
			currentNode = currentNode->GetLeftChild();
		}

		return currentNode;
	}

	//�ִ� �˻�
	Node<T>* FindMaxValue(Node<T>* currentNode)
	{
		//���� ������ ���� �ִ� ��� �˻�.

		while (currentNode->GetRightChild() != nullptr)
		{
			currentNode = currentNode->GetRightChild();
		}

		return currentNode;
	}

private:
	bool FindRecusive(const T& data, Node<T>* currentNode,Node<T>* outNode) const
	{
		//���� ����.(�˻� ����)
		if (currentNode == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		//�˻� �����ߴ��� Ȯ��.
		if (currentNode->GetData() == data)
		{
			outNode = currentNode;
			return true;
		}

		//�˻��� ��尡 ã������ ������ ũ��?
		if (currentNode->GetData() > data)
		{
			return FindRecusive(data, currentNode->GetLeftChild(), outNode);
		}


		//�˻��� ��尡 ã������ ������ ���� ���?
		if (currentNode->GetData() < data)
		{
			return FindRecusive(data, currentNode->GetRightChild(), outNode);
		}
		
		//����ó��.
		return false;
	}

	Node<T>* InsertRecusive(const T& data,Node<T>* currentNode,Node<T>* parent)
	{
		//���� ����.
		if (currentNode == nullptr)
		{
			//currentNode�� NULL�̸� ������ ��ġ�� ã��.

			return new Node<T>(data, parent);
		}	

		//���� �˻����� ����� �����Ͱ� �������� �����ͺ��� ū ��� / �����Ͱ� ���� ���
		if (currentNode->GetData() > data)
		{
			currentNode->SetLeftChild(InsertRecusive(data, 
				currentNode->GetLeftChild(),
				currentNode));
		}
		else //ū ���
		{
			currentNode->SetRightChild(InsertRecusive(data, 
				currentNode->GetRightChild(),
				currentNode));
		}

		return currentNode;
	}

	Node<T>* DeleteRecursive(const T& data, Node<T>* currentNode)
	{
		//��������
		if (currentNode != nullptr)
		{
			return nullptr;
		}

		//����� �� 1. ���� ���
		if (currentNode->GetData() > data)
		{
			currentNode->SetLeftChild(DeleteRecursive(data,currentNode->GetLeftChild()));
		}

		else if (currentNode->GetData() < data)
		{
			currentNode->SetRightChild(DeleteRecursive(data, currentNode->GetRightChild()));
		}

		else //������ ��� ã��.
		{
			//����� �� ( ����ó���Ҷ� �����˻�Ʈ���� ���ǿ� �����ؾ���)

			//����� �� 1. �ڽ��� �Ѵ� ���� ���.
			if (currentNode->GetLeftChild() == nullptr
				&& currentNode->GetRightChild() == nullptr)
			{
				delete currentNode;
				return nullptr;
			}

			//����� �� 2. �ڽ��� �Ѵ� �ִ� ���.
			if (currentNode->GetLeftChild() && currentNode->GetRightChild())
			{
				//����� �� 1.
				//���� �������� ���� ū ������ ��ü, ������ �������� ���� ���� ������ ��ü.

				//������ ��ġ�� ��尪�� ��ü������ �Ҵ�.
				currentNode->SetData(FindMinValue(currentNode->GetRightChild())->GetData());

				//��ü���ϴ� ��带 ����.
				currentNode->SetRightChild(
					DeleteRecursive(
					currentNode->GetData(),
					currentNode->GetRightChild()
					)
				);
			}

			//����� �� 3. �ڽ��� �ϳ��� �ִ� ���.
			else
			{
				//����� �� 1.
				if (currentNode->GetRightChild() == nullptr) //���ʸ� ����.
				{
					//���� �ڼ��� ��ȯ�ϱ� ���� �ӽ� ����.
					Node<T>* leftChild = currentNode->GetLeftChild();
					delete currentNode;

					return leftChild;
				}
				else if (currentNode->GetLeftChild() == nullptr)// �����ʸ� ����.
				{
					Node<T>* rightChild = currentNode->GetRightChild();
					delete currentNode;

					return rightChild;
				}
			}
		}

		return currentNode;
	}

	void Destroy()
	{
		//��Ʈ�� ��������� ����,
		if (root == nullptr)
		{
			return;
		}

		//�ڼ� ��� �����ϰ� ��Ʈ �����ϵ��� ó��.
		DestroyRecusive(root);
	}

	//�ı� ����Լ�.

	void DestroyRecusive(Node<T>* currentNode)
	{
		if (currentNode == nullptr)
		{
			return;
		}

		Node<T>* leftChild = currentNode->GetLeftChild();
		Node<T>* rightChild = currentNode->GetRightChild();

		if (!leftChild && !rightChild)// �ڼ��� ������
		{
			delete currentNode;
			currentNode = nullptr;

			return;
		}

		DestroyRecusive(leftChild);
		DestroyRecusive(rightChild);

		delete currentNode;
		currentNode = nullptr;
	}

private:
	//��Ʈ ���
	Node<T>* root = nullptr;
};