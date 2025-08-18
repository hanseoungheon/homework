#pragma once
#include <iostream>
const int maxQueueCount = 100;

class Queue
{
public:
	Queue()
	{
		memset(data, 0, sizeof(int) * maxQueueCount);
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		//rear�� ������ġ�� front�̸� ���� ��
		return (rear + 1) % maxQueueCount == front;
		//rear�� ����ĭ�� front�̹Ƿ� rear + 1 �ϰ� ��Ҽ��� ������ ��
	}

	bool Enqueue(int newData)
	{
		if (IsFull())
		{
			std::cout << "Error: ť�� ���� ��\n";
			return false;
		}
		//�� ��rear�� ���� ��ġ�� ���ο� ������ �߰�
		rear = (rear + 1) % maxQueueCount;
		data[rear] = newData;

		return true;
	}

	//ť���� ������ ����
	bool Dequeue(int& outValue)
	{
		//���� Ȯ��
		if (IsEmpty())
		{
			std::cout << "Error: ť�� �������\n";
			return false;
		}
		
		//�տ� �ִ� ������ ����
		front = (front + 1) % maxQueueCount;
		outValue = data[front];

		data[front] = 0;
		return true;
	}

	void Print()
	{
		std::cout << "ť ����";
		int max = front < rear ? rear : rear + maxQueueCount;
		for (int i = front + 1; i < max; ++i)
		{
			std::cout << "���� ť " << data[i] << "\n";
		}


		std::cout << "\n";
	}



private:
	int front = 0;
	int rear = 0;
	int data[maxQueueCount];
};