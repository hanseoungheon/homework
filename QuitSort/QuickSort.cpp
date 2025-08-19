#include "QuickSort.h"

int Partition(int* array, int left, int right)
{
	//피벗을 기준으로 배열을 분할.
	int pivot = array[left];
	int low = left + 1;
	int high = right;

	//low와 high가 교차할때 까지 반복
	while (low <= high)
	{
		//왼쪽에서 오른쪽으로 검색
		while (low <= right && array[low] <= pivot)
		{
			++low;
		}

		while (high > left && array[high] >= pivot)
		{
			--high;
		}

		//종료 조건 확인.
		//low와 high가 교차했으면 루프 종료
		if (low > high)
		{
			break;
		}

		Swap<int>(array[low], array[high]);
	}

	//피벗값과 왼쪽 마지막 값이랑 교환.
	Swap<int>(array[left], array[high]);

	//왼쪽 집합의 마지막 인덱스를 반환
	return high;
}

void QuickSort(int* array, int left, int right)
{
	//예외 처리
	//왼쪽 인덱스가 오른쪽 인덱스와 겹치거나 교차했으면 리턴.
	if (left >= right)
	{
		return;
	}

	// 피벗을 기준으로 배열을 분할!
	int pivot = Partition(array, left, right);

	//이후 재귀적 호출
	//왼쪽
	QuickSort(array, left, pivot - 1);

	//오른쪽
	QuickSort(array, pivot + 1, right);
}
