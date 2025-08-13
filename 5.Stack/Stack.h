#pragma once
#include <iostream>
#include <Windows.h>

//�ִ� �����

#define TEST 0

#if TEST
const int stackCount = 1;
#else
const int stackCount = 100;
#endif
//��ü����� ���� ���
//1. �ʿ��� ���� ��� �� ���� ->x ���(�޼ҵ�) ����
//2. �޼ҵ忡�� �ʿ��� ���� ����
//�޼ҵ�(�޽���(public), �޼ҵ�(private/protected)
//��ü ���� ������ �޽����θ� ��
//�� ������ ��� �������

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
		data[count++] = exp;

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
	float data[stackCount] = { };
	//���ÿ� ����Ǵ� �ڷ� �� 

	//count�� head�� ���
	int count = 0;
};