#include <iostream>

//����Ž��
//Binary Search
int BinarySearch(int array[], int target, int low, int high)
{
	//[1,2,3,4...,9]
	//mid = 5 �߰���. 
	//[1234],[6789] ������ ���� �� Ÿ���� Ž��
	// target > mid ? targer < mid ? �� �����߿��� �� ������ ���ǹ����� ���� Ž��
	// target == array[mid].

	// ���� ����(����/����).
	
	// �˻� ����
	if (low > high) // low�� high���� �۾ƾ���
	{
		return -1;
	}

	//�߰� ��
	int mid = (low + high) / 2;

	//Ž�� ���� ���� Ȯ��. -> ����� Ÿ���̸� �ٷ� �����ع�����
	if (array[mid] == target)
	{
		return mid;
	}
	//������ �� ���� Ž��
	else if (array[mid] < target)
	{
		return BinarySearch(array, target, mid + 1, high);
	}
	
	//���� �� Ž�� ���� else �Ƚᵵ �ɵ�?
	return BinarySearch(array, target, low, mid - 1);
}

int main()
{
	//Ž���� �ڷ�
	//���� Ž���� �����Ϸ��� ������ �ʼ�
	int array[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
	int length = sizeof(array) / sizeof(array[0]);
	int target = 56;

	int result = BinarySearch(array, target, 0, length - 1);

	if (result < 0)
	{
		std::cout << "�˻� ����";
	}
	else
	{
		std::cout << target << "�� " << result << "�� �ε������� ã��\n";
	}

	std::cin.get();
}