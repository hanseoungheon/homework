#pragma once

#include <iostream>
#include "Node.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
		:root(nullptr)
	{

	}

	~BinarySearchTree()
	{
		//Destroy();
	}

	//삽입
	//규칙
	//0. 중복된 값 허용 x
	// 1. 시작 - 루트에서부터 비교 시작.
	// 1-1 루트가 null이면 새 노드를 루트로 지정한다.
	// 2. 새로 추가하는 값이 비교하는 노드보다 작으면 왼쪽 서브 트리로 비교를 이어간다.
	// 3. 새로 추가하는 값이 비교하는 노드보다 크면 오른쪽 서브 트리로 비교를 이어간다.

	bool InsertNode(const T& newData)
	{
		//검색(중복된 값이 있는지 확인, 즉 이미 해당 값이 노드안에 있는지 확인)
		if (SearchNode(newData) == true)
		{
			std::cout << "Error:: 이미 중복된 값이 있으므로  추가할 수 없음";
			return false;
		}

		if (root == nullptr) //루트가 비어있으면 루트로 지정
		{
			root = new Node<T>(newData);
			return true;
		}

		root 
	}

	void DeleteNode(const T& deleteData)
	{
		//재귀적으로 삭제하는 함수를 호출
		//삭제 연산의 시작은 root
		//이후 오른쪽으로 점진적으로 가면서 재귀적으로 삭제
		
		root = DeleteNodeRecursive(root, deleteData);
	}

	Node<T>* SerachMinValue(Node<T>* Node)
	{
		while (data->left != nullptr) //왼쪽으로 계속 이동하면서 nullptr일때까지 탐색
		{
			node = node->left;
		}
		
		return node; //제일 왼쪽에 있는 작은 값 반환.
	}

	bool SearchNode(const T& data)
	{
		SearchNodeRecursive(root, data);
	}

	bool SearchNodeRecursive(Node<T>* node, const T& data)
	{
		if (node == nullptr) //검색실패
		{
			return false;
		}

		if (node->data == data) //노드의 data와 인자로 받은 data가 같으면 참
		{
			return true;
		}
		else if (node->data > data) //노드의 데이터가 인자로 받은 데이터보다 크면 왼쪽으로
		{
			return SearchNodeRecursive(node->left, data);
		}
		else //반대 명제 node->data < data
		{
			return SearchNodeRecursive(node->right, data);
		}
	}

	void PreorderTraverse(int depth = 0)
	{
		std::cout << "========== 전위 순회 시작 ==========\n";

		PreorderTraverseRecursive(root, depth);

		std::cout << "========== 전위 순회 종료 ==========\n";
	}


	void InorderTraverse(int depth = 0)
	{
		std::cout << "========== 중위 순회 시작 ==========\n";

		// 출력을 위해 중위 순회 방식으로 재귀 함수를 호출.
		// 탐색 시작은 루트 노트에서 부터.
		InorderTraverseRecursive(root, depth);

		std::cout << "========== 중위 순회 종료 ==========\n";
	}

	// 출력 (후위 순회).
	void PostorderTraverse(int depth = 0)
	{
		std::cout << "========== 후위 순회 시작 ==========\n";

		// 출력을 위해 후위 순회 방식으로 재귀 함수를 호출.
		// 탐색 시작은 루트 노트에서 부터.
		PostorderTraverseRecursive(root, depth);

		std::cout << "========== 후위 순회 종료 ==========\n";
	}

