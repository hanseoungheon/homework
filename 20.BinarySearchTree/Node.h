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

	//부모
	Node<T>* GetParent() const
	{
		return parent;
	}
	//왼쪽 자손.
	Node<T>* GetLeftChild() const
	{
		return left;
	}

	//오른쪽 자손.
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
	//노드가 저장할 데이터.
	T data;

	//부모
	Node<T>* parent = nullptr;

	//왼쪽 자손.
	Node<T>* left = nullptr;

	//오른쪽 자손.
	Node<T>* right = nullptr;
};