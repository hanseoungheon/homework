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
	
	//���� ó��(��� �Լ� ���� ����.)
	if (length <= 1)
	{
		return;
	}

	//�迭 ����
	int mid = length / 2;
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// ���� �迭�� ������, 0���� mid�ε������� ����.
	memcpy(leftArray, array, sizeof(int) * mid);

	// ������ �迭�� �� ����, mid���� length -mid �ε������� ����.
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// ���� �迭�� ���� ���� ����
	MergeSort(leftArray, mid);

	// ������ �迭�� ���� ���� ����
	MergeSort(rightArray, mid);

	//����
	Merge(array,leftArray,mid,rightArray,length - mid);

	delete[] leftArray;
	delete[] rightArray;
}
