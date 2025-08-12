
#include "PreCompiledHeader.h"

#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	//������ �Է� ����
	char input[50] = {};

	while (true)
	{
		std::cout << "�߰��� �����͸� �Է��ϼ���";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		if (atoi(input) == false)
		{
			std::cout << "���ڸ� �Է� �����մϴ�.";
			continue;
		}

		list.PushLast(atoi(input));
		list.Print();
	}
}