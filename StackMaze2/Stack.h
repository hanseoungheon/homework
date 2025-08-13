#pragma once
#include <iostream>
#include <Windows.h>

//최대 저장수

const int stackCount = 100;

template <typename T>
class Stack
{
public:
	Stack() = default;

	~Stack() = default;

	//스택이 비었는지 확인
	bool IsEmpty() const
	{
		return count == 0;
	}

	//스택이 가득 찼는지 확인
	bool IsFull() const
	{
		return count == stackCount;
	}

	//스택에 데이터 추가
	bool Push(const T& exp)
	{
		if (IsFull())
		{
			MessageBoxA(
				nullptr,
				"스택이 가득차 있어 추가가 불가능합니다.",
				"Stack Push Error",
				MB_OK
			);
			std::cout << "스택이 가득차 있어 추가가 불가능합니다.\n";
			return false;
		}

		//전달된 경험치를 데이터에 저장
		data[count] = exp;
		++count;

		return true;
	}

	//스택에 데이터 추출
	T Pop()
	{
		if (IsEmpty())
		{
			MessageBoxA(
				nullptr,
				"스택이 비어 있어 추출가 불가능합니다.",
				"Stack Pop Error",
				MB_OK
			);

			std::cout << "스택이 비어 있어서 추출이 불가능합니다.\n";
			return -1.0f;
		}

		--count;
		return data[count];
	}

	//정리 함수
	void Clear()
	{
		memset(data, 0, sizeof(T) * stackCount);
		count = 0;
	}
	//스택에 저장된 데이터 Getter
	int GetCount() const
	{
		return count;
	}

private:
	T data[stackCount] = { };
	//스택에 저장되는 자료 수 

	//count를 head로 사용
	int count = 0;
};