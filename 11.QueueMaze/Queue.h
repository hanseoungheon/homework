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
		//rear의 다음위치가 front이면 가득 참
		return (rear + 1) % size == front;
		//rear의 다음칸이 front이므로 rear + 1 하고 요소수로 나누면 됨
	}

	bool Enqueue(const T& newData)
	{
		if (IsFull())
		{
			std::cout << "Error: 큐가 가득 참\n";
			return false;
		}
		//뒤 즉rear의 다음 위치에 새로운 데이터 추가
		rear = (rear + 1) % size;
		data[rear] = newData;

		return true;
	}

	//큐에서 데이터 추출
	bool Dequeue(T& outValue)
	{
		//실패 확인
		if (IsEmpty())
		{
			std::cout << "Error: 큐가 비어있음\n";
			return false;
		}

		//앞에 있는 데이터 추출
		front = (front + 1) % size;
		outValue = data[front];

		memset(data + front, 0, sizeof(T));
		return true;
	}

	void Print()
	{
		std::cout << "큐 내용";
		int max = front < rear ? rear : rear + size;
		for (int i = front + 1; i < max; ++i)
		{
			std::cout << "현재 큐 " << data[i % size]  << "\n";
		}	


		std::cout << "\n";
	}



private:
	int front = 0;
	int rear = 0;
	int size = 0;
	T data[Size + 1];
};