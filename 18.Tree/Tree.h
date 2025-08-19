#pragma once
	
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
		//Todo: �ڼ� ��� �����ϴ� �Լ� ���� �� ȣ���ؾ� ��.
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

private:

	//��Ʈ ���.
	Node<T>* root = nullptr;
};