#pragma once

#include <iostream>
//��������(�����߿�) ũ�Ⱑ ���ϴ� �迭.
//���ø��� ���� ���̿� �������� �ؾ���.
//�̰� ���Ҹ����� h������ ���Ǹ� ���� ���ؼ� ���� ����ӿ��� �����ع���.

template <typename T>
class Vector
{
public:
	Vector()
		: size(0), capactiy(2)
	{
		//���� ������� �Ҵ�
		data = new T[capactiy];
	}

	//RAAI.
	~Vector()
	{
		if(data != nullptr)
			delete[] data;
	}

	//������ �߰��Լ�
	void PushBack(const T& value)
	{
		if (size == capactiy)
		{
			//TODO: ���ο� ������ ���Ҵ� �ʿ���(�̻�)

			ReAllocate(capactiy * 2);
		}

		//����� ������ ��� ���� ��ġ�� ���ο� �� ����.
		data[size] = value;

		//����� ����� ũ�� ���� ó��.
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

	//���� �� ������ ���� �ȵ��� ������ �����ε�
	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	//const ���� �ȸ���� ���߿� const ����
	const T& operator[](int index) const
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	//���� �Լ� �� �����Լ�
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
		//1. ���ο� ���� �Ҵ�
		T* newBlock = new T[newcapactiy];
		memset(newBlock, 0, sizeof(T) * newcapactiy);

		//2. ������ ����
		memcpy(newBlock, data, sizeof(T) * capactiy);
		//�Ʒ� for���� ����.
		//for (int ix = 0; ix < capactiy; ++ix)
		//{
		//	newBlock[ix] = data[ix];
		//}

		//3. �� �� �޸𸮰��� ���� �� ������Ʈ
		delete[] data;
		data = newBlock;
		capactiy = newcapactiy;
		//delete[] newBlock;
	}

	inline T* Data() const { return data; }

	inline int Size() const { return size; }

	inline int Capacity() const { return capactiy; }
private:
	//�ڷ� �����̳�
	T* data = nullptr;

	//�迭�� ����� ����� ��
	int size = 0;

	//�̸� Ȯ���ص� ���� ������ ũ��
	int capactiy;
};