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

//Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	//초기설정.
	if (nil == nullptr)
	{
		//Nil 노드를 생성.
		nil = new Node(0, Color::Black);
	}

	//루트 노드를 Nil로 설정(기본은 트리가 빈 상태로 설정).
	root = nil;
}
RedBlackTree::~RedBlackTree()
{
	//재귀적으로 모든 모드를 삭제하는 함수 작성 후 호출.
	DestroyRecursive(root);
	//Nil 노드 삭제,
	SafeDelete(nil);
	//아래 코드를 캡슐화한것.
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

//메시지.
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

	return true;
}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
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
				// 부모와 삼촌을 검정색으로 변경.
				newNode->GetParent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);

				//할아버지를 빨간색으로 변경.
				newNode->GetParent()->GetParent()->SetColor(Color::Red);

				//기준을 할아버지로 변경.
				newNode = newNode->GetParent()->GetParent();
				continue;
			}

			//삼촌이 검정색일때.
			//부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전

			//CASE2. 지그재그
			//Case3. 일직선으로 변경 후 문제 해결 시도.
			if (newNode == newNode->GetParent()->GetRightChild())
			{
				//회전.(좌회전)
				newNode = newNode->GetParent(); //부모를 받아서.
				RotateToLeft(newNode); //좌회전 시키기.
			}

			//Case3: 부모와 나의 위치가 일직선일때.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//우회전.
			RotateToRight(newNode->GetParent()->GetParent());

		}

		else
		{
			//엄마의 형제는 삼촌
			Node* uncle = newNode->GetParent()->GetParent()->GetLeftChild();

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
			if (newNode == newNode->GetParent()->GetLeftChild())
			{
				//회전.(우회전)
				newNode = newNode->GetParent(); // 부모를 받아서.
				RotateToRight(newNode);
			}

			//Case3: 부모와 나의 위치가 일직선일때.
			//부모를 Black으로 할아버지를 Red로.
			newNode->GetParent()->SetColor(Color::Black);
			newNode->GetParent()->GetParent()->SetColor(Color::Red);

			//좌회전.
			RotateToLeft(newNode->GetParent()->GetParent());
		}

	}

	//마지막으로 루트 노드 색상을 정리.
	root->SetColor(Color::Black);
}


// 회전: 부모와 자손의 위치를 바꾸는 기능.
// 좌회전 -> 왼쪽으로 회전. 오른쪽 자손과 부모의 위치를 교환.
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


// 회전: 부모와 자손의 위치를 바꾸는 기능.
// 우회전 -> 오른쪽으로 회전. 왼쪽 자손과 부모의 위치를 교환.
void RedBlackTree::RotateToRight(Node* node)
{
	//왼쪽 자손 노드.
	Node* left = node->GetLeftChild();

	//왼쪽 자손의 오른쪽 자손 노드를 부모의 왼쪽 자손으로 등록.
	node->SetLeftChild(left->GetRightChild());

	//부모 정리.
	if (left->GetRightChild() != nil)
	{
		left->GetRightChild()->SetParent(node);
	}

	//부모가 root인 경우.
	if (left->GetParent() == root)
	{
		//루트 변경.
		root = left;
		left->SetParent(nullptr);
	}
	//부모가 root가 아닌 경우.
	else
	{
		//조부모 기준으로 부모가 어디에 있었는지 확인.
		if (node == node->GetParent()->GetLeftChild())
		{
			node->GetParent()->SetLeftChild(left);
		}
		else
		{
			node->GetParent()->SetRightChild(left);
		}
	}

	//왼쪽 자손의 오른쪽 자손으로 부모 노드 등록.
	left->SetRightChild(node);

	//왼쪽 자손의 부모를 조부모로 설정.
	left->SetParent(node->GetParent());

	//부모의 부모를 왼쪽 자손으로 설정.
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 노드 색상이 검정이면 blackCount 증가.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// 부모 표기 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	// 부모 노드가 있는지 확인.
	if (node->GetParent())
	{
		// 부모 노드의 데이터 저장.
		parentData = node->GetParent()->GetData();

		// 부모 노드로부터 현재 노드의 위치 설정.
		if (node == node->GetParent()->GetLeftChild())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// 검은색 수 출력을 위한 문자열.
	char blackCountString[50] = { };

	// 자손이 없으면 현재까지의 검은색 노드 수 설정.
	if (node->GetLeftChild() == nil && node->GetRightChild() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth 출력.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << "  ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout
		<< node->GetData() << " "
		<< node->GetColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->GetLeftChild(), depth + 1, blackCount);
	PrintRecursive(node->GetRightChild(), depth + 1, blackCount);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// 재귀 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 자식이 있는 경우.
	DestroyRecursive(node->GetLeftChild());
	DestroyRecursive(node->GetRightChild());

	// 노드 삭제.
	SafeDelete(node);
}

void SetTextColor(TextColor color)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}


