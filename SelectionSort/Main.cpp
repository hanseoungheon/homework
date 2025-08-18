#include <iostream>
 
template<typename T>
void Swap(T& num1, T& num2)
{
	T temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

void SelectionSort(int* array, int length)
{
	//예외처리
	if (length <= 1)
	{
		return; //길이가 1개 이하면 정리할 필요가 없음 그냥 반환함.
	}

	//int ix, jx;
	for (int ix = 0; ix < length - 1; ++ix)
	{
		int minIndex = ix;

		for (int jx = ix; jx < length; ++jx)
		{
			//int min = INT_MAX;
			if (array[jx] < array[minIndex])
			{
				minIndex = jx;
			}
		}

		if(minIndex != ix)
			Swap<int>(array[ix], array[minIndex]);
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
	int length = sizeof(array) / sizeof(array[0]);

	std::cout << "정렬 전 배열 : ";
	PrintArray(array, length);

	SelectionSort(array, length);

	std::cout << "정렬 후 배열 : ";
	PrintArray(array, length);
}