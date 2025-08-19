#pragma once

#include "List.h"

template<typename T>
class Node
{
public:
	Node()
		:data(), parent(nullptr)
	{

	}

	Node(const T& data)
		:data(data), parent(nullptr)
	{

	}

	//���� ������ ����
	Node(const Node& other) = delete;

	~Node()
	{
		parent = nullptr;
	}

	//���� �����ؼ� �ڼ��� �߰��ϴ� �Լ�.
	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}

	void AddChild(Node<T>* child)
	{
		child->parent = this;

		children.PushBack(child);
	}

	//Getter & Setter.
	T GetData() const
	{
		return data;
	}

	const List<Node<T>*>& GetChildern() const
	{
		return children;
	}

	List<Node<T>*>& GetChildern() 
	{
		return children;
	}

	Node<T>* GetParent() const
	{
		return parent;
	}

	void SetParent(const Node<T>* const parent)
	{
		this->parent = parent;
	}

private:
	//��忡 ������ ������
	T data;

	//�θ� ���� ����
	Node<T>* parent = nullptr;

	//�ڼ� ��� ����Ʈ(���� �迭)
	List<Node<T>*> children;
};