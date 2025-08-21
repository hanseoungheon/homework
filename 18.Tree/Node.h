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

	//���� 
	//�ڼ� ���� �Լ�.
	void ReMoveChild(Node<T>* child)
	{
		ReMoveChildRecursive(child);
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

	void SetParent(Node<T>* const parent)
	{
		this->parent = parent;
	}

private:
	//�ڼ� ��带 �����Ҷ� �ڼ��� �ڼձ��� ��������� �����ϴ� �Լ�.
	void ReMoveChildRecursive(Node<T>* child)
	{
		//����Լ� ���� ����
		if (child == nullptr)
		{
			return;
		}

		//�ڼ� ��� ��������
		List<Node<T>*>& children = child->GetChildern();
		//����� �� �ڼ��� ���� ���
		if (children.Size() == 0)
		{
			//�θ��� �ڼ� ��Ͽ��� ���� ����
			child->GetParent()->GetChildern().Remove(child);

			delete child;
			child = nullptr;

			return;
		}
		
		//�ڼ��� �ִ� ����� ��
		while (children.Size() > 0)
		{
			ReMoveChildRecursive(children[0]);
		}

		//�ڼ��� ��� ������ �Ŀ��� �θ� ��Ͽ��� ���� ����
		child->GetParent()->GetChildern().Remove(child);

		delete child;
		child = nullptr;
	}

private:
	//��忡 ������ ������
	T data;

	//�θ� ���� ����
	Node<T>* parent = nullptr;

	//�ڼ� ��� ����Ʈ(���� �迭)
	List<Node<T>*> children;
};