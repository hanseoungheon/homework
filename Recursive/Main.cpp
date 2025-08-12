#include <iostream>

//이진탐색
//Binary Search
int BinarySearch(int array[], int target, int low, int high)
{
	//[1,2,3,4...,9]
	//mid = 5 중간값. 
	//[1234],[6789] 반으로 나눈 후 타겟을 탐색
	// target > mid ? targer < mid ? 두 영역중에서 한 영역만 조건문으로 구해 탐색
	// target == array[mid].

	// 종료 조건(예외/만족).
	
	// 검색 실패
	if (low > high) // low는 high보다 작아야함
	{
		return -1;
	}

	//중간 값
	int mid = (low + high) / 2;

	//탐색 성공 여부 확인. -> 가운데가 타겟이면 바로 추출해버리기
	if (array[mid] == target)
	{
		return mid;
	}
	//오른쪽 반 먼저 탐색
	else if (array[mid] < target)
	{
		return BinarySearch(array, target, mid + 1, high);
	}
	
	//왼쪽 반 탐색 굳이 else 안써도 될듯?
	return BinarySearch(array, target, low, mid - 1);
}

int main()
{
	//탐색할 자료
	//이진 탐색이 가능하려면 정렬이 필수
	int array[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
	int length = sizeof(array) / sizeof(array[0]);
	int target = 56;

	int result = BinarySearch(array, target, 0, length - 1);

	if (result < 0)
	{
		std::cout << "검색 실패";
	}
	else
	{
		std::cout << target << "을 " << result << "번 인덱스에서 찾음\n";
	}

	std::cin.get();
}