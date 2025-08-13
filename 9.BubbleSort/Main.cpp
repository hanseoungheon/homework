#include <iostream>

void Swap(int& a, int& b)
{
	//std::swap(a,b);
	int temp = a;
	a = b;
	b = temp;
}

//출력 함수
void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << array[i];

		if (i < length - 1)
			std::cout << ", ";
	}

	std::cout << "\n";
}


void Sort(int* array, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - i - 1; ++j)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}

			//PrintArray(array, length);
		}
	}
}


int main()
{
	int array[] = { 2,5,3,1,4 };

	int length = sizeof(array) / sizeof(array[0]);

	std::cout << "정렬 전 : ";
	PrintArray(array,length);

	Sort(array, length);

	std::cout << "정렬 후 : ";
	PrintArray(array, length);
}