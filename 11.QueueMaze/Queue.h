#pragma once
#include <iostream>

//const int maxQueueCount = 100;
template<typename T, int Size = 10>
class Queue
{
public:
	Queue()
		:size(Size + 1)
	{
		memset(data, 0, sizeof(int) * (size + 1));
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		//rear�� ������ġ�� front�̸� ���� ��
		return (rear + 1) % size == front;
		//rear�� ����ĭ�� front�̹Ƿ� rear + 1 �ϰ� ��Ҽ��� ������ ��
	}

	bool Enqueue(const T& newData)
	{
		if (IsFull())
		{
			std::cout << "Error: ť�� ���� ��\n";
			return false;
		}
		//�� ��rear�� ���� ��ġ�� ���ο� ������ �߰�
		rear = (rear + 1) % size;
		data[rear] = newData;

		return true;
	}

	//ť���� ������ ����
	bool Dequeue(T& outValue)
	{
		//���� Ȯ��
		if (IsEmpty())
		{
			std::cout << "Error: ť�� �������\n";
			return false;
		}

		//�տ� �ִ� ������ ����
		front = (front + 1) % size;
		outValue = data[front];

		memset(data + front, 0, sizeof(T));
		return true;
	}

	void Print()
	{
		std::cout << "ť ����";
		int max = front < rear ? rear : rear + size;
		for (int i = front + 1; i < max; ++i)
		{
			std::cout << "���� ť " << data[i % size]  << "\n";
		}	


		std::cout << "\n";
	}



private:
	int front = 0;
	int rear = 0;
	int size = 0;
	T data[Size + 1];
};