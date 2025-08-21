#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = default;

	~BinarySearchTree()
	{
		//Todo: 삭제하는 함수 구현 후 에 호출해야함.
		Destroy();
	}

	//삽입
	//-규칙-
	//1. 중복된 값은 허용하지 않는다.
	//2. 루트에서부터 비교 시작. 2-1 루트가 null이면 새 노드를 루트로 지정.
	//3. 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위트리로 비교 이어감.
	//4. 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 트리로 비교 이어감.

	bool Insert(const T& newData)
	{
		//중복 여부 확인.
		Node<T>* outNode = nullptr;
		if (Find(newData, outNode) == true)
		{
			//중복됐으면 종료
			std::cout << "Error: 이미 같은 값이 노드에 있습니다.";
			return false;
		}
		
		//루트가 null이면 루트로 지정.
		if (root == nullptr)
		{
			root = new Node<T>(newData);
			return true;
		}

		//Todo: 삽입 재귀함수 작성 후 호출.

		root = InsertRecusive(newData, root, nullptr);
		return true;
	}
	

	//검색
	bool Find(const T& data, Node<T>* outNode) const
	{
		Node<T>* currentNode = root;

		//재귀적으로 검사하는 함수.
		return FindRecusive(data, currentNode, outNode);
	}



	

	//삭제
	bool Delete(const T& data)
	{
		//검색
		Node<T>* deleteNode = nullptr;
		if (Find(data, deleteNode) == false)
		{
			std::cout << "삭제할 노드를 찾지 못했습니다.";
			return false;
		}

		//재귀적으로 삭제하는 함수 호출.
		root = DeleteRecursive(data,root);
		return true;
	}

	//중위 순회(정렬된 순서대로 출력 가능함.)

	//최솟값 검색
	Node<T>* FindMinValue(Node<T>* currentNode)
	{
		//가장 왼쪽 끝에 있는 노드 검색.
		while (currentNode->GetLeftChild() != nullptr)
		{
			currentNode = currentNode->GetLeftChild();
		}

		return currentNode;
	}

	//최댓값 검색
	Node<T>* FindMaxValue(Node<T>* currentNode)
	{
		//가장 오른쪽 끝에 있는 노드 검색.

		while (currentNode->GetRightChild() != nullptr)
		{
			currentNode = currentNode->GetRightChild();
		}

		return currentNode;
	}

private:
	bool FindRecusive(const T& data, Node<T>* currentNode,Node<T>* outNode) const
	{
		//종료 조건.(검색 실패)
		if (currentNode == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		//검색 성공했는지 확인.
		if (currentNode->GetData() == data)
		{
			outNode = currentNode;
			return true;
		}

		//검색한 노드가 찾으려는 값보다 크면?
		if (currentNode->GetData() > data)
		{
			return FindRecusive(data, currentNode->GetLeftChild(), outNode);
		}


		//검색한 노드가 찾으려는 값보다 작은 경우?
		if (currentNode->GetData() < data)
		{
			return FindRecusive(data, currentNode->GetRightChild(), outNode);
		}
		
		//예외처리.
		return false;
	}

	Node<T>* InsertRecusive(const T& data,Node<T>* currentNode,Node<T>* parent)
	{
		//종료 조건.
		if (currentNode == nullptr)
		{
			//currentNode가 NULL이면 삽입할 위치를 찾음.

			return new Node<T>(data, parent);
		}	

		//현재 검색중인 노드의 데이터가 넣으려는 데이터보다 큰 경우 / 데이터가 작은 경우
		if (currentNode->GetData() > data)
		{
			currentNode->SetLeftChild(InsertRecusive(data, 
				currentNode->GetLeftChild(),
				currentNode));
		}
		else //큰 경우
		{
			currentNode->SetRightChild(InsertRecusive(data, 
				currentNode->GetRightChild(),
				currentNode));
		}

		return currentNode;
	}

	Node<T>* DeleteRecursive(const T& data, Node<T>* currentNode)
	{
		//종료조건
		if (currentNode != nullptr)
		{
			return nullptr;
		}

		//경우의 수 1. 작은 경우
		if (currentNode->GetData() > data)
		{
			currentNode->SetLeftChild(DeleteRecursive(data,currentNode->GetLeftChild()));
		}

		else if (currentNode->GetData() < data)
		{
			currentNode->SetRightChild(DeleteRecursive(data, currentNode->GetRightChild()));
		}

		else //삭제할 노드 찾음.
		{
			//경우의 수 ( 삭제처리할때 이진검색트리의 조건에 부합해야함)

			//경우의 수 1. 자식이 둘다 없는 경우.
			if (currentNode->GetLeftChild() == nullptr
				&& currentNode->GetRightChild() == nullptr)
			{
				delete currentNode;
				return nullptr;
			}

			//경우의 수 2. 자식이 둘다 있는 경우.
			if (currentNode->GetLeftChild() && currentNode->GetRightChild())
			{
				//방법을 택 1.
				//왼쪽 하위에서 가장 큰 값으로 대체, 오른쪽 하위에서 가장 작은 값으로 대체.

				//삭제할 위치의 노드값을 대체값으로 할당.
				currentNode->SetData(FindMinValue(currentNode->GetRightChild())->GetData());

				//대체당하는 노드를 삭제.
				currentNode->SetRightChild(
					DeleteRecursive(
					currentNode->GetData(),
					currentNode->GetRightChild()
					)
				);
			}

			//경우의 수 3. 자식이 하나만 있는 경우.
			else
			{
				//방법을 택 1.
				if (currentNode->GetRightChild() == nullptr) //왼쪽만 있음.
				{
					//왼쪽 자손을 반환하기 위해 임시 저장.
					Node<T>* leftChild = currentNode->GetLeftChild();
					delete currentNode;

					return leftChild;
				}
				else if (currentNode->GetLeftChild() == nullptr)// 오른쪽만 있음.
				{
					Node<T>* rightChild = currentNode->GetRightChild();
					delete currentNode;

					return rightChild;
				}
			}
		}

		return currentNode;
	}

	void Destroy()
	{
		//루트가 비어있으면 종료,
		if (root == nullptr)
		{
			return;
		}

		//자손 모두 제거하고 루트 제거하도록 처리.
		DestroyRecusive(root);
	}

	//파괴 재귀함수.

	void DestroyRecusive(Node<T>* currentNode)
	{
		if (currentNode == nullptr)
		{
			return;
		}

		Node<T>* leftChild = currentNode->GetLeftChild();
		Node<T>* rightChild = currentNode->GetRightChild();

		if (!leftChild && !rightChild)// 자손이 없으면
		{
			delete currentNode;
			currentNode = nullptr;

			return;
		}

		DestroyRecusive(leftChild);
		DestroyRecusive(rightChild);

		delete currentNode;
		currentNode = nullptr;
	}

private:
	//루트 노드
	Node<T>* root = nullptr;
};