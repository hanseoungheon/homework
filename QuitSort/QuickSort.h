#pragma once

template<typename T>

void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

//배열을 분할한 뒤 나누는 함수
int Partition(int* array, int left, int right);

void QuickSort(int* array, int left, int right);