#pragma once
#include <iostream>
#include <Windows.h>

//�ִ� �����

const int stackCount = 100;

template <typename T>
class Stack
{
public:
	Stack() = default;

	~Stack() = default;

	//������ ������� Ȯ��
	bool IsEmpty() const
	{
		return count == 0;
	}

	//������ ���� á���� Ȯ��
	bool IsFull() const
	{
		return count == stackCount;
	}

	//���ÿ� ������ �߰�
	bool Push(const T& exp)
	{
		if (IsFull())
		{
			MessageBoxA(
				nullptr,
				"������ ������ �־� �߰��� �Ұ����մϴ�.",
				"Stack Push Error",
				MB_OK
			);
			std::cout << "������ ������ �־� �߰��� �Ұ����մϴ�.\n";
			return false;
		}

		//���޵� ����ġ�� �����Ϳ� ����
		data[count] = exp;
		++count;

		return true;
	}

	//���ÿ� ������ ����
	T Pop()
	{
		if (IsEmpty())
		{
			MessageBoxA(
				nullptr,
				"������ ��� �־� ���Ⱑ �Ұ����մϴ�.",
				"Stack Pop Error",
				MB_OK
			);

			std::cout << "������ ��� �־ ������ �Ұ����մϴ�.\n";
			return -1.0f;
		}

		--count;
		return data[count];
	}

	//���� �Լ�
	void Clear()
	{
		memset(data, 0, sizeof(T) * stackCount);
		count = 0;
	}
	//���ÿ� ����� ������ Getter
	int GetCount() const
	{
		return count;
	}

private:
	T data[stackCount] = { };
	//���ÿ� ����Ǵ� �ڷ� �� 

	//count�� head�� ���
	int count = 0;
};