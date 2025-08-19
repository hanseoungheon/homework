#include "MergeSort.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void Merge(int* array, 
	int* leftArray, int leftArrayLength, 
	int* rightArray, int rightArrayLength)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		++mergedIndex;
	}

	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	while (rightIndex < leftArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

void MergeSort(int* array, int length)
{
	
	//예외 처리(재귀 함수 종료 조건.)
	if (length <= 1)
	{
		return;
	}

	//배열 분할
	int mid = length / 2;
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// 왼쪽 배열에 값복사, 0부터 mid인덱스까지 복사.
	memcpy(leftArray, array, sizeof(int) * mid);

	// 오른쪽 배열에 값 복사, mid부터 length -mid 인덱스까지 복사.
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// 왼쪽 배열에 대해 병합 정렬
	MergeSort(leftArray, mid);

	// 오른쪽 배열에 대해 병합 정렬
	MergeSort(rightArray, mid);

	//병합
	Merge(array,leftArray,mid,rightArray,length - mid);

	delete[] leftArray;
	delete[] rightArray;
}
