#include "QuickSort.h"

int Partition(int* array, int left, int right)
{
	//�ǹ��� �������� �迭�� ����.
	int pivot = array[left];
	int low = left + 1;
	int high = right;

	//low�� high�� �����Ҷ� ���� �ݺ�
	while (low <= high)
	{
		//���ʿ��� ���������� �˻�
		while (low <= right && array[low] <= pivot)
		{
			++low;
		}

		while (high > left && array[high] >= pivot)
		{
			--high;
		}

		//���� ���� Ȯ��.
		//low�� high�� ���������� ���� ����
		if (low > high)
		{
			break;
		}

		Swap<int>(array[low], array[high]);
	}

	//�ǹ����� ���� ������ ���̶� ��ȯ.
	Swap<int>(array[left], array[high]);

	//���� ������ ������ �ε����� ��ȯ
	return high;
}

void QuickSort(int* array, int left, int right)
{
	//���� ó��
	//���� �ε����� ������ �ε����� ��ġ�ų� ���������� ����.
	if (left >= right)
	{
		return;
	}

	// �ǹ��� �������� �迭�� ����!
	int pivot = Partition(array, left, right);

	//���� ����� ȣ��
	//����
	QuickSort(array, left, pivot - 1);

	//������
	QuickSort(array, pivot + 1, right);
}
