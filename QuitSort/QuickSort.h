#pragma once

template<typename T>

void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

//�迭�� ������ �� ������ �Լ�
int Partition(int* array, int left, int right);

void QuickSort(int* array, int left, int right);