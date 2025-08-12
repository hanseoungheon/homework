#pragma once

#include <iostream>
#include "Node.h"

//노드 제거 함수
template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
class LinkedList
{
public:
	LinkedList()
		: first(new Node<T>()), last(new Node<T>()), count(0)
	{
		//시작 노드 서로 연결
		first->next = last;
		last->previous = first;
	}

	~LinkedList()
	{
		//@Incomplete: 삭제 함수 구현 후 호출 필요함.

		Clear();

		//기본 노드 삭제
		SafeDelete(first);
		SafeDelete(last);
	}

	//노드 전체 삭제 함수
	void Clear()
	{
		//시작 노드 저장
		Node<T>* current = first->next;

		//끝까지 반복
		while (current != nullptr && current != last)
		{
			Node<T>* next = current->next;
			SafeDelete(current);
			current  = next;
		}

		//카운트 정리
		count = 0;

		//초기상태로 초기화
		first->next = last;
		last->previous = first;

	}

	void Print()
	{
		Node<T>* current = first->next;

		while (current && current != last)
		{
			std::cout << "데이터: " << current->data << "\n";
			current = current->next;
		}
	}

	//마지막 위치에 노드 추가하는 함수
	void PushLast(const T& newData)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		//newNode:5
		//[f]<-[1]<-[2]<-[3]<-[5]<-[1]

		//원래의 마지막 노드 임시 저장
		Node<T>* previous = last->previous;
		previous->next = newNode;
		newNode->previous = previous;

		newNode->next = last;
		last->previous = newNode;

		++count;
	}
	
private:
	//처음과 마지막을 가리키는 노드
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;

	//리스트에 저장된 요소 수
	int count = 0;
};