#pragma once
#include <iostream>	
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
		List<Node<T>*>& childern = root->GetChildern();
		
		while (childern.Size() > 0)
		{
			root->ReMoveChild(childern[0]);
		}

		delete root;
		root = nullptr;
	}

	bool ReMove(const T& data)
	{
		//Todo: 삭제할 노드를 검색하고, 삭제하는 함수 작성 후 호출.
		Node<T>* outNode = nullptr;
		bool result = Find(data, outNode);
		
		if (result == false) //검색실패
		{
			std::cout << "삭제할 노드를 찾지 못했습니다.\n";

			return false;
		}

		//여기까지 오면 검색 성공.
		//경우의 수1: 삭제할 노드가 루트 노드인 경우
		if (outNode == root)
		{
			std::cout << "루트는 제거할 수 없습니다.\n";
			return false;
		}

		//경우의 수2:
		Node<T>* parent = outNode->GetParent();
		parent->ReMoveChild(outNode);

		return true;
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

	//전위 순회 함수(부모를 먼저 방문 -> 자손 방문)
	void PreOrderTraverse()
	{
		PreOrderTraverseRecursive(root);
	}

	//전위 순회 재귀 함수.
	//node: 방문할 기준 노드.
	//depth: 출력할 때 부모-자손 구분을 위해 들여쓰기할 값.
	void PreOrderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		if (node == nullptr)
		{
			return;
		}

		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		std::cout << node->GetData() << "\n";

		List<Node<T>*>& children = node->GetChildern();

		if (children.Size() == 0)
		{
			return;
		}

		for (int ix = 0; ix < children.Size(); ++ix)
		{
			Node<T>* child = children[ix];
			PreOrderTraverseRecursive(child, depth + 1);
		}
	}

private:

	//루트 노드.
	Node<T>* root = nullptr;
};