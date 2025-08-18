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
	//노드가 가지는 데이터
	T data;

	//부모 노드
	Node<T>* parent;

	//왼쪽 자손 노드
	Node<T>* left;

	//오른쪽 자손 노드
	Node<T>* right;
};