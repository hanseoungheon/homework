#include "RedBlackTree.h"

//메모리 해제 함수.
template<typename T>
void SafeDelete(T*& resource)
{
	if (resource != nullptr)
	{
		delete resource;
		resource = nullptr;
	}
}

Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	//초기설정.
	if (nil == nullptr)
	{
		//Nil 노드를 생성.
		nil = new Node(0, Color::Black);
	}

	root = nil;
}
RedBlackTree::~RedBlackTree()
{
	//Todo: 재귀적으로 모든 모드를 삭제하는 함수 작성 후 호출.
	//Nil 노드 삭제,
	SafeDelete(nil);
	//if (nil != nullptr)
	//{
	//	delete nil;
	//	nil = nullptr;
	//}
}

bool RedBlackTree::Find(int data, Node*& outNode)
{
	if (root == nil)
	{
		return false;
	}

	return FindRecursive(data, root, outNode);
}

bool RedBlackTree::Insert(int data)
{
	//중복 허용 x
	Node* currentNode = nullptr;
	if (Find(data, currentNode) == true)
	{
		std::cout << "이미 같은 값이 있습니다.\n";
		return false;
	}

	//삽입 처리.
	//return InsertRecusive(currentNode,);

	//트리가 비었으면 루트에 추가
	if (root == nil)
	{
		//루트는 반드시 블랙
		root = CreateNode(data, Color::Black);
		return true;
	}

	//재귀적으로 삽입할 위치 검색 후 삽입 처리.
	Node* newNode = CreateNode(data, Color::Red);
	InsertRecusive(root, newNode);

	//삽입 후 노드 정리.
	newNode->SetColor(Color::Red);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	//삽입 후 정리.
	RestructeAfterInsert(newNode);
}

Node* RedBlackTree::CreateNode(int data, Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	return newNode;
}

bool RedBlackTree::FindRecursive(int data, Node* currentNode, Node*& outNode)
{
	//종료 조건.
	if (currentNode == nil)
	{
		outNode = nullptr;
		return false;
	}

	//값 확인 > 검색 성공 확인.
	if (currentNode->GetData() == data)
	{
		outNode = currentNode;
		return true;
	}

	//작은 경우.
	if (currentNode->GetData() > data)
	{
		return FindRecursive(data, currentNode->GetLeftChild(), outNode);
	}

	//큰 경우
	return FindRecursive(data, currentNode->GetRightChild(), outNode);

	return false;
}

void RedBlackTree::InsertRecusive(Node* currentNode, Node* newNode)
{
	//작으면 왼쪽 하위 트리에 삽입.
	if (currentNode->GetData() > newNode->GetData())
	{
		//왼쪽 하위 자손이 없으면, 왼쪽 자손으로 추가.
		if (currentNode->GetLeftChild() == nil)
		{
			currentNode->SetLeftChild(newNode);

			newNode->SetParent(currentNode);

			return;
		}

		InsertRecusive(currentNode->GetLeftChild(), newNode);
	}

	else //크거나 같으면 오른쪽 하위 트리에 삽입.
	{
		//오른쪽 하위 자손이 없으면, 오른쪽 자손으로 추가.
		if (currentNode->GetRightChild() == nil)
		{
			currentNode->SetRightChild(newNode);

			newNode->SetParent(currentNode);

			return;
		}

		InsertRecusive(currentNode->GetRightChild(), newNode);
	}
}

void RedBlackTree::RestructeAfterInsert(Node* newNode)
{
	//부모 노드가 빨간색인 경우(Red-Red-Conflict).
	while (newNode != root && newNode->GetParent()->GetColor() == Color::Red)
	{
		//부모와 삼촌을 Black, 할아버지를 Red로 변경 후, 할아버지 기준으로 다시 검사
		//삼촌 가져오기-> 부모의 위치에 따라 달라짐.
		if (newNode->GetParent() 
			== newNode->GetParent()->GetParent()->GetLeftChild()) //부모의 부모의 자식는 엄마
		{
			//엄마의 형제는 삼촌
			Node* uncle = newNode->GetParent()->GetParent()->GetRightChild();

			//Cas1. 삼촌도 빨강.
			//부모와 삼촌을 블랙으로, 할아버지는 빨강으로.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				//할아버지를 빨간색으로 변경.
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				//기준을 하랑버지로 변경.
				newNode = newNode->GetParent()->GetParent();
				continue;
			}

			//삼촌이 검정색일때.
			//부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전

			//CASE2. 지그재그
			//Case3. 일직선으로 변경 후 문제 해결 시도.
			if (newNode == newNode->GetParent()->GetRightChild());
			{
				//회전.(좌회전)

			}

			//Case3: 부모와 나의 위치가 일직선일때.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

		}

		else
		{
			//엄마의 형제는 삼촌
			Node* uncle = newNode->GetParent()->GetParent()->GetRightChild();

			//Cas1. 삼촌도 빨강.
			//부모와 삼촌을 블랙으로, 할아버지는 빨강으로.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				//할아버지를 빨간색으로 변경.
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				//기준을 하랑버지로 변경.
				newNode = newNode->GetParent()->GetParent();
				continue;
			}

			//삼촌이 검정색일때.
			//부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전

			//CASE2. 지그재그
			//Case3. 일직선으로 변경 후 문제 해결 시도.
			if (newNode == newNode->GetParent()->GetRightChild());
			{
				//회전.(우회전)

			}

			//Case3: 부모와 나의 위치가 일직선일때.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);


			//좌회전.
		}

	}


}

void RedBlackTree::RotateToLeft(Node* node)
{
	//오른쪽 자손 노드.
	Node* right = node->GetRightChild();

	node->SetRightChild(right->GetLeftChild());


	//부모 정리.
	if (right->GetLeftChild() != nil)
	{
		right->GetLeftChild()->SetParent(node);
	}

	//부모가 root인 경우.
	if (right->GetParent() == root)
	{
		//루트 변경.
		root = right;
		right->SetParent(nullptr);
	}
	//부모가 root가 아닌 경우.
	else
	{
		//조부모 기준으로 부모가 어디에 있었는지 확인.
		if (node == node->GetParent()->GetLeftChild())
		{
			node->GetParent()->SetLeftChild(right);
		}
		else
		{
			node->GetParent()->SetRightChild(right);
		}
	}

	//오른쪽 자손의 왼쪽 자손으로 부모 노드 등록.
	right->SetLeftChild(node);

	//오른쪽 자손의 부모를 조부모로 설정.
	right->SetParent(node->GetParent());

	//부모의 부모를 오른쪽 자손으로 설정.
	node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node* node)
{
	//왼쪽 자손 노드.
	Node* left = node->GetLeftChild();

	node->SetLeftChild(left->GetRightChild());
}

