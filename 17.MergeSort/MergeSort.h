#pragma once

/// <summary>
/// ���ҵ� �迭�� �ٽ� ��ġ�� ���� �Լ�. 
/// </summary>
/// <param name="array">������ �迭</param>
/// <param name="leftArray">���ҵ� ���� �迭</param>
/// <param name="leftArrayLength">���� �迭 ũ��</param>
/// <param name="rightArray">���ҵ� ������ �迭</param>
/// <param name="rightArrayLength">������ �迭 ũ��</param>
void Merge(int* array, int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength);

/// <summary>
/// ���� ���� �Լ�.
/// </summary>
/// <param name="array">������ ��� �迭</param>
/// <param name="length">�迭 ũ��</param>
void MergeSort(int* array, int length);