private:
	// 재귀적으로 삽입을 처리하는 함수.
	// node: 현재 비교하는 노드.
	// parent: node의 부모 노드.
	// newData: 삽입하려는 새 데이터.
	Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& newData)
	{
		if (node == nullptr) //노드가 nullptr이면 새로 생성한 노드를 반환
		{
			return new Node<T>(newData, parent);
		}

		// 추가하려는 값이 비교 노드보다 작으면, 왼쪽 서브 트리로 탐색.
		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}

		// 추가하려는 값이 비교 노드보다 크면, 오른쪽 서브 트리로 탐색.
		else
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	//삭제 재귀함수
	Node<T>* DeleteNodeRecursive(Node<T>* node, const T& deleteData)
	{
		if (node == nullptr) 
		{
			std::cout << "삭제할 데이터를 찾지 못함";
			return nullptr;
		}

		if (node->data > deleteData) //삭제하려는 데이터가 비교 데이터보다 작으면 왼쪽으로 이동
		{
			node->left = DeleteNodeRecursive(node->left, deleteData);
		}
		// 삭제하려는 데이터가 비교 데이터보다 크면 오른쪽 서브 트리로 이동.
		else if (node->data < deleteData)
		{
			node->right = DeleteNodeRecursive(node->right, deleteData);
		}


		// 찾으면, 삭제 처리.
		else
		{
			// 경우1 - 자식이 없는 경우. (둘 모두 null인 경우)
			if (node->left == nullptr && node->right == nullptr)
			{
				// 노드 삭제 후 함수 종료.
				delete node;
				return nullptr;
			}

			// 경우3 - 자식이 둘 다 있는 경우. (둘 모두 null이 아닌 경우).
			if (node->left != nullptr && node->right != nullptr)
			{
				// 삭제되는 노드의 오른쪽 서브 트리에서 가장 작은 값을 검색해서 삭제하는
				// 노드의 값을 업데이트.
				node->data = SearchMinValue(node->right)->data;

				// 위에서 구한 오른쪽 서브 트리에서 가장 작은 값을 가진 노드를 삭제.
				node->right = DeleteNodeRecursive(node->right, node->data);
			}
			else
			{
				// 경우2 - 자식이 하나만 있는 경우 (둘 중 하나만 null인 경우).
				if (node->left == nullptr)
				{
					// 오른쪽 자손을 반환하기 위해 임시로 포인터 저장.
					Node<T>* right = node->right;

					// 노드 제거.
					delete node;

					// 오른쪽 자손 반환.
					return right;
				}

				else if (node->right == nullptr)
				{
					// 왼쪽 자손을 반환하기 위해 임시로 포인터 저장.
					Node<T>* left = node->left;

					// 노드 제거.
					delete node;

					// 왼쪽 자손 반환.
					return left;
				}
			}
		}

	}

	// 전위 순회 재귀 함수.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		if (node == nullptr) //종료 조건
		{
			//트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << " ";
			}

			std::cout << "null\n";

			return;
		}


		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		std::cout << node->data << "\n";

		// 왼쪽 서브 트리를 전위 순회.
		PreorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 서브 트리를 전위 순회.
		PreorderTraverseRecursive(node->right, depth + 1);
	}

	void InorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (node == nullptr)
		{
			// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// 왼쪽 서브 트리를 중위 순회.
		InorderTraverseRecursive(node->left, depth + 1);

		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리.
		std::cout << node->data << "\n";

		// 오른쪽 서브 트리를 중위 순회.
		InorderTraverseRecursive(node->right, depth + 1);
	}

	// 후위 순회 재귀 함수.
	void PostorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (node == nullptr)
		{
			// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// 왼쪽 서브 트리를 후위 순회.
		PostorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 서브 트리를 후위 순회.
		PostorderTraverseRecursive(node->right, depth + 1);

		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리.
		std::cout << node->data << "\n";
	}

private:
	// 모든 노드를 제거할 때 사용하는 함수.
	void Destroy()
	{
		// 루트 노드가 null이면 종료.
		if (root == nullptr)
		{
			return;
		}

		// 왼쪽 자손 > 오른쪽 자손 > 루트 순으로 제거.
		DestroyRecursive(root);
	}

	void DestroyRecursive(Node<T>* node)
	{
		// 재귀함수 종료 조건.
		if (node == nullptr)
		{
			return;
		}

		// 왼쪽 자손 / 오른쪽 자손 확인.
		Node<T>* left = node->left;
		Node<T>* right = node->right;

		// 자손이 없는 경우.
		if (left == nullptr && right == nullptr)
		{
			// 노드 삭제 후 함수 종료.
			delete node;
			return;
		}

		DestroyRecursive(left);
		DestroyRecursive(right);

		delete node;
	}


private:
	Node<T>* root;

};