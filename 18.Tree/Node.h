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

	//삭제 
	//자손 삭제 함수.
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
	//자손 노드를 삭제할때 자손의 자손까지 재귀적으로 삭제하는 함수.
	void ReMoveChildRecursive(Node<T>* child)
	{
		//재귀함수 종료 조건
		if (child == nullptr)
		{
			return;
		}

		//자손 목록 가져오기
		List<Node<T>*>& children = child->GetChildern();
		//경우의 수 자손이 없는 경우
		if (children.Size() == 0)
		{
			//부모의 자손 목록에서 나를 제거
			child->GetParent()->GetChildern().Remove(child);

			delete child;
			child = nullptr;

			return;
		}
		
		//자손이 있는 경우의 수
		while (children.Size() > 0)
		{
			ReMoveChildRecursive(children[0]);
		}

		//자손을 모두 삭제한 후에는 부모 목록에서 나를 제거
		child->GetParent()->GetChildern().Remove(child);

		delete child;
		child = nullptr;
	}

private:
	//노드에 저장할 데이터
	T data;

	//부모 참조 변수
	Node<T>* parent = nullptr;

	//자손 노드 리스트(동적 배열)
	List<Node<T>*> children;
};