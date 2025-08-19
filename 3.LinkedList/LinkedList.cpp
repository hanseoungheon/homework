	#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
	:head(nullptr),count(0)
{

}

LinkedList::~LinkedList()
{
	//삭제 로직
	//if (head != nullptr)
	//	delete head;
	//count = NULL;
	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		//다음 노드로 넘어가기 전에 임시 저장
		trail = current;

		//다음 노드로 이동
		current = current->next;
		
		//노드 삭제
		delete trail;
		trail = nullptr;

		//디버깅 목적
		--count;
	}
}

void LinkedList::AddToHead(int newData)
{
	//새로운 노드 생성
	Node* newNode = new Node(newData);

	//#1 Head가 비어있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}
	//#2 Head가 비어있지 않은 경우
	newNode->next = head;	//주소 복사
	head = newNode;
	++count;
}

void LinkedList::Insert(int newData)
{
	//맨 뒤에다가 추가하는 함수
	Node* newNode = new Node(newData);

	//#리스트가 비어있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	//#2 리스트가 비어있지 않은 경우
	//1. 마지막 노드 검색해야함.
	//타고 타고 가다가 nullptr을 만났을때?
	Node* current = head;
	Node* trail = nullptr;

	//next노드가 null일때까지 검색
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}


	//마지막 노드 검색 완료된 상태!
	trail->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	//Todo: 삭제로직 구현해야함

	//리스트가 비어있으면 종료
	if (head == nullptr)
	{
		std::cout << "리스트가 비어있어서 삭제가 불가능합니다.\n";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		//종료 조건
		//찾으려는 데이터를 가진 노드 검색에 성공한 경우!
		if (current->data == data)
		{
			break;
		}
			
		//못찾았으면 검색 이어감
		trail = current;
		current = current->next;
	}

	//경우의 수 확인
	//#1 리스트에 삭제하려는 데이터가 없음(못찾음)
	if (current == nullptr)
	{
		std::cout << "값: " << data << "를 찾지 못했습니다.";
		return;
	}

	//#2 검색에 성공한 경우
	//#2-1 삭제하려는 노드가 head인 경우
	if (current == head)
	{
		//head가 없으면 안되므로 그 다음 노드를 head로 지정
		head = head->next;

	}
	//#2-2 삭제하려는 노드가 head가 아닌 경우
	else
	{
		//[h]->[1]->[2]->[3]->nullptr
		//2를 지워야한다면
		//trail:1,current:2
		//[h]->[1]->[3]
		trail->next = current->next;
	}

	delete current;
	current = nullptr;
	--count;
}

void LinkedList::Print()
{
	//출력
	Node* current = head;

	while (current != nullptr)
	{
		//현재 노드 데이터 출력
		std::cout << *current << "\n";

		//다음 노드로 이동
		current = current->next;
	}
}

void LinkedList::MyNodeSort() //길이는 count
{
	Node* current = head;
	Node* trail = nullptr;
	Node* temp = nullptr;
	Node* previous = nullptr;
	for (int i = 0; i < count - 1; ++i)
	{
		std::cout << "i가 " << i << "일 때!\n";
		for (int j = 0; j < count - i - 1; ++j)
		{
			trail = current->next;
			temp = trail->next;
			if (current->data > (current->next)->data && current == head)
			{
				trail->next = head;
				head = trail;
				current->next = temp;


				previous = trail;
				current = trail->next;
				Print();
				std::cout << "\n";
				continue;
			}
			else if (current->data > (current->next)->data && current != head)
			{
				trail->next = current;
				current->next = temp;
				previous->next = trail;


				previous = trail;
				current = trail->next;
				Print();
				std::cout << "\n";
				continue;
			}
			Print();
			std::cout << "\n";

			previous = current;
			current = current->next;

		}
		current = head;
	}
}

void LinkedList::ChangeHead()
{
	Node* current = head;
	head = current->next;
}

void LinkedList::Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

