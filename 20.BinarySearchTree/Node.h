#pragma once

template<typename T>
class Node
{
public:
	Node(const T& data , Node<T>* parent = nullptr)
		:data(data), parent(parent)
	{

	}


public:
	//Getter & Settrer
	T GetData() const
	{
		return data;
	}

	//�θ�
	Node<T>* GetParent() const
	{
		return parent;
	}
	//���� �ڼ�.
	Node<T>* GetLeftChild() const
	{
		return left;
	}

	//������ �ڼ�.
	Node<T>* GetRightChild() const
	{
		return right;
	}

	void SetData(const T& newData)
	{
		data = newData;
	}

	void SetParent(Node<T>* newParent)
	{
		parent = newParent;
	}

	void SetLeftChild(Node<T>* newLeftChild)
	{
		left = newLeftChild;
	}

	void SetRightChild(Node<T>* newRightChild)
	{
		right = newRightChild;
	}

private:
	//��尡 ������ ������.
	T data;

	//�θ�
	Node<T>* parent = nullptr;

	//���� �ڼ�.
	Node<T>* left = nullptr;

	//������ �ڼ�.
	Node<T>* right = nullptr;
};