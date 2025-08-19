#pragma once
	
#include "List.h"
#include "Node.h"

template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))
	{

	}

	~Tree()
	{
		//Todo: 자손 모두 삭제하는 함수 구현 후 호출해야 함.
	}

	void AddChild(const T& parentData, const T& childData)
	{
		//검색.
		Node<T>* outParent = nullptr;
		bool result = Find(parentData, outParent);

		//부모노드 검색에 성공했으면 부모노드의 자손으로 노드 추가.
		if (result)
		{
			outParent->AddChild(childData);
			return;
		}
		//부모노드 검색 실패
		std::cout << "해당 값을 갖는 부모 노드 검색에 실패했습니다.\n";
	}

	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		//재귀 함수 종료 조건
		if (node == nullptr)
		{
			outNode = nullptr; //못찾았음.
			return false;
		}

		//검색 성공
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}


		//자손을 재귀적으로 검색.
		List<Node<T>*>& children = node->GetChildern();
		int count = children.Size();

		for (int ix = 0; ix < count; ++ix)
		{
			//자손 검색 진행
			Node<T>* child = children[ix];
			bool result = FindRecursive(data, child, outNode);

			if (result == true)
			{
				return true;
			}
		}

		//검색 실패
		outNode = nullptr;
		return false;
	}

private:

	//루트 노드.
	Node<T>* root = nullptr;
};