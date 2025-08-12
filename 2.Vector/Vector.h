#pragma once

#include <iostream>
//동적으로(실행중에) 크기가 변하는 배열.
//템플릿은 같은 파이에 구현까지 해야함.
//이게 뭔소리나면 h헤더라고 정의만 하지 못해서 여기 헤더임에도 구현해버림.

template <typename T>
class Vector
{
public:
	Vector()
		: size(0), capactiy(2)
	{
		//내부 저장공간 할당
		data = new T[capactiy];
	}

	//RAAI.
	~Vector()
	{
		if(data != nullptr)
			delete[] data;
	}

	//데이터 추가함수
	void PushBack(const T& value)
	{
		if (size == capactiy)
		{
			//TODO: 새로운 공간에 재할당 필요함(이사)

			ReAllocate(capactiy * 2);
		}

		//저장된 마지막 요소 다음 위치에 새로운 값 지정.
		data[size] = value;

		//저장된 요소의 크기 증가 처리.
		++size;
	}

	void PushBack(T&& value)
	{
		if (size == capactiy)
		{
			ReAllocate( 2 * capactiy);
		}

		data[size] = std::move((value));
		++size;
	}

	//접근 및 설정을 위한 안덱스 연산자 오버로딩
	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	//const 따로 안만들면 나중에 const 못씀
	const T& operator[](int index) const
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	//접근 함수 및 설정함수
	T& At(int index)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	void Set(int index, const T& value)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		data[index] = value;
	}

	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

private:
	void ReAllocate(int newcapactiy)
	{
		//1. 새로운 공간 할당
		T* newBlock = new T[newcapactiy];
		memset(newBlock, 0, sizeof(T) * newcapactiy);

		//2. 기존값 복사
		memcpy(newBlock, data, sizeof(T) * capactiy);
		//아래 for문과 같음.
		//for (int ix = 0; ix < capactiy; ++ix)
		//{
		//	newBlock[ix] = data[ix];
		//}

		//3. 다 쓴 메모리공간 해제 및 업데이트
		delete[] data;
		data = newBlock;
		capactiy = newcapactiy;
		//delete[] newBlock;
	}

	inline T* Data() const { return data; }

	inline int Size() const { return size; }

	inline int Capacity() const { return capactiy; }
private:
	//자료 컨테이너
	T* data = nullptr;

	//배열에 저장된 요소의 수
	int size = 0;

	//미리 확보해둔 저장 공간의 크기
	int capactiy;
};