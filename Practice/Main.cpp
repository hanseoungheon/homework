#include <iostream>

#define ArraySize(array) sizeof(array) / sizeof(array[0])

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
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
int Partition(int* array, int left, int right)
{
	int pivot = array[left];
	int low = left + 1;
	int high = right;

	while (low <= high) //�����Ҷ� ���� �ݺ�!
	{
		while (low <= right && array[low] <= pivot)
		{
			++low;
		}

		while (high > left && array[high] >= pivot)
		{
			--high;
		}

		if (low > high) //������ ���� ����
		{
			break;
		}

		Swap<int>(array[low], array[high]);

	}

	Swap<int>(array[left], array[high]);

	return high; //high�� ���� �ǹ��� ��.
}

void QuickSort(int* array, int left, int right)
{
	if (left >= right) //������ �����ʺ��� ŭ = ������ �������� �ǰ� �������� ������ ��. ����!
	{
		return;
	}

	int pivot = Partition(array, left, right);

	//���� ���
	QuickSort(array, left, pivot - 1);

	//������ ���
	QuickSort(array, pivot + 1, right);
}

int main()
{
	int array[] =
	{
		1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
		80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
		52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
		92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
		90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
		98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
		6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
		30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
		49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
		32, 46, 70, 3, 86, 68, 36, 67, 55, 65
	};

	int length = (int)ArraySize(array);

	//������ ���
	PrintArray(array, length);

	//����
	QuickSort(array, 0, length - 1);

	//���� �� ���
	std::cout << "\n";
	PrintArray(array, length);

	std::cin.get();
}