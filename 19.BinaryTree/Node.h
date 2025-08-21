#pragma once

//이진 트리에 사용될 노드 클래스
template<typename T>
class Node
{
	template<typename T>
	friend class BinaryTree;

	//public 함수 = 인터페이스
public:

	// 생성자
	Node()
		: data(), parent(nullptr), left(nullptr), right(nullptr)
	{

	}

	Node(const T& data)
		: data(data), parent(nullptr), left(nullptr), right(nullptr)
	{

	}

	//기본 소멸자를 명시적으로 지정!
	~Node() = default;

	//-----------------------------------------------------------------------------//
	//자손 추가 함수 (AddChild<Left,Right>)
	void AddLeftChild(const T& data)
	{
		//노드를 생성해서 다른 함수 호출.
		AddLeftChild(new Node<T>(data));
	}
	void AddLeftChild(Node<T>* child) //오버로딩
	{
		child->SetParent(this);

		left = child;
	}

	void AddRightChild(const T& data)
	{
		//노드를 생성해서 다른 함수 호출.
		AddRightChild(new Node<T>(data));
	}
	void AddRightChild(Node<T>* child)
	{
		child->SetParent(this);

		right = child;
	}

	//삭제함수
	void Destroy()
	{
		//부모 노드 정리.
		if (parent != nullptr)
		{
			//이 노드가 부모 기준 왼쪽인지 확인.
			if (parent->GetLeftChild() == this)
			{
				parent->left = nullptr;
			}

			//이 노드가 부모 기준 오른쪽인지 확인.
			else if (parent->GetRightChild() == this)
			{
				parent->right = nullptr;
			}
		}

		//자손까지 방문해서 모두 제거해버리기.
		DestroyRecursive(this);
	}

	//Getter & Setter-------------------------------------------------------------//
	T GetData() const
	{
		return data;
	}

	Node<T>* GetParent() const
	{
		return parent;
	}

	void SetParent(Node<T>* newParent)
	{
		parent = newParent;
	}

	Node<T>* GetLeftChild() const
	{
		return left;
	}

	Node<T>* GetRightChild() const
	{
		return right;
	}

private:
	void DestroyRecursive(Node<T>* node)
	{
		//왼쪽 있는지 조건문으로 확인후 계속 내려가다가 마지막까지 내려가면 지움
		//그 후 올라오면서 오른쪽 확인후 내려가면 다시 왼쪽 확인
		//이런식으로 아래서 위로 재귀적으로 삭제.
		
		//탈출 조건
		if (node == nullptr)
		{
			return;
		}

		//자손 노드 존재 확인
		Node<T>* leftChild = node->GetLeftChild();
		Node<T>* rightChild = node->GetRightChild();

		//경우의 수 1. 자손이 없는 경우
		if (leftChild == nullptr && rightChild == nullptr)
		{
			delete node;
			node = nullptr;
			return;
		}

		//경우의 수 2: 자손이 있는 경우=> 재귀적으로 자손 노드 삭제.
		DestroyRecursive(leftChild);
		DestroyRecursive(rightChild);

		delete node;
		node = nullptr;
	}

private:
	//데이터
	T data;

	//부모노드
	Node<T>* parent = nullptr;
	//왼쪽, 오른쪽 자손
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};