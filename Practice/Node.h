#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
	Node(const T& data)
		:data(data), parent(parent), left(nullptr), right(nullptr)
	{

	}

	~Node()
	{
		parent = nullptr;
		left = nullptr;
		rigbt = nullptr;
	}
private:
	//��尡 ������ ������
	T data;

	//�θ� ���
	Node<T>* parent;

	//���� �ڼ� ���
	Node<T>* left;

	//������ �ڼ� ���
	Node<T>* right;
};