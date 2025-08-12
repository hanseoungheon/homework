
#include "PreCompiledHeader.h"

#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	//데이터 입력 루프
	char input[50] = {};

	while (true)
	{
		std::cout << "추가할 데이터를 입력하세요";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		if (atoi(input) == false)
		{
			std::cout << "숫자만 입력 가능합니다.";
			continue;
		}

		list.PushLast(atoi(input));
		list.Print();
	}
}