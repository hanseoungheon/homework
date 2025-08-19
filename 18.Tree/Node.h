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

	//복사 생성자 제거
	Node(const Node& other) = delete;

	~Node()
	{
		parent = nullptr;
	}

	//값을 전달해서 자손을 추가하는 함수.
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
	//노드에 저장할 데이터
	T data;

	//부모 참조 변수
	Node<T>* parent = nullptr;

	//자손 노드 리스트(동적 배열)
	List<Node<T>*> children;
};