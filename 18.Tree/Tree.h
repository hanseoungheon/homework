#pragma once
#include <iostream>	
#include "List.h"
#include "Node.h"

template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))
	{

	}

	~Tree()
	{
		List<Node<T>*>& childern = root->GetChildern();
		
		while (childern.Size() > 0)
		{
			root->ReMoveChild(childern[0]);
		}

		delete root;
		root = nullptr;
	}

	bool ReMove(const T& data)
	{
		//Todo: ������ ��带 �˻��ϰ�, �����ϴ� �Լ� �ۼ� �� ȣ��.
		Node<T>* outNode = nullptr;
		bool result = Find(data, outNode);
		
		if (result == false) //�˻�����
		{
			std::cout << "������ ��带 ã�� ���߽��ϴ�.\n";

			return false;
		}

		//������� ���� �˻� ����.
		//����� ��1: ������ ��尡 ��Ʈ ����� ���
		if (outNode == root)
		{
			std::cout << "��Ʈ�� ������ �� �����ϴ�.\n";
			return false;
		}

		//����� ��2:
		Node<T>* parent = outNode->GetParent();
		parent->ReMoveChild(outNode);

		return true;
	}

	void AddChild(const T& parentData, const T& childData)
	{
		//�˻�.
		Node<T>* outParent = nullptr;
		bool result = Find(parentData, outParent);

		//�θ��� �˻��� ���������� �θ����� �ڼ����� ��� �߰�.
		if (result)
		{
			outParent->AddChild(childData);
			return;
		}
		//�θ��� �˻� ����
		std::cout << "�ش� ���� ���� �θ� ��� �˻��� �����߽��ϴ�.\n";
	}

	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		//��� �Լ� ���� ����
		if (node == nullptr)
		{
			outNode = nullptr; //��ã����.
			return false;
		}

		//�˻� ����
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}


		//�ڼ��� ��������� �˻�.
		List<Node<T>*>& children = node->GetChildern();
		int count = children.Size();

		for (int ix = 0; ix < count; ++ix)
		{
			//�ڼ� �˻� ����
			Node<T>* child = children[ix];
			bool result = FindRecursive(data, child, outNode);

			if (result == true)
			{
				return true;
			}
		}

		//�˻� ����
		outNode = nullptr;
		return false;
	}

	//���� ��ȸ �Լ�(�θ� ���� �湮 -> �ڼ� �湮)
	void PreOrderTraverse()
	{
		PreOrderTraverseRecursive(root);
	}

	//���� ��ȸ ��� �Լ�.
	//node: �湮�� ���� ���.
	//depth: ����� �� �θ�-�ڼ� ������ ���� �鿩������ ��.
	void PreOrderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		if (node == nullptr)
		{
			return;
		}

		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		std::cout << node->GetData() << "\n";

		List<Node<T>*>& children = node->GetChildern();

		if (children.Size() == 0)
		{
			return;
		}

		for (int ix = 0; ix < children.Size(); ++ix)
		{
			Node<T>* child = children[ix];
			PreOrderTraverseRecursive(child, depth + 1);
		}
	}

private:

	//��Ʈ ���.
	Node<T>* root = nullptr;
};