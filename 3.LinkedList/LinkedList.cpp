	#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
	:head(nullptr),count(0)
{

}

LinkedList::~LinkedList()
{
	//���� ����
	//if (head != nullptr)
	//	delete head;
	//count = NULL;
	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		//���� ���� �Ѿ�� ���� �ӽ� ����
		trail = current;

		//���� ���� �̵�
		current = current->next;
		
		//��� ����
		delete trail;
		trail = nullptr;

		//����� ����
		--count;
	}
}

void LinkedList::AddToHead(int newData)
{
	//���ο� ��� ����
	Node* newNode = new Node(newData);

	//#1 Head�� ����ִ� ���
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}
	//#2 Head�� ������� ���� ���
	newNode->next = head;	//�ּ� ����
	head = newNode;
	++count;
}

void LinkedList::Insert(int newData)
{
	//�� �ڿ��ٰ� �߰��ϴ� �Լ�
	Node* newNode = new Node(newData);

	//#����Ʈ�� ����ִ� ���
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	//#2 ����Ʈ�� ������� ���� ���
	//1. ������ ��� �˻��ؾ���.
	//Ÿ�� Ÿ�� ���ٰ� nullptr�� ��������?
	Node* current = head;
	Node* trail = nullptr;

	//next��尡 null�϶����� �˻�
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}


	//������ ��� �˻� �Ϸ�� ����!
	trail->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	//Todo: �������� �����ؾ���

	//����Ʈ�� ��������� ����
	if (head == nullptr)
	{
		std::cout << "����Ʈ�� ����־ ������ �Ұ����մϴ�.\n";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		//���� ����
		//ã������ �����͸� ���� ��� �˻��� ������ ���!
		if (current->data == data)
		{
			break;
		}
			
		//��ã������ �˻� �̾
		trail = current;
		current = current->next;
	}

	//����� �� Ȯ��
	//#1 ����Ʈ�� �����Ϸ��� �����Ͱ� ����(��ã��)
	if (current == nullptr)
	{
		std::cout << "��: " << data << "�� ã�� ���߽��ϴ�.";
		return;
	}

	//#2 �˻��� ������ ���
	//#2-1 �����Ϸ��� ��尡 head�� ���
	if (current == head)
	{
		//head�� ������ �ȵǹǷ� �� ���� ��带 head�� ����
		head = head->next;

	}
	//#2-2 �����Ϸ��� ��尡 head�� �ƴ� ���
	else
	{
		//[h]->[1]->[2]->[3]->nullptr
		//2�� �������Ѵٸ�
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
	//���
	Node* current = head;

	while (current != nullptr)
	{
		//���� ��� ������ ���
		std::cout << *current << "\n";

		//���� ���� �̵�
		current = current->next;
	}
}

void LinkedList::MyNodeSort() //���̴� count
{
	Node* current = head;
	Node* trail = nullptr;
	Node* temp = nullptr;
	Node* previous = nullptr;
	for (int i = 0; i < count - 1; ++i)
	{
		std::cout << "i�� " << i << "�� ��!\n";
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

