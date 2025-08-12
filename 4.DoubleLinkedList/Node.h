#pragma once

template<typename T>
class Node
{
	template<typename T>
	friend class LinkedList;

public:
	Node()
		:data(),next(nullptr), previous(nullptr)
	{

	}

	~Node()
	{

	}
private:
	T data;

	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;
};