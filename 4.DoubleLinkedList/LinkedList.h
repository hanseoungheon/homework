#pragma once

#include <iostream>
#include "Node.h"

//��� ���� �Լ�
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
		//���� ��� ���� ����
		first->next = last;
		last->previous = first;
	}

	~LinkedList()
	{
		//@Incomplete: ���� �Լ� ���� �� ȣ�� �ʿ���.

		Clear();

		//�⺻ ��� ����
		SafeDelete(first);
		SafeDelete(last);
	}

	//��� ��ü ���� �Լ�
	void Clear()
	{
		//���� ��� ����
		Node<T>* current = first->next;

		//������ �ݺ�
		while (current != nullptr && current != last)
		{
			Node<T>* next = current->next;
			SafeDelete(current);
			current  = next;
		}

		//ī��Ʈ ����
		count = 0;

		//�ʱ���·� �ʱ�ȭ
		first->next = last;
		last->previous = first;

	}

	//ù ��ġ�� ������ ��� �߰��ϴ� �Լ�
	void PushFirst(const T& newData)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;
		
		Node<T>* next = first->next;
		newNode->next = next;
		first->next = newNode;
		newNode->previous = first;
		next->previous = newNode;

		++count;
	}

	//�����ϱ�
	void Delete(const T& deleteData)
	{
		//�������
		if (first->next = nullptr)
		{
			std::cout << "����ũ�� ��� �־� ��带 ������ �� �����ϴ�.";
			return;
		}

		Node<T>* deleteNode = first->next;

		while (deleteNode != nullptr && deleteNode != last)
		{
			if (deleteNode->data == deleteData)
			{
				break;
			}

			//��ã������ ��������
			deleteNode = deleteNode->next;
		}
		

		//��ã��
		if (deleteNode == nullptr || deleteNode = last)
		{
			std::cout << "������ ��带 ã�� ���߽��ϴ�.\n";
			return;
		}

		deleteNode->previous->next = deleteNode->next;
		deleteNode->next->previous = deleteNode->previous;

		SafeDelete(deleteNode);

		--count;
	}

	void Print()
	{
		Node<T>* current = first->next;

		while (current && current != last)
		{
			std::cout << "������: " << current->data << "\n";
			current = current->next;
		}
	}

	//������ ��ġ�� ��� �߰��ϴ� �Լ�
	void PushLast(const T& newData)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		//newNode:5
		//[f]<-[1]<-[2]<-[3]<-[5]<-[1]

		//������ ������ ��� �ӽ� ����
		Node<T>* previous = last->previous;
		previous->next = newNode;
		newNode->previous = previous;

		newNode->next = last;
		last->previous = newNode;

		++count;
	}
	
private:
	//ó���� �������� ����Ű�� ���
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;

	//����Ʈ�� ����� ��� ��
	int count = 0;
};