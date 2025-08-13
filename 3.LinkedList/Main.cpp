#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "LinkedList.h"
int main()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	LinkedList list;

	char input[50] = {};

	//데이터 추가 루프
	while (true)
	{
		std::cout << "추가할 데이터를 입력해주세요(종료는 q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		//데이터 삽입
		//예외처리.
		if (!atoi(input))
		{
			std::cout << "숫자만 입력가능합니다.\n";
			continue;
		}

		//데이터 삽입
		list.Insert(atoi(input));

		//출력
		list.Print();
	}

	while (true)
	{
		std::cout << "현재 카운트 수 : " << list.Count() << "\n";	
		std::cout << "오름차순으로 정렬을 원하시면 s, 아니면 q를 입력해주세요.";
		std::cin >> input;
		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		if (strcmp(input, "s") == 0 || strcmp(input, "S") == 0)
		{
			list.MyNodeSort();
		}

		//list.Print();
	}
	
	//데이터 삭제 루프
	while (true)
	{
		std::cout << "삭제할 데이터를 입력해주세요(종료는 q)\n";
		std::cin >> input;



		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		//데이터 삽입
		//예외처리.
		else if (!atoi(input))
		{
			std::cout << "숫자만 입력가능합니다.\n";
			continue;
		}

		//데이터 삭제
		list.Delete(atoi(input));
		//출력
		list.Print();
	}

	int a = 3;
	int b = 4;
	int& ref = a;
	ref = b;
	
	std::cin.get();
}