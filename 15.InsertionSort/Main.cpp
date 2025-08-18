#include <iostream>

#define ArraySize(array) sizeof(array) / sizeof(array[0])

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 삽입 정렬
void InsertionSort(int* array, int length)
{
	if (length <= 1)
		return;

	for (int ix = 1; ix < length; ++ix)
	{
		int keyValue = array[ix];
		int jx = ix - 1;

		while (jx >= 0 && array[jx] > keyValue)
		{
			// 값 밀기.
			array[jx + 1] = array[jx];
			--jx;
		}

		array[jx + 1] = keyValue;
	}

}

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{
	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	int length = ArraySize(array);

	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	InsertionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);


}