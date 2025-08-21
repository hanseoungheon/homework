#pragma once

#include "Node.h"
#include <iostream>

template<typename T>
class BinaryTree
{
public:
	BinaryTree()
		: root(nullptr)
	{

	}

	BinaryTree(const T& data)
	{
		root = new Node<T>(data);
	}

	~BinaryTree()
	{
		if (root != nullptr)
		{
			root->Destroy();
		}
	}

	//자손 추가 함수.
	void AddLeftChild(const T& parentData, const T& childData)
	{
		//1.검색(부모찾기 먼저)
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		if (result == true)
		{
			parent->AddLeftChild(childData);
			return;
		}

		//검색 실패
		std::cout << "부모 노드를 찾지 못했습니다.\n";
	}

	void AddRightChild(const T& parentData, const T& childData)
	{
		//1.검색(부모찾기 먼저)
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		if (result == true)
		{
			parent->AddRightChild(childData);
			return;
		}

		//검색 실패
		std::cout << "부모 노드를 찾지 못했습니다.\n";
	}

	//데이터 찾기 함수
	bool Find(const T& data, Node<T>*& outNode)
	{
		//재귀 검색 함수 호출.
		return FindRecursive(data, root, outNode);
	}

	//전위 순회 함수.
	void PreorderTraverse()
	{
		PreorderTraverseRecursive(root);
	}

	//삭제
	bool DeleteNode(const T& data)
	{
		//1. 검색.
		Node<T>* deleteNode = nullptr;
		bool result = Find(data, deleteNode);

		//찾았으면 삭제.
		if (result == true)
		{
			deleteNode->Destroy();
			
			return true;
		}

		//못찾았으면 메시지 출력하기.
		std::cout << "노드 검색에 실패하여 삭제를 못했습니다.\n";
		return false;
	}

	//Getter
	//왼쪽.오른쪽 자손 반환 함수.
	Node<T>* GetLeft() const
	{
		return root->GetLeftChild();
	}

	Node<T>* GetRight() const
	{
		return root->GetRightChild();
	}


private:
	//재귀 검색 함수.
	bool FindRecursive(const T& data, Node<T>* node,Node<T>*& outNode)
	{
		//종료 조건.
		if (node == nullptr)
		{
			//출력에 null설정
			outNode = nullptr;
			return false;
		}

		//검색 확인 단계
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		//왼쪽 자손으로 검색 진행.
		bool result = FindRecursive(data, node->GetLeftChild(), outNode);

		if (result == true)
		{
			return true;
		}

		//오른쪽 자손으로 검색 진행.
		result = FindRecursive(data, node->GetRightChild(), outNode);

		if (result == true)
		{
			return true;
		}

		//검색 실패
		outNode = nullptr;

		return false;
	}

	//재귀 전위 순회 함수
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		//종료조건
		if (node == nullptr)
		{
			return;
		}

		//깊이 출력
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		//부모 방문.
		std::cout << node->GetData() << "\n";

		PreorderTraverseRecursive(node->GetLeftChild(), depth + 1);

		PreorderTraverseRecursive(node->GetRightChild(), depth + 1);
	}

private:
	//루트 노드(시작점 노드)
	Node<T>* root = nullptr;
};